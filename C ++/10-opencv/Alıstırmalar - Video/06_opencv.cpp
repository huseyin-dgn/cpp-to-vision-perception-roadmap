/*
🧩 SORU 7 — CANLI AKIŞTA YÜZ VE GÖZ TESPİTİ

Görevlerin:

1) İki tane cascade yükle:
   - Yüz için:  haarcascade_frontalface_default.xml
   - Göz için:  haarcascade_eye.xml

2) Cascade'ler yüklenemezse ekrana hata bas ve programı bitir.

3) Kamerayı aç (VideoCapture cap(0)) ve açılmazsa çık.

4) Sonsuz döngü başlat:
      while (true) { ... }

5) Döngü içinde:
      - Kameradan frame oku
      - Frame boşsa break;

6) Frame'i griye çevir ve equalizeHist uygula.

7) Yüzleri tespit et (detectMultiScale ile):
      std::vector<cv::Rect> faces;

8) Her yüz için:
      - Yüz dikdörtgenini çiz (rectangle)
      - Yüz bölgesi için ROI çıkar:
            cv::Mat faceROI = gray(faceRect);

      - Bu ROI içinde gözleri tespit et:
            std::vector<cv::Rect> eyes;
            eye_cascade.detectMultiScale(...)

      - Her göz için:
            - Gözün merkezini hesapla (faceRect offset'ini ekleyerek)
            - Merkezde küçük bir daire çiz (circle)

9) Sonuç frame'ini "Yuz + Goz Tespiti" penceresinde göster.

10) 'q' veya 'Q' basılırsa döngüden çık.

11) cap.release() + destroyAllWindows() ile temizle.

Aşağıdaki main fonksiyonunu bu adımlara göre doldur:
*/

// int main()
// {
//     // 1) Cascade'leri oluştur ve yükle

//     // 2) Yüklenemezse hata ver ve çık

//     // 3) Kamerayı aç

//     // 4) Kamera açılmadıysa çık

//     // 5) Sonsuz döngü

//         // Frame ve gray tanımla

//         // Frame oku, boşsa break

//         // Griye çevir + equalizeHist

//         // 7) Yüzleri tespit et (faces vector)

//         // 8) Her yüz için:
//         //    - rectangle ile yüzü çiz
//         //    - ROI çıkar (faceROI)
//         //    - eye_cascade ile gözleri bul
//         //    - göz merkezlerine daire çiz

//         // 9) Sonuç frame'ini göster

//         // 10) 'q' gelirse break

//     // 11) Kaynakları temizle

//     return 0;
// }

#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
      // 1) Cascade'leri oluştur
      cv::CascadeClassifier face_cascade;
      cv::CascadeClassifier eye_cascade;

      // 2) Yüz cascade'ini yükle
      if (!face_cascade.load("haarcascade_frontalface_default.xml"))
      {
            std::cout << "Yuz cascade dosyasi yuklenemedi!" << std::endl;
            return -1;
      }

      // 2) Göz cascade'ini yükle
      if (!eye_cascade.load("haarcascade_eye.xml"))
      {
            std::cout << "Goz cascade dosyasi yuklenemedi!" << std::endl;
            return -1;
      }

      // 3) Kamerayı aç
      cv::VideoCapture cap(0);

      // 4) Kamera açılmadıysa çık
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

            // Histogram eşitle (kontrastı düzeltir)
            cv::equalizeHist(gray, gray);

            // 7) Yüzleri tespit et
            std::vector<cv::Rect> faces;
            face_cascade.detectMultiScale(
                gray,
                faces,
                1.1, // scaleFactor
                3,   // minNeighbors
                0,
                cv::Size(30, 30) // minSize
            );

            // 8) Her yüz için
            for (size_t i = 0; i < faces.size(); ++i)
            {
                  cv::Rect faceRect = faces[i];

                  // Yüzün etrafına yeşil dikdörtgen
                  cv::rectangle(frame, faceRect, cv::Scalar(0, 255, 0), 2);

                  // Yüz bölgesinin ROI'sini al (göz aramayı sadece burada yap)
                  cv::Mat faceROI = gray(faceRect);

                  // Gözleri tespit et
                  std::vector<cv::Rect> eyes;
                  eye_cascade.detectMultiScale(
                      faceROI,
                      eyes,
                      1.1, // scaleFactor
                      3,   // minNeighbors
                      0,
                      cv::Size(15, 15) // minSize (gözler için daha küçük)
                  );

                  // Her göz için daire çiz
                  for (size_t j = 0; j < eyes.size(); ++j)
                  {
                        cv::Rect eyeRect = eyes[j];

                        // Gözün merkezini hesapla (faceRect offset'i ile birlikte)
                        cv::Point eye_center(
                            faceRect.x + eyeRect.x + eyeRect.width / 2,
                            faceRect.y + eyeRect.y + eyeRect.height / 2);

                        int radius = cvRound((eyeRect.width + eyeRect.height) * 0.25);

                        // Mavi daire (BGR: 255,0,0)
                        cv::circle(frame, eye_center, radius, cv::Scalar(255, 0, 0), 2);
                  }
            }

            // 9) Sonuç frame'ini göster
            cv::imshow("Yuz + Goz Tespiti", frame);

            // 10) 'q' gelirse break
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
