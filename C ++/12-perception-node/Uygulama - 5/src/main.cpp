#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

#include "frame_types.hpp"
#include "detection_types.hpp"
#include "yolo_preprocess_node.hpp"
#include "yolo_inference_node.hpp"
#include "draw_utils.hpp"

int main(int argc, char** argv)
{
    std::string source = "0";
    std::string model_path = "../models/yolo_detector.torchscript.pt";

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "--model" && i + 1 < argc)
        {
            model_path = argv[++i];
        }
        else
        {
            source = arg;
        }
    }

    std::cout << "[main] source: " << source << "\n";
    std::cout << "[main] model : " << model_path << "\n";

    cv::VideoCapture cap;

    if (source == "0" || source == "1" || source == "2")
    {
        int cam_index = std::stoi(source);
        cap.open(cam_index);
    }
    else
    {
        cap.open(source);
    }

    if (!cap.isOpened())
    {
        std::cerr << "[main] cannot open source\n";
        return 1;
    }

    YoloPreprocessConfig pre_cfg;
    pre_cfg.input_width  = 640;
    pre_cfg.input_height = 640;
    pre_cfg.device       = "cpu";

    YoloPreprocessNode pre_node(pre_cfg);

    YoloInferenceConfig inf_cfg;
    inf_cfg.model_path     = model_path;
    inf_cfg.device         = "cpu";
    inf_cfg.score_threshold = 0.25f;

    YoloInferenceNode inf_node(inf_cfg);

    cv::Mat frame;
    std::uint64_t frame_id = 0;

    cv::namedWindow("YOLO Perception", cv::WINDOW_NORMAL);

    while (true)
    {
        if (!cap.read(frame) || frame.empty())
            break;

        ++frame_id;

        int orig_w = frame.cols;
        int orig_h = frame.rows;

        ImageFrame f(frame, frame_id, "stream");

        torch::Tensor input_tensor = pre_node.process(f);
        if (!input_tensor.defined() || input_tensor.numel() == 0)
            continue;

        DetectionList dets = inf_node.infer(input_tensor, orig_w, orig_h);

        draw_detections(frame, dets);

        cv::imshow("YOLO Perception", frame);
        int key = cv::waitKey(1);
        if (key == 27) // ESC
            break;
    }

    return 0;
}
