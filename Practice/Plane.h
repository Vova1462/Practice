#pragma once
#include"Poly.h"
#include"BoundingBox.h"
namespace Modeling3D
{
	class Plane
	{
		double A, B, C, D;
		//ѕолучение представлени€ плоскости в виде многоугольника, огранниченного данными Bounding_Box
	public:
		PolyModel GetPolyRepresentation(BoundingBox bbox);
		bool CrossPlaneWithLine(Point point_1, Point point_2, Point* result);
	};
}