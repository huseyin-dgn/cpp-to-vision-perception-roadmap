#include <iostream>
#include <stdexcept>
#include <opencv2/opencv.hpp>

int main()
{
    try
    {
        std::string imagePath = "test.jpg"; // Proje klasörüne bir test.jpg koyarsan güzel olur

        // Görüntüyü oku (BGR formatında gelir)
        cv::Mat img = cv::imread(imagePath);

        if (img.empty())
        {
            throw std::runtime_error("Gorsel yuklenemedi. Dosya yolu hatali mi? test.jpg var mi?");
        }

        std::cout << "Gorsel yuklendi. Boyut: "
                  << img.cols << "x" << img.rows << "\n";

        // Pencere aç ve görüntüyü göster
        cv::imshow("OpenCV Penceresi", img);

        std::cout << "Pencere acildi. Bir tusa bas, program kapansin.\n";
        cv::waitKey(0); // Herhangi bir tus bekler

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "[HATA] " << e.what() << "\n";
        return 1;
    }
}
