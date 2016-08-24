#include "Poly.h"
#include <iostream>
#include <fstream>

using namespace std;

namespace Modeling3D
{
	int PolyModel::WriteToSTLFile(char * filename) { // создаем метод класса PolyModel

		ofstream fout(
			filename,
			ios_base::out |
			ios_base::binary); // открываем файл stl дл€ записи в бинарном виде

		if (!fout) {
			cout << "File error"; // провер€ем, открылс€ ли файл
			return 1;
		}
		

		char header[80]; //записываем заголовок 80 байт
		fout.write(header, 80);

		//запишем количество треугольников, определив количество элементов массива Triangles
		unsigned triangles_num = Triangles.size();
		fout.write(reinterpret_cast<char*>(&triangles_num), sizeof(unsigned));
		
		// «апись треугольников

		for (unsigned i = 0; i < triangles_num; i++) {
			float normal[3] = { 0.0, 0.0, 0.0 }; // создаем нулевой массив дл€ нормалей
			fout.write(reinterpret_cast <char*>(normal), 12); // записываем его в файл

			// «апишем координат треугольника
			float coordinates[9];//??

			Point pt1, pt2, pt3; // создаем три точки
			Triangle tr;

			tr = Triangles[i]; // текущий треугольник
			pt1 = Points[tr.V[0]]; // координаты его точечк
			pt2 = Points[tr.V[1]];
			pt3 = Points[tr.V[2]];

			coordinates[0] = static_cast <float>(pt1.X);
			coordinates[1] = static_cast <float>(pt1.Y);
			coordinates[2] = static_cast <float>(pt1.Z);
							 						  
			coordinates[3] = static_cast <float>(pt2.X);
			coordinates[4] = static_cast <float>(pt2.Y);
			coordinates[5] = static_cast <float>(pt2.Z);
													  
			coordinates[6] = static_cast <float>(pt3.X);
			coordinates[7] = static_cast <float>(pt3.Y);
			coordinates[8] = static_cast <float>(pt3.Z);

			fout.write(reinterpret_cast <char*>(coordinates), 9 * sizeof(float));

			// «аписываем 16 бит Attribute byte count
			unsigned short attr_byte_count;
			fout.write(reinterpret_cast<char*>(&attr_byte_count), sizeof(unsigned short));
		}
		return 0;
	}
}