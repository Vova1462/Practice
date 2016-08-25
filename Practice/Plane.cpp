#include <array>
#include<algorithm>

#include "Plane.h"
#include "BoundingBox.h"
#include "Poly.h"



using namespace std;
namespace Modeling3D {

	// функция ищет пересечечния плоскости с прямой
	// функция должна вернуть результат: есть пересечение или нет
	// point_1, point_2 - точки, через которые проходит заданная прямая
	// plane - плоскость
	// result - точка пересечения
	// функция возвращает true, если точка найдена
	bool Plane::GetIntersectionWhithLine(Point point_1, Point point_2, Point& result) {

		double p1, p2, p3;

		p1 = point_2.X - point_1.X;
		p2 = point_2.Y - point_1.Y;
		p3 = point_2.Z - point_1.Z;

		double x1, y1, z1;

		x1 = point_1.X;
		y1 = point_1.Y;
		z1 = point_1.Z;

		//проверим, есть ли точка пересечения, в этом случае знамеатель не должен быть равен нулю
		if ((A*p1 + B*p2 + C*p3) == 0.0) {
			return false;
		}

		double t = -(A*x1 + B*y1 + C*z1 + D) / (A*p1 + B*p2 + C*p3);

		result.X = x1 + p1*t; //разименовываем указатель и присваиваем переменной значение
		result.Y = y1 + p2*t; // точка пересечения найдена и записана в result
		result.Z = z1 + p3*t;


		return true;
	}
	 // функция для проверки, лежит ли число в интервале
	bool IsValueBetween(double val, double a, double b) {
		
		if (a < b)
			return (a <= val)&&(val <= b); // проверяем, лежит ли значение в этом интервале, если да, то true, иначе false
		else
			return (b <= val)&&(val <= a); // проверяем, лежит ли значение в этом интервале, если да, то true, иначе false
	}
	
	bool Plane::GetIntersectionLineSegment(Point point_1, Point point_2, Point & result)
	{
		Point p; //временная точка
		if (GetIntersectionWhithLine(point_1, point_2, p)) // если пересечение найдено
		{
			if (   (IsValueBetween(p.X, point_1.X, point_2.X)) // проверим с помощью функции, лежит ли наша точка в отрезке
				&& (IsValueBetween(p.Y, point_1.Y, point_2.Y))// если да, вернуть true
				&& (IsValueBetween(p.Z, point_1.Z, point_2.Z))) {

				result = p; // если точка пересечения найдена, то присваиваем result p
				return true;
			}
		}
				
		return false;
	}

	bool ComparingParesofArray(pair<double,int> a, pair<double, int> b)
	{
		return a.first < b.first;
	}

	int GetAngleBetweenVectors(Point point_1, Point point_2, Point point_3)
	{
		return acos(((point_2.X-point_1.X)*(point_3.X - point_1.X)+ 
					(point_2.Y - point_1.Y)*(point_3.Y - point_1.Y)+
					(point_2.Z- point_1.Z)*(point_3.Z - point_1.Z)) 
					/
					  (sqrt(pow((point_2.X - point_1.X),2) 
							+ pow((point_2.Y - point_1.Y),2) 
							+ pow((point_2.Z - point_1.Z),2))*
					  sqrt(pow((point_3.X - point_1.X),2) 
							+ pow((point_3.Y - point_1.Y),2)
							+ pow((point_3.Z - point_1.Z),2))));
	}

	PolyModel Plane::GetPolyRepresentation(BoundingBox bbox)
	{
		// массив вершин куба
		Point v[8];

		v[0].X = bbox.Xmax;
		v[0].Y = bbox.Ymin;
		v[0].Z = bbox.Zmax;

		v[1].X = bbox.Xmax;
		v[1].Y = bbox.Ymax;
		v[1].Z = bbox.Zmax;

		v[2].X = bbox.Xmin;
		v[2].Y = bbox.Ymax;
		v[2].Z = bbox.Zmax;

		v[3].X = bbox.Xmin;
		v[3].Y = bbox.Ymin;
		v[3].Z = bbox.Zmax;

		v[4].X = bbox.Xmax;
		v[4].Y = bbox.Ymin;
		v[4].Z = bbox.Zmin;

		v[5].X = bbox.Xmax;
		v[5].Y = bbox.Ymax;
		v[5].Z = bbox.Zmin;

		v[6].X = bbox.Xmin;
		v[6].Y = bbox.Ymax;
		v[6].Z = bbox.Zmin;

		v[7].X = bbox.Xmin;
		v[7].Y = bbox.Ymin;
		v[7].Z = bbox.Zmin;

		// Ребра

		typedef std::pair<Point, Point> Edge; // создали новое имя Edge для типа std::pair<Point, Point>

		array<Edge, 12> e{ {			// создаем массив ребер Edge на 12 элементов
					{v[0],v[1]},
					{v[1],v[2]},
					{v[2],v[3]},
					{v[3],v[0]},

					{v[0],v[4]},
					{v[1],v[5]},
					{v[2],v[6]},
					{v[3],v[7]},

					{v[4],v[5]},
					{v[5],v[6]},
		
					{v[6],v[7]},
					{v[7],v[4]}
					} };

		// массив точек пересечения плоскости с ребрами
		vector<Point> intersect_pts;

		for (auto edge : e) { // это такой цикл, где edge - ссылка на текущий элемент массива
			Point p;
			if (GetIntersectionLineSegment(edge.first, edge.second, p)) // если точка пересечения найдена
				intersect_pts.push_back(p); // то положить ее в массив
		}

		unsigned intersect_pts_count = intersect_pts.size();

		PolyModel model;
		
		if (intersect_pts_count == 0)
			return model;

		//Массив углов между лучами выпущенными из одной точки
		vector<pair<double, int>> angles(intersect_pts.size() - 1);
		 
		angles[0] = make_pair(0.0, 1);
		double max_angle = 0.0;
		size_t max_angle_index = 0;
		for (size_t i = 2; i < intersect_pts.size(); i++)
		{
			double angle = GetAngleBetweenVectors(intersect_pts[0],
				intersect_pts[1],
				intersect_pts[i]);
			angles[i] = make_pair(angle, i);
			if (max_angle < angle)
			{
				max_angle = angle;
				max_angle_index = i;
			}
		}
		for (size_t i = 2; i < intersect_pts.size(); i++)
		{
			double angle = GetAngleBetweenVectors(intersect_pts[0],
				intersect_pts[max_angle_index],
				intersect_pts[i]);
			if (i == max_angle_index) angle = 0.0;
			angles[i] = make_pair(angle, i);
		}

		sort(angles.begin() + 1, angles.end(),ComparingParesofArray);
		//Строятся треугольники
		for (unsigned i =2; i < intersect_pts_count; i++)
		{
			Point p1 = intersect_pts[0];
			Point p2 = intersect_pts[angles[i - 1].second];
			Point p3 = intersect_pts[angles[i].second];
			model.AddTriangle(p1, p2, p3);
		}

		return model; // возвращение полигональной модели
	}
}