#ifndef DETECTION_TYPES_HPP
#define DETECTION_TYPES_HPP

#include <vector>

struct DetectedObject
{
    int class_id{-1};
    float score{0.0f};
    float x1{0.0f};
    float y1{0.0f};
    float x2{0.0f};
    float y2{0.0f};
};

using DetectionList = std::vector<DetectedObject>;

#endif // DETECTION_TYPES_HPP
