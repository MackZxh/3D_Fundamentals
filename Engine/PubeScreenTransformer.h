#pragma once
#include "ChiliWin.h"
#include "Vec3.h"
#include "Graphics.h"

class CLASS_DECLSPEC PubeScreenTransformer
{
public:
	PubeScreenTransformer()
		:
		xFactor(float(Graphics::ScreenWidth) / 2.0f),
		yFactor(float(Graphics::ScreenHeight) / 2.0f)
	{}
	template<class Vertex>
	Vertex& Transform(Vertex& v) const
	{
		const float zInv = 1.0f / v.pos.z;
		// divide all position components and attributes by z
		// (we want to be interpolating our attributes in the
		//  same space where the x,y interpolation is taking
		//  place to prevent distortion)
		v *= zInv;
		// adjust position x,y from perspective normalized space
		// to screen dimension space after perspective divide
		v.pos.x = (v.pos.x + 1.0f) * xFactor;
		v.pos.y = (-v.pos.y + 1.0f) * yFactor;
		// store 1/z in z (we will need the interpolated 1/z
		// so that we can recover the attributes after interp.)
		v.pos.z = zInv;

		return v;
	}
	template<class Vertex>
	Vertex GetTransformed(const Vertex& v) const
	{
		return Transform(Vertex(v));
	}

	Vec3& TransformVec3(Vec3& v) const
	{
		//const float zInv = 1.0f / v.z;
		//// divide all position components and attributes by z
		//// (we want to be interpolating our attributes in the
		////  same space where the x,y interpolation is taking
		////  place to prevent distortion)
		//v *= zInv;
		// adjust position x,y from perspective normalized space
		// to screen dimension space after perspective divide
		v.x = (v.x + 1.0f) * xFactor;
		v.y = (-v.y + 1.0f) * yFactor;
		// store 1/z in z (we will need the interpolated 1/z
		// so that we can recover the attributes after interp.)
		//v.z = zInv;

		return v;
	}
	Vec3 GetTransformedVec3(const Vec3& v) const
	{
		Vec3 v3 = Vec3(v);
		return TransformVec3(v3);
	}
private:
	float xFactor;
	float yFactor;
};