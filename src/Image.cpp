#include "Image.h"
#include <format>
#include <stb_image.h>

ImageUPtr Image::load(const std::filesystem::path& fileName)
{
    int width = 0;
    int height = 0;
    int numChannels = 0;

    if (auto pixels = stbi_load(fileName.string().c_str(), &width, &height, &numChannels, 0)) {
        return ImageUPtr(new Image(pixels, width, height, numChannels));
    }

    throw std::runtime_error(std::format("Cannnot load image {}", fileName.string()));
}

Image::Image(std::uint8_t* pixels, int width, int height, int numChannels)
   : m_pixels(pixels)
   , m_width(width)
   , m_height(height)
   , m_numChannels(numChannels)
{}

void Image::PixelsDeleter::operator()(std::uint8_t* pixels) const
{
    stbi_image_free(pixels);
}

const std::uint8_t* Image::pixels() const
{
    return m_pixels.get();
}

size_t Image::width() const
{
    return m_width;
}

size_t Image::height() const
{
    return m_height;
}

size_t Image::numChannels() const
{
    return m_numChannels;
}