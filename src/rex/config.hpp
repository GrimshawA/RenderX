#ifndef REX_CONFIG_HPP_
#define REX_CONFIG_HPP_

#define REX_API

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

#endif // REX_CONFIG_HPP_
