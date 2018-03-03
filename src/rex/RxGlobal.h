#ifndef GDI_Common_h__
#define GDI_Common_h__

namespace Render
{
	namespace Primitive
	{
		enum Type
		{
			Triangles,
			TriangleFan,
			TriangleStrip,
			Lines,
			LineLoop,
			LineStrip,
			Points
		};
	}

	namespace Blend
	{
		enum Mode
		{
			Alpha,
			Add,       ///< Simply sums the incoming color to the destination color.
			AddAlpha,
			Multiply,
			PreMultBlend,
			None
		};
	}
};

struct FScissorRect
{
	int x;
	int y;
	int w;
	int h;
};

struct FRenderState
{
	bool ZTest;
	bool ZWrite;
	int  ZFunc;
	int  BlendFunc;
	int  BlendAlphaFunc;
	bool AlphaToCoverage;
	int  CullMode;
};

#endif // GDI_Common_h__
