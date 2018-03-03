#ifndef DaevaRenderCoreInterfaces_h__
#define DaevaRenderCoreInterfaces_h__

#include <bitcore/Config.h>
#include <bitcore/Vector.h>
#include <bitcore/String.h>

#include <vector>

class Image;

/**
\class GDI_Texture2D
\brief Interface for implementing regular textures
*/
class DAEVA_API RxTextureImpl
{
public:

    /// Create or recreate the texture with a given size
    virtual bool create(unsigned int width, unsigned int height);

    /// Retrieve the texture from the GPU and into an image
    /// Does not work in OpenGL ES platforms. An warning is logged in such platforms.
    /// Returns false if the operation fails
    virtual bool copyToImage(Image& image) const;

    /// Get the texture rectangle size
    virtual TVector2<int> getSize() const = 0;

    /// Loads the texture from disk
    virtual bool loadFromFile(const String& filename);

    /// Loads the texture from a image buffer
    virtual bool loadFromImage(const Image& image);

    /// Sets the texture repeat mode
    virtual void setRepeated(bool repeated);

    /// Set the texture filtering mode
    virtual void setSmooth(bool smooth);

    /// Updates a given region inside the texture with an array of pixels
    virtual void update(const uint8_t* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y);

    /// Update the texture on the GPU with an array of pixels
    virtual void update(const uint8_t* pixels);

    /// Update the texture on the GPU from an image
    virtual void update(const Image& image);

    virtual void generateMips();
};

/**
    \class GDI_VertexBuffer
    \brief Abstract interface for handling on-gpu geometry buffers
*/
class DAEVA_API RxVertexBufferImpl
{
public:

    struct FVertexComponent
    {
        int numElements;
        int size;
        int stride;
    };

    struct FVertexFormat
    {
        std::vector<FVertexComponent> attributes;
    };

    FVertexFormat format;
};

namespace detail
{
	/**
	\class GDI_TextureCubemap
	\brief Interface for implementing cubemap textures
	*/
	class DAEVA_API GDI_CubeTexture
	{
	public:

	};

	/**
	\class GDI_Texture3D
	\brief Interface for implementing 3D textures on any graphics API
	*/
	class DAEVA_API GDI_Texture3D
	{
	public:

    };

	/**
	\class GDI_IndexBuffer
	\brief Abstract interface for handling on-gpu index buffers
	*/
	class DAEVA_API GDI_IndexBuffer
	{
	public:

	};

};
#endif // DaevaRenderCoreInterfaces_h__
