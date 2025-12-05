#include "yolo_inference_node.hpp"

#include <iostream>

YoloInferenceNode::YoloInferenceNode(const YoloInferenceConfig& config)
    : config_(config)
{
    if (config_.device == "cuda" && torch::cuda::is_available())
    {
        device_ = torch::kCUDA;
        std::cout << "[YoloInferenceNode] CUDA\n";
    }
    else
    {
        device_ = torch::kCPU;
        std::cout << "[YoloInferenceNode] CPU\n";
    }

    try
    {
        model_ = torch::jit::load(config_.model_path, device_);
        model_.eval();
        model_loaded_ = true;
        std::cout << "[YoloInferenceNode] model loaded: "
                  << config_.model_path << "\n";
    }
    catch (const c10::Error& e)
    {
        std::cerr << "[YoloInferenceNode] load error: "
                  << e.what() << "\n";
        model_loaded_ = false;
    }
}

DetectionList YoloInferenceNode::infer(const torch::Tensor& input,
                                       int orig_width,
                                       int orig_height)
{
    DetectionList out;

    if (!model_loaded_)
    {
        std::cerr << "[YoloInferenceNode] model not loaded\n";
        return out;
    }

    if (!input.defined() || input.numel() == 0)
    {
        std::cerr << "[YoloInferenceNode] invalid input\n";
        return out;
    }

    torch::Tensor x = input.to(device_);

    try
    {
        torch::NoGradGuard no_grad;

        std::vector<torch::jit::IValue> inputs;
        inputs.push_back(x);

        torch::IValue result = model_.forward(inputs);

        torch::Tensor det;
        if (result.isTensor())
        {
            det = result.toTensor();
        }
        else if (result.isTuple())
        {
            auto t = result.toTuple();
            det = t->elements()[0].toTensor();
        }
        else if (result.isList())
        {
            auto list = result.toTensorVector();
            if (!list.empty())
                det = list[0];
        }

        if (!det.defined() || det.numel() == 0)
            return out;

        if (det.dim() == 3)
            det = det[0];

        if (det.size(1) < 6)
        {
            std::cerr << "[YoloInferenceNode] unexpected det shape\n";
            return out;
        }

        float scale_x = static_cast<float>(orig_width) / 640.0f;
        float scale_y = static_cast<float>(orig_height) / 640.0f;

        int num = det.size(0);
        for (int i = 0; i < num; ++i)
        {
            float x1 = det[i][0].item<float>();
            float y1 = det[i][1].item<float>();
            float x2 = det[i][2].item<float>();
            float y2 = det[i][3].item<float>();
            float score = det[i][4].item<float>();
            int cls = static_cast<int>(det[i][5].item<float>());

            if (score < config_.score_threshold)
                continue;

            DetectedObject obj;
            obj.class_id = cls;
            obj.score    = score;
            obj.x1       = x1 * scale_x;
            obj.y1       = y1 * scale_y;
            obj.x2       = x2 * scale_x;
            obj.y2       = y2 * scale_y;

            out.push_back(obj);
        }
    }
    catch (const c10::Error& e)
    {
        std::cerr << "[YoloInferenceNode] inference error: "
                  << e.what() << "\n";
    }

    return out;
}
