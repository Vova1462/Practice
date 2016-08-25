#include"Poly.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>

using namespace std;
namespace Modeling3D
{
	int PolyModel::ReadFromSTLFile(char * filename)
	{
		char buf[6];
		buf[5] = '\0';
		unsigned int number_of_triangles = 0;
		
		//Открытие файла
		ifstream ist(filename, ios_base::binary);
		if (!ist) {
			cout << "Error, can't find your file";
			return -1;
		}
		
		//Проверка, что файл бинарный
		ist.read(buf, 5);
		if (string(buf) == "solid") 
			return 1;

		//Пропускаем 80 байт
		ist.seekg(80, ios::beg);
		
		//Считывание колличества треугольников
		ist.read(reinterpret_cast<char *> (&number_of_triangles), 4);
		float coordinates[9];

		//установим емкость массива, т.е. capacity, чтобы не выделять лишнюю память
		Points.reserve(3 * number_of_triangles);
		Triangles.reserve(number_of_triangles); 


		for (int i = 0;i < number_of_triangles;i++)
		{
			//Пропускаем нормали (3хfloat байт)
			ist.seekg(3 * sizeof(float), ist.cur);

			//Считывание координат
			ist.read(reinterpret_cast<char *> (coordinates), 9 * sizeof(float));

			Point pt1, pt2, pt3; // создаем три точки
			pt1.X = coordinates[0];
			pt1.Y = coordinates[1];
			pt1.Z = coordinates[2];

			pt2.X = coordinates[3];
			pt2.Y = coordinates[4];
			pt2.Z = coordinates[5];

			pt3.X = coordinates[6];
			pt3.Y = coordinates[7];
			pt3.Z = coordinates[8];

			Points.push_back(pt1); // записываем в конец массива координаты первой точки
			Points.push_back(pt2);
			Points.push_back(pt3);

			Triangle tr; // создаем номер точки
			tr.V[0] = i * 3;
			tr.V[1] = i * 3 + 1;
			tr.V[2] = i * 3 + 2;

			Triangles.push_back(tr);// положим в конец массива


			//Пропускаем специальные числа
			ist.seekg(sizeof(unsigned short), ist.cur);

		}
		return 0;
	}

	int PolyModel::WriteToSTLFile(char * filename) { // создаем метод класса PolyModel

		ofstream fout(
			filename,
			ios_base::out |
			ios_base::binary); // открываем файл stl для записи в бинарном виде

		if (!fout) {
			cout << "File error"; // проверяем, открылся ли файл
			return 1;
		}


		char header[80]; //записываем заголовок 80 байт
		fout.write(header, 80);

		//запишем количество треугольников, определив количество элементов массива Triangles
		unsigned triangles_num = Triangles.size();
		fout.write(reinterpret_cast<char*>(&triangles_num), sizeof(unsigned));

		// Запись треугольников

		for (unsigned i = 0; i < triangles_num; i++) {
			float normal[3] = { 0.0, 0.0, 0.0 }; // создаем нулевой массив для нормалей
			fout.write(reinterpret_cast <char*>(normal), 12); // записываем его в файл

															  // Запишем координат треугольника
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

			// Записываем 16 бит Attribute byte count
			unsigned short attr_byte_count;
			fout.write(reinterpret_cast<char*>(&attr_byte_count), sizeof(unsigned short));
		}
		return 0;
	}

	void PolyModel::AddTriangle(Point p1, Point p2, Point p3)
	{
		int max_point_index = Points.size() - 1;

		Points.push_back(p1);
		Points.push_back(p2);
		Points.push_back(p3);

		Triangle tr;
		tr.V[0] = max_point_index + 1;
		tr.V[1] = max_point_index + 2;
		tr.V[2] = max_point_index + 3;

		Triangles.push_back(tr);

	}

}