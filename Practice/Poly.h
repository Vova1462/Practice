#pragma once
#include<vector>
#include "Point.h"
#include "Triangle.h"

namespace Modeling3D
{
	class PolyModel 
	{
		//Параметры класса
		std::vector<Point> Points;
		std::vector<Triangle> Triangles;
	public:
		int ReadFromSTLFile(char * filename);//метод класса(публичный) Чтение STL файла
		int WriteToSTLFile(char * filename); // запись в STL файл

		void AddTriangle(Point p1, Point p2, Point p3);
	};
}