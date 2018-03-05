//#include <RenderX/RxShader.h>
//#include <RenderX/RxDevice.h>
//#include <RenderX/RxInterfaces.h>

//Shader::Shader()
//: m_impl(nullptr)
//{
//	//m_impl = gGraphicsDevice->createShader();
//}

//Shader::Shader(const Shader& other)
//{
//	m_impl = other.m_impl;
//	m_impl->refCount++;
//}

//Shader::~Shader()
//{
//    release();
//}

//void Shader::load(const std::vector<ShaderSource>& sources)
//{
//    if (m_impl)
//        m_impl->load(sources);
//}

//Shader& Shader::operator=(const Shader& other)
//{
//	if (m_impl != other.m_impl)
//	{
//		release();
//		m_impl = other.m_impl;
//		m_impl->refCount++;
//	}
//	return *this;
//}

//void Shader::release()
//{
//	if (m_impl && --m_impl->refCount == 0)
//	{
//		// Destroy the resource
//	}
//}
