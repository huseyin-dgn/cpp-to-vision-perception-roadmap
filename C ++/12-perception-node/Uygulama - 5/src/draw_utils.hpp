#ifndef DRAW_UTILS_HPP
#define DRAW_UTILS_HPP

#include "detection_types.hpp"

#include <opencv2/core.hpp>

void draw_detections(cv::Mat& frame, const DetectionList& dets);

#endif // DRAW_UTILS_HPP
