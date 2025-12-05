/*
🧩 SORU 6 — CANLI AKIŞTA YÜZ TESPİTİ

Görevlerin:

1) Haar cascade sınıflandırıcıyı yükle:
      cv::CascadeClassifier face_cascade;
      face_cascade.load("haarcascade_frontalface_default.xml");
   - Eğer yüklenemezse ekrana hata bas ve programı bitir.

2) Kamerayı aç:
      cv::VideoCapture cap(0);
   - Açılmazsa programı bitir.

3) Sonsuz döngü başlat:
      while (true) { ... }

4) Döngü içinde:
      a) Kameradan frame oku
      b) Frame boşsa break

5) Frame'i griye çevir:
      cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

6) Görüntüyü biraz yumuşat (noise azaltmak için):
      cv::equalizeHist(gray, gray);
   (istenirse GaussianBlur da eklenebilir)

7) Yüzleri tespit et:
      std::vector<cv::Rect> faces;
      face_cascade.detectMultiScale(
          gray, faces,
          1.1,        // scaleFactor
          3,          // minNeighbors
          0,          // flags (genelde 0)
          cv::Size(30, 30) // minSize
      );

   Yorum satırı olarak:
      - scaleFactor ne işe yarar?
      - minNeighbors nedir?

8) Bulunan her yüz için:
      - Rectangle çiz: cv::rectangle(frame, face, Scalar(0,255,0), 2);
      - İstersen yüzün üstüne "Yuz" yazısı koy:
           cv::putText(...)

9) "Yuz Tespiti" adlı pencerede sonucu göster:
      cv::imshow("Yuz Tespiti", frame);

10) 'q' veya 'Q' basılırsa döngüden çık.

11) Döngü bitince:
      cap.release();
      cv::destroyAllWindows();

Aşağıdaki main fonksiyonunu bu maddelere göre doldur:
*/

// #include <iostream>
// #include <opencv2/opencv.hpp>

// int main()
// {
//     // 1) Haar cascade'i yükle

//     // 2) Kamerayı aç

//     // 3) Kamera açılmadıysa çık

//     // 4) Sonsuz döngü

//         // Frame ve gray tanımla

//         // Frame oku, boşsa break

//         // Griye çevir

//         // Histogram eşitle (equalizeHist)

//         // 7) detectMultiScale ile yüzleri bul

//         // 8) Her yüz için rectangle (ve istersen putText) çiz

//         // 9) Göster

//         // 10) 'q' gelirse break

//     // 11) Kaynakları temizle

//     return 0;
// }

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 1) Haar cascade'i yükle
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml"))
    {
        std::cout << "Cascade dosyasi yuklenemedi!" << std::endl;
        return -1;
    }

    // 2) Kamerayı aç
    cv::VideoCapture cap(0);

    // 3) Kamera açılmadıysa çık
    if (!cap.isOpened())
    {
        std::cout << "Kamera acilmadi..." << std::endl;
        return -1;
    }

    while (true)
    {
        cv::Mat frame;
        cv::Mat gray;

        // Frame oku
        cap.read(frame);
        if (frame.empty())
        {
            std::cout << "Frame okunamadi, cikiliyor..." << std::endl;
            break;
        }

        // Griye çevir
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Histogram eşitle
        // Kontrastı biraz toparlayıp yüz tespitini iyileştirir.
        cv::equalizeHist(gray, gray);

        // 7) Yüzleri tespit et
        std::vector<cv::Rect> faces;

        // scaleFactor: her adımda pencereyi ne kadar büyütelim (1.1 -> %10 büyüme)
        // minNeighbors: bir bölgenin yüz sayılması için kaç "pozitif" tespit lazım (gürültüyü azaltır)
        face_cascade.detectMultiScale(
            gray,
            faces,
            1.1,             // scaleFactor
            3,               // minNeighbors
            0,               // flags (genelde 0 bırakılır)
            cv::Size(30, 30) // minSize: en küçük yüz boyutu
        );

        // 8) Bulunan her yüz için rectangle çiz
        for (size_t i = 0; i < faces.size(); ++i)
        {
            cv::Rect face = faces[i];

            // Yeşil dikdörtgen
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);

            // İstersen üstüne "Yuz" yaz
            cv::putText(frame,
                        "Yuz",
                        cv::Point(face.x, face.y - 10),
                        cv::FONT_HERSHEY_SIMPLEX,
                        0.7,
                        cv::Scalar(0, 255, 0),
                        2);
        }

        // 9) Göster
        cv::imshow("Yuz Tespiti", frame);

        // 10) 'q' gelirse çık
        char c = static_cast<char>(cv::waitKey(1));
        if (c == 'q' || c == 'Q')
        {
            break;
        }
    }

    // 11) Kaynakları temizle
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
