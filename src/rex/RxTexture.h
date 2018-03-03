#ifndef RENDERXTEXTURE_H__
#define RENDERXTEXTURE_H__

#include <bitcore/Config.h>
#include <bitcore/Vector.h>
#include <bitcore/String.h>
#include <bitcore/Asset.h>

class Image;
class RxTextureImpl;

/**
    \class RxTexture
    \brief Interface for an internal texture resource

	Texture2D is the base class for different two
	dimensional texture implementations. For example,
	DirectX textures are instanced from a DirectX
	DLL from a subclass of Texture2D. A OpenGL
	texture will be subclassed from Texture2D as well and
	instanced appropriately.

	This is so game code can deal with an abstract Texture2D
	object, without worrying about what kind of API will be used
	to render the actual game. This allows for extreme
	flexibility as the games will easily run in new software
	or hardware rendering API's.
	
	By favoring the underlying implementation by composition,
	Texture2D can be extended for more specialized before and
	even swap low level implementation on the fly.
*/
class DAEVA_API RxTexture : public DvAsset
{
public:
	/// Construct the uninitialized texture
    RxTexture();

	/// Ensure destruction of the resource
    virtual ~RxTexture();

	/// Create the texture with the given size
	bool create(std::size_t width, std::size_t height);

	/// Set the texture as repeating for sampling outside its area
	void setRepeated(bool repeated);

	/// Set the texture filtering mode
	void setSmooth(bool smooth);

	void generateMips();

	/// Loads a texture from disk with the global graphics API
	/// Should be avoided in favor of the central asset loading
	bool loadFromFile(const String& filename);

	/// Loads the texture from a image buffer
	/// Should be avoided in favor of the central asset loading
	bool loadFromImage(const Image& image);

	/// Retrieve the texture from the GPU and into an image
	/// Does not work in OpenGL ES platforms. An warning is logged in such platforms.
	/// Returns false if the operation fails
	bool copyToImage(Image& image) const;

	/// A texture is a rectangle, with finite size
	TVector2<int> getSize() const;

	/// Updates a given region inside the texture with an array of pixels
	void update(const uint8_t* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y);

	/// Update the texture on the GPU with an array of pixels
	void update(const uint8_t* pixels);

	/// Update the texture on the GPU from an image
	void update(const Image& image);

	/// Get the maximum size a texture can be
	static std::size_t getMaximumSize();

//private:
    /// The actual texture resource, implemented in a low level renderer
    RxTextureImpl* _impl = nullptr;
};
#endif // RENDERXTEXTURE_H__
