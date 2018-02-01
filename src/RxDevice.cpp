#include <RenderX/RxDevice.h>
#include <bitgraphics/Window.h>
#include <bitgraphics/API.h>
#include <RenderX/OpenGL/GLHelpers.h>
#include <RenderX/OpenGL/GLVertexBuffer.h>

#include <bitcore/Logger.h>
#include <bitgraphics/Drawable.h>
#include <bitcore/Bitmap.h>

#include <RenderX/RxVertexArray.h>
#include <RenderX/RxIndexArray.h>

#include <RenderX/Impl/OpenGL/RxTextureGL.h>

/// Global instance of graphics device, for the global calls
RenderCore* gGraphicsDevice = nullptr;

RenderCore* RenderCore::currentContext = nullptr;


RenderCore::RenderCore()
: m_type(Other)
, m_shaderUsageHint(true)
, mVertexBuffer(nullptr)
, mIndexBuffer(nullptr)
, m_activeShader(nullptr)
{

	gfx_device = this;
	// Let's make sure the global device is up to date
	gGraphicsDevice = this;

	setInstance(this);

	m_model.resize(1);

	m_primitiveTable[Render::Primitive::Triangles] = static_cast<int>(GL_TRIANGLES);
	m_primitiveTable[Render::Primitive::TriangleFan] = static_cast<int>(GL_TRIANGLE_FAN);
	m_primitiveTable[Render::Primitive::TriangleStrip] = static_cast<int>(GL_TRIANGLE_STRIP);
	m_primitiveTable[Render::Primitive::Lines] = static_cast<int>(GL_LINES);
	m_primitiveTable[Render::Primitive::LineLoop] = static_cast<int>(GL_LINE_LOOP);
	m_primitiveTable[Render::Primitive::Points] = static_cast<int>(GL_POINTS);
	m_primitiveTable[Render::Primitive::LineStrip] = static_cast<int>(GL_LINE_STRIP);

	setClearColor(Color::Orange);
}

RenderCore::~RenderCore()
{

}

RenderCore* RenderCore::instance()
{
	return currentContext;
	return gGraphicsDevice;
}

void RenderCore::setInstance(RenderCore* inst)
{
	gGraphicsDevice = inst;
	currentContext = inst;
}

void RenderCore::init()
{
	Image whiteTexture;
	whiteTexture.create(1, 1, Color::White);
    m_defaultTexture = new RxTexture;
    m_defaultTexture->_impl = createTexture2D();
    m_defaultTexture->_impl->loadFromImage(whiteTexture);
}

const char* RenderCore::getAdapterName()
{
	return "null";
}

RxTextureImpl* RenderCore::createTexture2D()
{
	return nullptr;
}

RxFramebufferImpl* RenderCore::createFramebuffer()
{
	return nullptr;
}


RxVertexBufferImpl* RenderCore::createVertexBuffer(){ return nullptr; }
GDI_IndexBuffer*  RenderCore::createIndexBuffer(){ return nullptr; }
void              RenderCore::destroyVertexBuffer(RxVertexBufferImpl* buffer){}
void              RenderCore::destroyIndexBuffer(GDI_IndexBuffer* buffer){}

// -- Unimplemented API at Renderer level
void RenderCore::setDefaultShader(){}

void RenderCore::setShader(detail::GDI_ShaderProgram* shader)
{
}

RenderCore::Type RenderCore::getType()
{
	return m_type;
}

/// Get the full name of this renderer
String RenderCore::getName()
{
	return m_name;
}

DvWindow* RenderCore::getWindow()
{
	return m_window;
}

void RenderCore::setClearColor(const Color& color)
{
	m_clearColor = color;
	vec4 c = m_clearColor.normalized();
	glClearColor(c.x, c.y, c.z, c.w);
}

/// Set an hint to the renderer which tells it to prefer shaders by default(true), or to use the fixed pipeline instead
/// By default, it means a direction relation with setDefaultShader(). Applies only to platforms with both options available.
void RenderCore::setShaderUsageHint(bool allow)
{
	m_shaderUsageHint = allow;
}

/// Get a current renderer-global matrix
mat4 RenderCore::getProjectionMatrix()
{
	return m_projection;
}

/// Get a current renderer-global matrix
mat4 RenderCore::getViewMatrix()
{
	return m_view;
}

/// Get a current renderer-global matrix
mat4 RenderCore::getModelMatrix()
{
	return m_model[m_model.size() - 1];
}

/// Push client-side geometry to the GPU
/// This is usually slower than using a VBO because the data is uploaded to the GPU every time
void RenderCore::draw(const RxVertexArray& vertexData)
{
}

/// Get the current clear color
Color RenderCore::getClearColor()
{
	return m_clearColor;
}

void RenderCore::setTarget(RenderTarget& target)
{
	//m_window = &target;
	//m_window->activate();
}

void RenderCore::setDefaultTransforms()
{
	setProjectionMatrix(mat4::identity);
	setViewMatrix(mat4::identity);
	setModelMatrix(mat4::identity);
}

void RenderCore::setDefaultViewport()
{
	setViewport(0.f, 0.f, 1.f, 1.f);
}

/// Set the viewport in target-relative coordinates
/// If you want to set the viewport in pixels, use setViewportInPixels()
void RenderCore::setViewport(float left, float top, float width, float height)
{
	int bottom = m_window->size().y - (top*m_window->size().y + height*m_window->size().y);
	glViewport(left * m_window->size().x, bottom, width * m_window->size().x, height * m_window->size().y);
}

/// Set the viewport as in glViewport()
void RenderCore::setViewportInPixels(int left, int top, int width, int height)
{
	int bottom = m_window->size().y - (top + height);
	glViewport(left, bottom, width, height);
	glViewport(left, top, width, height);
}

/// Activates blending with the default mode: Alpha
void RenderCore::setDefaultBlending()
{
	setBlendMode(Render::Blend::Alpha);
	glBlendEquation(GL_FUNC_ADD);
}

void RenderCore::reloadDefaultShader()
{
}

void RenderCore::setBlendMode(Render::Blend::Mode mode)
{
	setBlendingEnabled(true);

	switch(mode)
	{
		case Render::Blend::Add:
		{
			glBlendFunc(GL_ONE, GL_ONE);
		}
		break;

		case Render::Blend::AddAlpha:
			{
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);				
			}
			break;

		case Render::Blend::Multiply:
		{
			glBlendFunc(GL_DST_COLOR, GL_ZERO);
		}
		break;

		case Render::Blend::Alpha:
		{
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		break;

		case Render::Blend::None:
		{
			glBlendFunc (GL_ONE, GL_ZERO);
		}
		break;

		case Render::Blend::PreMultBlend:
		{
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		}
		break;
	}
}

void RenderCore::setBlendingEnabled(bool enable)
{
	if(enable) glEnable(GL_BLEND);
	else		glDisable(GL_BLEND);
}

void RenderCore::setDefaultTarget()
{
	glBindFramebufferCGL(GL_FRAMEBUFFER_CGL, 0);
	m_window->setActive(true);
}

void RenderCore::setVertexBuffer(RxVertexBufferImpl* vertexBuffer)
{
	/*mVertexBuffer = vertexBuffer;

	if (vertexBuffer)
	{
		static_cast<GLVertexBuffer*>(vertexBuffer)->bind();
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}*/
}

void RenderCore::setClippingEnabled(bool enable)
{
	if(enable) glEnable (GL_SCISSOR_TEST);
	else       glDisable(GL_SCISSOR_TEST);
}

/// Resets the scissor clipping rectangle to the full target
void RenderCore::resetClippingRect()
{

}

/// Set the scissor clipping rectangle, it cannot exceed the current rectangle
/// You can only request a sub-region of the current clipping area, unless you call resetClippingRect() first
void RenderCore::setClippingRect(FloatRect rect)
{
	glScissor(rect.left, m_window->size().y - (rect.top + rect.height), rect.width, rect.height);
}

void RenderCore::pushClippingRect(FloatRect rect, bool isNormalized)
{
	setClippingEnabled(true);

	// If its normalized, convert back to pixels for the calculations
	if(isNormalized)
	{
        //rect.left *= getWindow()->width();
        //rect.width *= getWindow()->width();
        //rect.top *= getWindow()->height();
        //rect.height *= getWindow()->height();
	}

	FloatRect finalRect;

	/*if(m_scissorStack.empty())
	{
		// compare against the full window size
		finalRect = FloatRect(0, 0, m_window->getSize().x, m_window->getSize().y);
	}
	else
	{
		// compare against the previous scissor test
		finalRect = m_scissorStack.top();
	}*/

	// Crop rect if needed and push
	if(rect.left < finalRect.left)
	{
		rect.width = rect.width - finalRect.left - rect.left;
		rect.left = finalRect.left;
	}
	if(rect.top < finalRect.top)
	{
		rect.height = rect.height - finalRect.top - rect.top;
		rect.top = finalRect.top;
	}
	if(rect.left + rect.width > finalRect.left + finalRect.width)
	{
		rect.width = finalRect.left + finalRect.width - rect.left;
	}
	if(rect.top + rect.height > finalRect.top + finalRect.height)
	{
		rect.height = finalRect.top + finalRect.height - rect.top;
	}	

	// Push the final approved rect to the stack
	//m_scissorStack.push(rect);

	// Activate the nested scissor region already cut
	setClippingRect(rect);
}

void RenderCore::popClippingRect()
{
	/*if (!m_scissorStack.empty())
	m_scissorStack.pop();

	if(m_scissorStack.empty())
		setClippingEnabled(false);*/
}

void RenderCore::setDepthTestEnabled(bool enable)
{
	if(enable) glEnable(GL_DEPTH_TEST);
	else       glDisable(GL_DEPTH_TEST);
}

void RenderCore::clearDepthBuffer()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void RenderCore::clearStencilBuffer()
{
	glClear(GL_STENCIL_BUFFER_BIT);
}

void RenderCore::clearColorBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void RenderCore::clearAllBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

/// Set the default depth test mode: false
void RenderCore::setDefaultDepthTesting()
{
	setDepthTestEnabled(false);
}

void RenderCore::setDefaultTexture()
{
	glActiveTexture(GL_TEXTURE0);
	setTexture(m_defaultTexture);
}

/// Draw a debug quad with the given color,angle and dimensions - slow
void RenderCore::drawDebugQuad(float x, float y, float angle, float width, float height, Color color)
{
	Transform2 vtransform;
	vtransform.rotate(angle);
	vtransform.translate(x,y);

	mat4 translation = mat4::translate(x,y,0);

	VertexArray2D varray(Render::Primitive::Triangles, 6);
	varray[0].position = Vector2(width/2,-height/2);
	varray[1].position = Vector2(-width/2,height/2);
	varray[2].position = Vector2(-width/2,-height/2);
	varray[3].position = Vector2(width/2,-height/2);
	varray[4].position = Vector2(width/2,height/2);
	varray[5].position = Vector2(-width/2, height/2);

	varray[0].color = color;
	varray[1].color = color;
	varray[2].color = color;
	varray[3].color = color;
	varray[4].color = color;
	varray[5].color = color;

	for(int i = 0; i < 6; i++)
	{
		varray[i].position = vec4(translation * vec4(varray[i].position.x, varray[i].position.y, 0.f, 1.f)).xy();
	}

	draw(varray);
}

/// Draw a debug line with the given color - slow
void RenderCore::drawDebugLine(Vector2 begin, Vector2 end, Color color)
{
	VertexArray2D varray(Render::Primitive::Lines, 2);
	varray[0].position = begin;
	varray[1].position = end;

	varray[0].color = color;
	varray[1].color = color;

	draw(varray);
}

bool RenderCore::readPixels(Image& image)
{
	int width = static_cast<int>(m_window->size().x);
	int height = static_cast<int>(m_window->size().y);

	// copy rows one by one and flip them (OpenGL's origin is bottom while SFML's origin is top)
	std::vector<uint8_t> pixels(width * height * 4);
	for (int i = 0; i < height; ++i)
	{
		uint8_t* ptr = &pixels[i * width * 4];
		glReadPixels(0, height - i - 1, width, 1, GL_RGBA, GL_UNSIGNED_BYTE, ptr);
	}

	image.create(width, height, &pixels[0]);

	return false;
}

void RenderCore::setFramebuffer(RxFramebuffer* fbuffer)
{

}

/// Orders the renderer to reload the default texture etc
void RenderCore::reloadResources()
{
	reloadDefaultShader();

	Image whiteTexture;
	whiteTexture.create(1,1,Color::White);

	m_defaultTexture->loadFromImage(whiteTexture);
}

/// Draw a debug circle with the given color and radius - slow
void RenderCore::drawDebugCircle(Vector2 center, float radius, Vector2 axis, Color color)
{
	VertexArray2D varray(Render::Primitive::TriangleFan, 0);
	const float k_segments = 32.0f;
	const float k_increment = 2.0f * 3.14159 / k_segments;
	float theta = 0.0f;

	for (int i = 0; i < k_segments; ++i)
	{
		Vector2 v = center + Vector2(cosf(theta), sinf(theta)) * radius;
		theta += k_increment;
		varray.append(VertexArray2D::Vertex(v, color, Vector2()));
	}
	
	/*theta = 0.0f;
	glColor4ub(color.r, color.g, color.b, color.a);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < k_segments; ++i)
	{
		Vector2 v = center + Vector2(cosf(theta), sinf(theta)) * radius;
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}
	glEnd();*/

	draw(varray);
}

void RenderCore::drawArrays(Render::Primitive::Type primitiveType, int start, int count)
{
	glDrawArrays(static_cast<GLenum>(m_primitiveTable[primitiveType]), static_cast<GLint>(start), static_cast<GLsizei>(count));
}

void RenderCore::enableVertexAttribArray(unsigned int index)
{
	glEnableVertexAttribArray(static_cast<GLuint>(index));
}

void RenderCore::disableVertexAttribArray(unsigned int index)
{
	glDisableVertexAttribArray(static_cast<GLuint>(index));
}

void RenderCore::setVertexAttribPointer(unsigned int index, int numComponents, int componentType, bool normalized, int stride, const void* ptr)
{
	glVertexAttribPointer(static_cast<GLuint>(index), static_cast<GLint>(numComponents), static_cast<GLenum>(componentType), static_cast<GLboolean>(normalized), static_cast<GLsizei>(stride), static_cast<const GLvoid*>(ptr));
}

void RenderCore::draw(const VertexArray2D& varray)
{
	Log("Why are you calling draw on an abstract base class?");
}

void RenderCore::draw(const RxVertexArray& vertexArray, const RxIndexArray& indexArray)
{
	if (vertexArray._data.size())
	{
		//Log("Drawing a vertex array %d triangles!!!", indexArray.size() / 3);

		enableVertexAttribArray(0);
		enableVertexAttribArray(1);
		enableVertexAttribArray(2);

		setVertexAttribPointer(0, 3, GL_FLOAT, false, vertexArray.stride(), vertexArray.data());
		setVertexAttribPointer(1, 4, GL_FLOAT, false, vertexArray.stride(), &vertexArray._data[0] + vertexArray.getAttributeOffset(1));
		setVertexAttribPointer(2, 2, GL_FLOAT, false, vertexArray.stride(), &vertexArray._data[0] + vertexArray.getAttributeOffset(2));

		glDrawElements(GL_TRIANGLES, indexArray.size(), GL_UNSIGNED_SHORT, indexArray.data());

		disableVertexAttribArray(0);
		disableVertexAttribArray(1);
		disableVertexAttribArray(2);
	}
}

/// Allows a drawable to draw itself
void RenderCore::draw(Drawable &drawable)
{
	drawable.onDraw(this);
}

void RenderCore::setProjectionMatrix(const mat4& projection)
{
	m_projection = projection;
}
void RenderCore::setViewMatrix(const mat4& view)
{
	m_view = view;
}
void RenderCore::setModelMatrix(const mat4& model)
{
	m_model[m_model.size() - 1] = model;
}

/// The renderer always has a target resolution to operate
/// On windowed mode, its the size of the window's client area and in fullscreen the native resolution we're running at
int RenderCore::resolutionWidth()
{
    return 0;
    //return getWindow()->width();
}

/// The renderer always has a target resolution to operate
/// On windowed mode, its the size of the window's client area and in fullscreen the native resolution we're running at
int RenderCore::resolutionHeight()
{
    return 0;
    //return getWindow()->height();
}
