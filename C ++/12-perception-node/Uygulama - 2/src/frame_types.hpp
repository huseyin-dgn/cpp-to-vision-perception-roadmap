#ifndef FRAME_TYPES_HPP
#define FRAME_TYPES_HPP

#include <opencv2/core.hpp>
#include <cstdint>
#include <string>

// Tek bir görüntü karesini temsil eder.
struct ImageFrame
{
    cv::Mat image;             // Ham görüntü
    std::uint64_t frame_id{0}; // Frame numarası / id
    std::string source_name;   // Kaynak adı (örn: "file:test.jpg")

    ImageFrame() = default;

    ImageFrame(const cv::Mat &img,
               std::uint64_t id,
               const std::string &source)
        : image(img),
          frame_id(id),
          source_name(source)
    {
    }
};

#endif // FRAME_TYPES_HPP
