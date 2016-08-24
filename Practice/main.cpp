#include<stdlib.h>
#include<iostream>
#include"Poly.h"
#include"BoundingBox.h"
#include"Plane.h"
using namespace Modeling3D;
int main(int argc, char** argv)
{
	PolyModel model;

	model.ReadFromSTLFile(argv[1]);
	//model.WriteToSTLFile(argv[2]);

	BoundingBox bbox;
	
	Plane plane;

	PolyModel plane_repr=plane.GetPolyRepresentation(bbox);
	plane_repr.WriteToSTLFile(argv[3]);

	return 0;
}