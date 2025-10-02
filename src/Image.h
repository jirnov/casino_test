#pragma once

#include "Forward.h"
#include <memory>

class Image {
public:
    static ImageUPtr load(const std::string& fileName);

    const std::uint8_t* pixels() const;
    size_t width() const;
    size_t height() const;
    size_t numChannels() const;

private:
    Image(std::uint8_t* pixels, int width, int height, int numChannels);

    struct PixelsDeleter {
        void operator()(std::uint8_t* pixels) const;
    };

    std::unique_ptr<std::uint8_t[], PixelsDeleter> m_pixels;
    size_t m_width;
    size_t m_height;
    size_t m_numChannels;
};