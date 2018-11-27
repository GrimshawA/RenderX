#include "bitmap.hpp"

// If SFML is used, use stb_image as header only because it was already defined
//#if defined NEPHILIM_SFML && defined SFML_STATIC
//#define STBI_HEADER_FILE_ONLY
//#endif

//#if (defined NEPHILIM_SFML && !defined SFML_STATIC) || !defined NEPHILIM_SFML
#define STB_IMAGE_WRITE_IMPLEMENTATION
//#endif

#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"

/*namespace
{
	// stb_image callbacks that operate on a sf::InputStream
	int read(void* user, char* data, int size)
	{
		File* stream = static_cast<File*>(user);
		return static_cast<int>(stream->read(data, size));
	}
	void skip(void* user, unsigned int size)
	{
		File* stream = static_cast<File*>(user);
		stream->seek(stream->tell() + size);
	}
	int eof(void* user)
	{
		File* stream = static_cast<File*>(user);
		return stream->tell() >= stream->getSize();
	}
}*/

namespace rex {

bitmap::bitmap()
    : m_size {0,0}
{

}

bool bitmap::saveToFile(const std::string& path)
{
    return stbi_write_png(path.c_str(), m_size.w, m_size.h, 4, &m_pixels[0], 0) != 0;
}

void bitmap::create(unsigned int width, unsigned int height, const color& color)
{
	// Assign the new size
    m_size.w = width;
    m_size.h = height;

	// Resize the pixel buffer
	m_pixels.resize(width * height * 4);

	// Fill it with the specified color
	uint8_t* ptr = &m_pixels[0];
	uint8_t* end = ptr + m_pixels.size();
	while (ptr < end)
	{
		*ptr++ = color.r;
		*ptr++ = color.g;
		*ptr++ = color.b;
		*ptr++ = color.a;
	}
}

void bitmap::setPixel(unsigned int x, unsigned int y, const color& color)
{
    uint8_t* pixel = &m_pixels[(x + y * m_size.w) * 4];
	*pixel++ = color.r;
	*pixel++ = color.g;
	*pixel++ = color.b;
	*pixel++ = color.a;
}

void bitmap::flip()
{
    bitmap img = *this;
    for (int i = 0; i < m_size.w; ++i)
	{
        for (int j = 0; j < m_size.h; ++j)
		{
            img.setPixel(i, j, getPixel(m_size.w - i - 1, /*m_size.y - j - 1*/j));
		}
	}
	*this = img;
}

bool bitmap::loadFromFile(const std::string &path)
{
    /*File stream(path, IODevice::BinaryRead);
	if(!stream)
	{
	    Log("Image: Invalid path: %s", path.c_str());
	    return false;
    }

	// Setup the stb_image callbacks
	stbi_io_callbacks callbacks;
	callbacks.read = &read;
	callbacks.skip = &skip;
	callbacks.eof  = &eof;

	// Clear the array (just in case)
	m_pixels.clear();

	// Load the image and get a pointer to the pixels in memory
	int width, height, channels;
	//unsigned char* ptr = stbi_load(String(path).c_str(), &width, &height, &channels,STBI_rgb_alpha);
	unsigned char* ptr = stbi_load_from_callbacks(&callbacks, &stream, &width, &height, &channels, STBI_rgb_alpha);

	if (ptr && width && height)
	{
		// Assign the image properties
		m_size.x = width;
		m_size.y = height;

		// Copy the loaded pixels to the pixel buffer
		m_pixels.resize(width * height * 4);
		memcpy(&m_pixels[0], ptr, m_pixels.size());

		// Free the loaded pixels (they are now in our own pixel buffer)
		stbi_image_free(ptr);

		return true;
	}
	else
	{
		// Error, failed to load the image
//		String errorResult = "Failed to load image. \"" + path + "\". Reason : " + stbi_failure_reason();
        //Log("%s", errorResult.c_str());
		return false;
    }*/

	return true;
}

/// Get the color of an individual pixel
color bitmap::getPixel(unsigned int x, unsigned int y)
{
    uint8_t* pixel = &m_pixels[(x + y * m_size.w) * 4];
    color c;
    c.r = *pixel++;
    c.g = *pixel++;
    c.b = *pixel++;
    c.a = *pixel++;
    return c;
}

void bitmap::create(unsigned int width, unsigned int height, const uint8_t* pixels)
{
	m_pixels.resize(width*height*4);
	memcpy(&m_pixels[0], pixels, m_pixels.size());
    m_size.w = width;
    m_size.h = height;
}

size bitmap::getSize() const
{
	return m_size;
}

const uint8_t* bitmap::getPixelsPtr() const
{
	return &m_pixels[0];
}

void bitmap::createMaskFromColor(const color &color, uint8_t alpha)
{
	// Make sure that the image is not empty
	if (!m_pixels.empty())
	{
		// Replace the alpha of the pixels that match the transparent color
		uint8_t* ptr = &m_pixels[0];
		uint8_t* end = ptr + m_pixels.size();
		while (ptr < end)
		{
			if ((ptr[0] == color.r) && (ptr[1] == color.g) && (ptr[2] == color.b) && (ptr[3] == color.a))
				ptr[3] = alpha;
			ptr += 4;
		}
	}
}

}
