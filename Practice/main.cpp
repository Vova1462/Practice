#include<stdlib.h>
#include<iostream>
#include"Poly.h"
#include"BoundingBox.h"
#include"Plane.h"
#include <string>

using namespace std;
using namespace Modeling3D;
int main(int argc, char** argv)
{
	PolyModel model;

	model.ReadFromSTLFile(argv[1]);
	//model.WriteToSTLFile(argv[2]);

	BoundingBox bbox;
	string as(argv[4]), // создаем строки из переданных параментов 
		bs(argv[5]),
		cs(argv[6]),
		ds(argv[7]);
	
	// вызываем конструктор Plane и передаем ему 4 аргумента double
	Plane plane(stod(as),
		stod(bs),
		stod(cs),
		stod(ds));

	PolyModel plane_repr=plane.GetPolyRepresentation(bbox);
	plane_repr.WriteToSTLFile(argv[3]);

	return 0;
}