#pragma once
#include<vector>
#include "Point.h"
#include "Triangle.h"

namespace Modeling3D
{
	class PolyModel 
	{
		//��������� ������
		std::vector<Point> Points;
		std::vector<Triangle> Triangles;
	public:
		int ReadFromSTLFile(char * filename);//����� ������(���������) ������ STL �����
		int WriteToSTLFile(char * filename); // ������ � STL ����

		void AddTriangle(Point p1, Point p2, Point p3);
	};
}