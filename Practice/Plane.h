#pragma once
#include "Poly.h"
#include "BoundingBox.h"

namespace Modeling3D
{
	class Plane {

		double A, B, C, D;

	public: // тк у нас класс, то все методы его закрыты, в отличие от структуры, которая и так открыта, ты что надо сделать класс public

		// создаем конструктор класса Plane, этот конструктор по умолчанию
		Plane() : // стандартный синтаксис для инициализации членов класса
			A(1.0), 
			B(0.0), 
			C(0.0), 
			D(0.0) {}

		Plane(double a, double b, double c, double d) : // создаем второй конструктор, чем перегружаем функцию
			A(a),
			B(b),
			C(c),
			D(d) {} 
	
		

		//получить представление плоскости в виде многоугольника типа
		// полимодел, который ограничен данными BoundingBox
		PolyModel GetPolyRepresentation(BoundingBox bbox); 

		// функция ищет пересечечния плоскости с прямой
		// функция должна вернуть результат: есть пересечение или нет
		// point_1, point_2 - точки, через которые проходит заданная прямая
		// plane - плоскость
		// result - точка пересечения
		// функция возвращает true, если точка найдена
		bool GetIntersectionWhithLine(Point point_1, Point point_2, Point& result);

		//функция, которая ищет точку пересечения отрезка и плоскости
		bool GetIntersectionLineSegment(Point point_1, Point point_2, Point& result);
	};

}
