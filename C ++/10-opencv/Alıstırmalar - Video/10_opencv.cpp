/*
🧩 SORU 11 — CANLI AKIŞTA MOUSE İLE ROI SEÇİMİ

Amaç:
- "Kamera" penceresinde canlı görüntü akarken,
- Fare ile tıklayıp sürükleyerek bir dikdörtgen (ROI) seç,
- Mouse'u bıraktığında bu ROI'yi kes (crop) edip "ROI" penceresinde göster.

Görevlerin:

1) Global veya static bazı değişkenlere ihtiyacımız var:
   - cv::Rect g_roi;
   - bool g_drawing = false;
   - cv::Point g_startPoint;

2) Bir mouse callback fonksiyonu yaz:
   void onMouse(int event, int x, int y, int flags, void* userdata)
   {
       - event == EVENT_LBUTTONDOWN:
            g_drawing = true;
            g_startPoint = (x, y);
            g_roi = Rect(x, y, 0, 0);

       - event == EVENT_MOUSEMOVE ve g_drawing == true ise:
            g_roi.width  = x - g_startPoint.x;
            g_roi.height = y - g_startPoint.y;
            (negatif durumlar için istersen normalize edebilirsin)

       - event == EVENT_LBUTTONUP:
            g_drawing = false;
            g_roi.width  = x - g_startPoint.x;
            g_roi.height = y - g_startPoint.y;
   }

3) main içinde:
   - Kamerayı aç (VideoCapture cap(0))
   - "Kamera" penceresini oluştur (namedWindow)
   - setMouseCallback("Kamera", onMouse, nullptr);

4) Sonsuz döngüde:
   - Kameradan frame oku, boşsa break
   - frame'i kopyala: cv::Mat display = frame.clone();

   - Eğer g_drawing veya g_roi genişliği/yüksekliği > 0 ise:
        - cv::Rect roiNorm = g_roi;
        - ROI dikdörtgenini normalize et (genişlik negatifse düzelt vs.)
        - display üzerine rectangle çiz (yeşil)

   - display'i "Kamera" penceresinde göster.

   - Eğer g_drawing == false ve g_roi geçerli boyuttaysa:
        - Aynı normalize edilmiş Rect ile frame içinden crop al:
              cv::Mat roi = frame(roiRect).clone();
        - "ROI" penceresinde göster.

   - 'q' veya 'Q' basılırsa break.

5) Döngü bitince:
   - cap.release();
   - destroyAllWindows();

Not:
- Rect negatif genişlik/yükseklik üretebileceği için normalize etmek gerekir:
      int x1 = min(g_startPoint.x, x);
      int y1 = min(g_startPoint.y, y);
      int x2 = max(g_startPoint.x, x);
      int y2 = max(g_startPoint.y, y);
      g_roi = Rect(x1, y1, x2 - x1, y2 - y1);
*/

#include <iostream>
#include <opencv2/opencv.hpp>

// 1) Global değişkenleri burada tanımlayacağız

// 2) Mouse callback fonksiyonunu burada yazacağız

// int main()
// {
//     // 3) Kamerayı aç, pencereyi ve mouse callback'i ayarla

//     // 4) Sonsuz döngü: frame oku, ROI dikdörtgenini çiz, ROI'yi ayrı pencerede göster

//     // 5) Kaynakları temizle

//     return 0;
// }

#include <iostream>
#include <opencv2/opencv.hpp>

// 1) Global değişkenler
cv::Rect g_roi;
bool g_drawing = false;
cv::Point g_startPoint;

// Mouse callback fonksiyonu
void onMouse(int event, int x, int y, int flags, void *userdata)
{
    switch (event)
    {
    case cv::EVENT_LBUTTONDOWN:
        // Sol tuşa basıldığında çizim başlasın
        g_drawing = true;
        g_startPoint = cv::Point(x, y);
        g_roi = cv::Rect(x, y, 0, 0);
        break;

    case cv::EVENT_MOUSEMOVE:
        if (g_drawing)
        {
            // Çizerken dinamik olarak ROI güncelle
            int x1 = std::min(g_startPoint.x, x);
            int y1 = std::min(g_startPoint.y, y);
            int x2 = std::max(g_startPoint.x, x);
            int y2 = std::max(g_startPoint.y, y);

            g_roi = cv::Rect(x1, y1, x2 - x1, y2 - y1);
        }
        break;

    case cv::EVENT_LBUTTONUP:
        // Sol tuş bırakıldığında çizimi bitir
        g_drawing = false;
        {
            int x1 = std::min(g_startPoint.x, x);
            int y1 = std::min(g_startPoint.y, y);
            int x2 = std::max(g_startPoint.x, x);
            int y2 = std::max(g_startPoint.y, y);

            g_roi = cv::Rect(x1, y1, x2 - x1, y2 - y1);
        }
        break;

    default:
        break;
    }
}

int main()
{
    // 3) Kamerayı aç
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cout << "Kamera acilmadi..." << std::endl;
        return -1;
    }

    // Pencereyi oluştur ve mouse callback'i bağla
    cv::namedWindow("Kamera");
    cv::setMouseCallback("Kamera", onMouse, nullptr);

    while (true)
    {
        cv::Mat frame;
        cap.read(frame);
        if (frame.empty())
        {
            std::cout << "Frame okunamadi, cikiliyor..." << std::endl;
            break;
        }

        // Ekranda göstermek için bir kopya al
        cv::Mat display = frame.clone();

        // ROI dikdörtgeni geçerliyse çiz
        if (g_roi.width > 0 && g_roi.height > 0)
        {
            cv::rectangle(display, g_roi, cv::Scalar(0, 255, 0), 2);

            // Sadece seçim bittikten sonra (mouse bırakıldıktan sonra) ROI'yi gösterelim
            if (!g_drawing)
            {
                // ROI frame sınırları içindeyse crop al
                cv::Rect roiSafe = g_roi & cv::Rect(0, 0, frame.cols, frame.rows);
                if (roiSafe.width > 0 && roiSafe.height > 0)
                {
                    cv::Mat roi = frame(roiSafe).clone();
                    cv::imshow("ROI", roi);
                }
            }
        }

        // Kamerayı göster
        cv::imshow("Kamera", display);

        // 'q' gelirse çık
        char c = static_cast<char>(cv::waitKey(1));
        if (c == 'q' || c == 'Q')
        {
            break;
        }
    }

    // 5) Kaynakları temizle
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
