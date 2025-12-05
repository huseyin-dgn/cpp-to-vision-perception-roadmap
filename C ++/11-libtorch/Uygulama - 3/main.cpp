// SORU:
//  - OpenCV ile okuduğum cv::Mat görüntüsünü, LibTorch için uygun
//    bir torch::Tensor haline nasıl getiririm?

#include <iostream>
#include <torch/script.h>
#include <opencv2/opencv.hpp>

int main()
{
    try
    {
        // 1) Resmi OpenCV ile oku
        cv::Mat img = cv::imread("test.jpg");
        if (img.empty())
        {
            std::cerr << "[HATA] test.jpg yuklenemedi..." << std::endl;
            return -1;
        }

        std::cout << "[OK] Orijinal resim boyutu: "
                  << img.cols << "x" << img.rows << " (W x H)" << std::endl;

        // 2) BGR -> RGB dönüşümü (PyTorch genelde RGB bekler)
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

        // 3) uint8 -> float32 ve 0–1 aralığına ölçekleme
        cv::Mat img_float;
        img.convertTo(img_float, CV_32F, 1.0 / 255.0);

        // 4) from_blob ile HWC -> tensor (N, H, W, C)
        //    Not: img_float.rows = H, img_float.cols = W, 3 kanal var.
        auto tensor_image = torch::from_blob(
            img_float.data,                               // veri pointer'ı
            {1, img_float.rows, img_float.cols, 3},       // boyutlar: N, H, W, C
            torch::TensorOptions().dtype(torch::kFloat32) // tip: float32
        );

        // 5) NHWC -> NCHW permute (PyTorch standart formatı)
        tensor_image = tensor_image.permute({0, 3, 1, 2}).contiguous();

        std::cout << "[OK] Tensor boyutu (NCHW): " << tensor_image.sizes() << std::endl;

        // *** Önemli Not:
        // from_blob, OpenCV'nin bellek alanını kullanıyor.
        // img/img_float yaşam döngüsü sonlanmadan bu tensörü kullanmam gerekiyor.
        // Gerekirse .clone() ile kendi kopyasını oluşturabilirim:
        //
        // tensor_image = tensor_image.clone();

        // Bu aşamada tensor_image artık modele verilebilecek durumda:
        // - Şekil: [1, 3, H, W]
        // - Tip: float32
        // - Değer aralığı: 0–1
    }
    catch (const std::exception &e)
    {
        std::cerr << "[EXCEPTION] " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
