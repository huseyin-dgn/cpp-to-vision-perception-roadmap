#ifndef FRAME_TYPES_HPP
#define FRAME_TYPES_HPP

#include <opencv2/core.hpp>
#include <cstdint>
#include <string>

// Tek bir görüntü karesini temsil eden basit yapı
struct ImageFrame
{
    cv::Mat image;              // Görüntü verisi
    std::uint64_t frame_id{0};  // Frame kimliği
    std::string source_name;    // Kaynak (örn: "file:cat.png")

    ImageFrame() = default;

    ImageFrame(const cv::Mat& img,
               std::uint64_t id,
               const std::string& source)
        : image(img),
          frame_id(id),
          source_name(source)
    {}
};

#endif // FRAME_TYPES_HPP
