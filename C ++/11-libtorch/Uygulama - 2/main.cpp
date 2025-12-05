// SORU:
//  - Bir resmi OpenCV ile nasıl okurum ve ekranda nasıl gösteririm?

#include <iostream>
#include <torch/script.h>
#include <opencv2/opencv.hpp>

int main()
{
    try
    {
        cv::Mat img = cv::imread("test.jpg");
        if (img.empty())
        {
            std::cerr << "Test.jpg yuklenemedi...";
            return -1;
        }

        std::cout << "Resim başarıyla yuklendi..Boyut ;" << img.cols << "X" << img.rows;

        cv::imshow("Görüntü", img);

        cv::waitKey(0);
    }
    catch (const std::exception &e)
    {
        std::cerr << "[EXCEPTION] " << e.what() << std::endl;
        return -1;
    }
    return 0;
}