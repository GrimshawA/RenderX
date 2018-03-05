//#include <RenderX/RxTexture.h>
//#include <RenderX/RxDevice.h>
//#include <RenderX/Impl/OpenGL/RxTextureGL.h>

//bool RxTextureImpl::copyToImage(Image& image) const
//{
//	return false;
//}

//bool RxTextureImpl::create(unsigned int width, unsigned int height)
//{
//	return false;
//}

//bool RxTextureImpl::loadFromFile(const String& filename)
//{
//	return false;
//}

//void RxTextureImpl::setRepeated(bool repeated)
//{

//}

//void RxTextureImpl::setSmooth(bool smooth)
//{

//}

//bool RxTextureImpl::loadFromImage(const Image& image)
//{
//	return false;
//}

//void RxTextureImpl::update(const uint8_t* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y)
//{

//}

//void RxTextureImpl::update(const uint8_t* pixels)
//{
//}

//void RxTextureImpl::update(const Image& image)
//{
//}

//void RxTextureImpl::generateMips()
//{

//}

////////////////////////////////////////////////////////////////

//RxTexture::RxTexture()
//: _impl(nullptr)
//{
//	//_impl = gGraphicsDevice->createTexture2D();
//}

//RxTexture::~RxTexture()
//{
//	delete _impl;
//}

//void RxTexture::generateMips()
//{
//	_impl->generateMips();
//}

//bool RxTexture::create(std::size_t width, std::size_t height)
//{
//	if (!_impl)
//		_impl = gGraphicsDevice->createTexture2D();

//	return _impl->create(width, height);
//}

//TVector2<int> RxTexture::getSize() const
//{
//	if (_impl)
//		return _impl->getSize();
//	else
//		return TVector2<int>(0, 0);
//}

//bool RxTexture::loadFromFile(const String& filename)
//{
//	if (!_impl)
//		_impl = gGraphicsDevice->createTexture2D();

//	return _impl->loadFromFile(filename);
//}

//void RxTexture::setRepeated(bool repeated)
//{
//	_impl->setRepeated(repeated);
//}

//void RxTexture::setSmooth(bool smooth)
//{
//	_impl->setSmooth(smooth);
//}

//bool RxTexture::loadFromImage(const Image& image)
//{
//	if (!_impl)
//        _impl = RenderCore::instance()->createTexture2D();

//	return _impl->loadFromImage(image);
//}

//void RxTexture::update(const uint8_t* pixels, unsigned int width, unsigned int height, unsigned int x, unsigned int y)
//{
//	_impl->update(pixels, width, height, x, y);
//}

//std::size_t RxTexture::getMaximumSize()
//{
//    return RxTextureGL::getMaximumSize();
//}

//void RxTexture::update(const uint8_t* pixels)
//{
//	_impl->update(pixels);
//}

//void RxTexture::update(const Image& image)
//{
//	_impl->update(image);
//}

//bool RxTexture::copyToImage(Image& image) const
//{
//	return true;
//}

