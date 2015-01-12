#include "cube_object.hxx"

namespace js2scad
{

CubeObject::CubeObject(ObjectsCollection& collection, double x, double y, double z, bool center) :
	AbstractSolidObject(collection),
	_x(x),
	_y(y),
	_z(z),
	_center(center)
{}

CubeObject::~CubeObject()
{}

void CubeObject::toScad(std::ostream& to) const
{
	to << "cube([" << _x << ", " << _y << ", " << _z <<
		"], center = " << std::boolalpha << _center << ")";
}

} // namespace js2scad
