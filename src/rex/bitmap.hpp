#ifndef REX_BITMAP_HPP_
#define REX_BITMAP_HPP_

#include <vector>
#include <string>

namespace rex {

class color
{
public:
    int r, g, b, a;
};

class size
{
public:
    int w, h;
};

class bitmap
{
public:
	/// Creates an empty image with size (0,0)
    bitmap();

	/// Attempts to save the image buffer in a file
    bool saveToFile(const std::string& path);

	/// Attempts to load an image from a file
    bool loadFromFile(const std::string &path);

	void flip();

	/// Set the color of an individual pixel
    void setPixel(unsigned int x, unsigned int y, const color& color);

	/// Get the color of an individual pixel
    color getPixel(unsigned int x, unsigned int y);

	/// Get the size of the image
    size getSize() const;

	/// Sets the desired transparency on all pixels with the selected color
    void createMaskFromColor(const color &color, uint8_t alpha = 0);

	/// Creates or recreates the image with a selected fill color
    void create(unsigned int width, unsigned int height, const color& color);

	/// Creates or recreates the image from a pixel array
	void create(unsigned int width, unsigned int height,const uint8_t* pixels);

	/// Get the raw array of pixels
	const uint8_t* getPixelsPtr() const;

private:
	std::vector<uint8_t> m_pixels; ///< The dynamic array of pixels
    size m_size;
};
}

#endif // REX_BITMAP_HPP_
