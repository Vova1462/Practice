#include "Plane.h"
#include "BoundingBox.h"
#include"Poly.h"

namespace Modeling3D
{
	//ѕолучение точки пересечени€(result) пр€мой(заданой point1,point2) и плоскости(plane)
	bool Plane::CrossPlaneWithLine( Point point_1, Point point_2, Point* result)
	{
		Plane surface;
		double p1, p2, p3;
		//¬ычисление направл€ющего вектора
		p1 = point_2.X - point_1.X;
		p2 = point_2.Y - point_1.Y;
		p3 = point_2.Z - point_1.Z;
		//ѕолучение начальных координат
		double x1, y1, z1;
		x1 = point_1.X;
		y1 = point_1.Y;
		z1 = point_1.Z;
		//ѕроверка на паралельность плоскости и пр€мой
		if (A*p1 + B*p2 + C*p3 == 0)
		{
			result = nullptr;
			return false;
		}
		//¬ычисление координат точки
		double t = -(A*x1 + B*y1 + C*z1 + D) / (A*p1 + B*p2 + C*p3);
		if (result == nullptr)
			result = new Point();
		result->X = p1*t + x1;
		result->Y = p2*t + y1;
		result->Z = p3*t + z1;
		return true;
	}

	PolyModel Plane::GetPolyRepresentation(BoundingBox bbox)
	{

		for (int i = 0;i < 12;i++)
		{

		}
		return PolyModel();
	}
}
