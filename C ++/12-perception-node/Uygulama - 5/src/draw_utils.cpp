#include "draw_utils.hpp"

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <sstream>

void draw_detections(cv::Mat& frame, const DetectionList& dets)
{
    for (const auto& d : dets)
    {
        cv::Rect rect(
            static_cast<int>(d.x1),
            static_cast<int>(d.y1),
            static_cast<int>(d.x2 - d.x1),
            static_cast<int>(d.y2 - d.y1)
        );

        cv::rectangle(frame, rect, cv::Scalar(0, 255, 0), 2);

        std::ostringstream ss;
        ss << "id:" << d.class_id << " s:" << d.score;

        cv::putText(frame,
                    ss.str(),
                    cv::Point(rect.x, rect.y - 5),
                    cv::FONT_HERSHEY_SIMPLEX,
                    0.5,
                    cv::Scalar(0, 255, 0),
                    1);
    }
}
