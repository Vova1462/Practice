#pragma once
#include "Poly.h"
#include "BoundingBox.h"

namespace Modeling3D
{
	class Plane {

		double A, B, C, D;

	public: // �� � ��� �����, �� ��� ������ ��� �������, � ������� �� ���������, ������� � ��� �������, �� ��� ���� ������� ����� public

		// ������� ����������� ������ Plane, ���� ����������� �� ���������
		Plane() : // ����������� ��������� ��� ������������� ������ ������
			A(1.0), 
			B(0.0), 
			C(0.0), 
			D(0.0) {}

		Plane(double a, double b, double c, double d) : // ������� ������ �����������, ��� ����������� �������
			A(a),
			B(b),
			C(c),
			D(d) {} 
	
		

		//�������� ������������� ��������� � ���� �������������� ����
		// ���������, ������� ��������� ������� BoundingBox
		PolyModel GetPolyRepresentation(BoundingBox bbox); 

		// ������� ���� ������������ ��������� � ������
		// ������� ������ ������� ���������: ���� ����������� ��� ���
		// point_1, point_2 - �����, ����� ������� �������� �������� ������
		// plane - ���������
		// result - ����� �����������
		// ������� ���������� true, ���� ����� �������
		bool GetIntersectionWhithLine(Point point_1, Point point_2, Point& result);

		//�������, ������� ���� ����� ����������� ������� � ���������
		bool GetIntersectionLineSegment(Point point_1, Point point_2, Point& result);
	};

}
