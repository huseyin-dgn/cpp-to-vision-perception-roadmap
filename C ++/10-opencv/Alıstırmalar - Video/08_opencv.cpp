// /*
// 🧩 SORU 9 — VIDEO'DAN OKU, CANNY UYGULA, YENİ VIDEO KAYDET

// Görevlerin:

// 1) "input.mp4" videosunu aç:
//       cv::VideoCapture cap("input.mp4");

// 2) Video açılmazsa programı bitir.

// 3) Videonun FPS, genişlik ve yüksekliğini al:
//       double fps   = cap.get(CAP_PROP_FPS);
//       int width    = (int)cap.get(CAP_PROP_FRAME_WIDTH);
//       int height   = (int)cap.get(CAP_PROP_FRAME_HEIGHT);

// 4) VideoWriter oluştur:
//       cv::VideoWriter writer(
//           "output.mp4",
//           cv::VideoWriter::fourcc('m','p','4','v'),
//           fps,
//           cv::Size(width, height),
//           false  // Canny tek kanal (gri) olduğu için false
//       );

// 5) Writer açılmazsa programı bitir.

// 6) Sonsuz döngü:
//       - cap.read(frame);
//       - frame boşsa break;

//       - frame'i griye çevir
//       - Canny uygula:
//             cv::Canny(gray, edges, 100, 200);

//       - edges'i output videosuna writer.write(edges);

//       - Ekranda:
//             "Orijinal" → frame
//             "Canny"    → edges
//         pencerelerini göster.

//       - 'q' basılırsa döngüden çık.

// 7) Döngü bitince:
//       cap.release();
//       writer.release();
//       destroyAllWindows();

// Aşağıdaki main fonksiyonunu bu adımlara göre doldur:
// */

// #include <iostream>
// #include <opencv2/opencv.hpp>

// int main()
// {
//     // 1) Video dosyasını aç

//     // 2) Açılmazsa çık

//     // 3) FPS, genişlik, yükseklik al

//     // 4) VideoWriter oluştur

//     // 5) Writer açılmazsa çık

//     // 6) Sonsuz döngü

//         // Frame, gray, edges tanımla

//         // Frame oku, boşsa break

//         // Griye çevir

//         // Canny uygula

//         // edges'i output videoya yaz

//         // Orijinal ve Canny pencerelerini göster

//         // 'q' gelirse break

//     // 7) Kaynakları serbest bırak

//     return 0;
// }

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 1) Video dosyasını aç
    cv::VideoCapture cap("input.mp4");

    // 2) Açılmazsa çık
    if (!cap.isOpened())
    {
        std::cout << "Video acilamadi!" << std::endl;
        return -1;
    }

    // 3) FPS, genişlik, yükseklik al
    double fps = cap.get(cv::CAP_PROP_FPS);
    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    std::cout << "Video FPS: " << fps << std::endl;
    std::cout << "Genislik: " << width << ", Yukseklik: " << height << std::endl;

    // 4) VideoWriter oluştur (Canny tek kanal, o yüzden isColor = false)
    cv::VideoWriter writer(
        "output.mp4",
        cv::VideoWriter::fourcc('m', 'p', '4', 'v'),
        fps > 0 ? fps : 25.0, // fps 0 dönerse fallback olarak 25 fps kullan
        cv::Size(width, height),
        false // tek kanal (gri / Canny)
    );

    // 5) Writer açılmazsa çık
    if (!writer.isOpened())
    {
        std::cout << "VideoWriter olusturulamadi!" << std::endl;
        return -1;
    }

    while (true)
    {
        cv::Mat frame;
        cv::Mat gray;
        cv::Mat edges;

        // Frame oku
        cap.read(frame);
        if (frame.empty())
        {
            std::cout << "Video sonuna gelindi veya frame okunamadi." << std::endl;
            break;
        }

        // Griye çevir
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Canny kenar tespiti
        cv::Canny(gray, edges, 100, 200);

        // edges tek kanallı Mat, writer.isColor = false olduğu için direkt yazabiliriz
        writer.write(edges);

        // Ekranda göster
        cv::imshow("Orijinal", frame);
        cv::imshow("Canny", edges);

        // 'q' basılırsa çık
        char c = static_cast<char>(cv::waitKey(1));
        if (c == 'q' || c == 'Q')
        {
            break;
        }
    }

    // 7) Kaynakları serbest bırak
    cap.release();
    writer.release();
    cv::destroyAllWindows();

    return 0;
}
