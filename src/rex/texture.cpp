#include "texture.hpp"

namespace rex {

//bool rex::textureImpl::copyToImage(Image& image) const
//{
//    return false;
//}

//bool rex::textureImpl::create(unsigned int width, unsigned int height)
//{
//    return false;
//}

//bool rex::textureImpl::loadFromFile(const String& filename)
//{
//    return false;
//}

//void rex::textureImpl::setRepeated(bool repeated)
//{

//}

//void rex::textureImpl::setSmooth(bool smooth)
//{

//}

//bool rex::textureImpl::loadFromImage(const Image& image)
//{
//    return false;
//}

//void rex::textureImpl::update(const uint8_t* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y)
//{

//}

//void rex::textureImpl::update(const uint8_t* pixels)
//{
//}

//void rex::textureImpl::update(const Image& image)
//{
//}

//void rex::textureImpl::generateMips()
//{

//}

//////////////////////////////////////////////////////////////

texture::texture()
{
}

texture::~texture()
{
}

//void texture::generateMips()
//{
//    _impl->generateMips();
//}

//bool texture::create(std::size_t width, std::size_t height)
//{
//    if (!_impl)
//        _impl = gGraphicsDevice->createTexture2D();

//    return _impl->create(width, height);
//}

//TVector2<int> texture::getSize() const
//{
//    if (_impl)
//        return _impl->getSize();
//    else
//        return TVector2<int>(0, 0);
//}

//bool texture::loadFromFile(const String& filename)
//{
//    if (!_impl)
//        _impl = gGraphicsDevice->createTexture2D();

//    return _impl->loadFromFile(filename);
//}

//void texture::setRepeated(bool repeated)
//{
//    _impl->setRepeated(repeated);
//}

//void texture::setSmooth(bool smooth)
//{
//    _impl->setSmooth(smooth);
//}

//bool texture::loadFromImage(const Image& image)
//{
//    if (!_impl)
//        _impl = RenderCore::instance()->createTexture2D();

//    return _impl->loadFromImage(image);
//}

//void texture::update(const uint8_t* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y)
//{
//    _impl->update(pixels, width, height, x, y);
//}

//std::size_t texture::getMaximumSize()
//{
//    return rex::textureGL::getMaximumSize();
//}

//void texture::update(const uint8_t* pixels)
//{
//    _impl->update(pixels);
//}

//void texture::update(const Image& image)
//{
//    _impl->update(image);
//}

//bool texture::copyToImage(Image& image) const
//{
//    return true;
//}

}

