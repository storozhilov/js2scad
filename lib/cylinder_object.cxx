#include "cylinder_object.hxx"

namespace js2scad
{

CylinderObject::CylinderObject(ObjectsCollection& collection, double height) :
	AbstractSolidObject(collection),
	_height(height),
	_hasRadius(false),
	_radius(),
	_hasBottomConeRadius(false),
	_bottomConeRadius(),
	_hasTopConeRadius(false),
	_topConeRadius(),
	_hasDiameter(false),
	_diameter(),
	_hasBottomConeDiameter(false),
	_bottomConeDiameter(),
	_hasTopConeDiameter(false),
	_topConeDiameter(),
	_hasCenter(false),
	_center(),
	_hasFragmentAngle(false),
	_fragmentAngle(),
	_hasFragmentSize(false),
	_fragmentSize(),
	_hasResolution(false),
	_resolution()
{}

CylinderObject::~CylinderObject()
{}

void CylinderObject::setRadius(double r)
{
	_hasRadius = true;
	_radius = r;
}

void CylinderObject::setBottomConeRadius(double r1)
{
	_hasBottomConeRadius = true;
	_bottomConeRadius = r1;
}

void CylinderObject::setTopConeRadius(double r2)
{
	_hasTopConeRadius = true;
	_topConeRadius = r2;
}

void CylinderObject::setDiameter(double d)
{
	_hasDiameter = true;
	_diameter = d;
}

void CylinderObject::setBottomConeDiameter(double d1)
{
	_hasBottomConeDiameter = true;
	_bottomConeDiameter = d1;
}

void CylinderObject::setTopConeDiameter(double d2)
{
	_hasTopConeDiameter = true;
	_topConeDiameter = d2;
}

void CylinderObject::setCenter(bool center)
{
	_hasCenter = true;
	_center = true;
}

void CylinderObject::setFragmentAngle(double fa)
{
	_hasFragmentAngle = true;
	_fragmentAngle = fa;
}

void CylinderObject::setFragmentSize(double fs)
{
	_hasFragmentSize = true;
	_fragmentSize = fs;
}

void CylinderObject::setResolution(double res)
{
	_hasResolution = true;
	_resolution = res;
}

void CylinderObject::toScad(std::ostream& to) const
{
	to << "cylinder(h = " << _height;
	if (_hasRadius) {
		to << ", r = " << _radius;
	}
	if (_hasBottomConeRadius) {
		to << ", r1 = " << _bottomConeRadius;
	}
	if (_hasTopConeRadius) {
		to << ", r2 = " << _topConeRadius;
	}
	if (_hasDiameter) {
		to << ", d = " << _diameter;
	}
	if (_hasBottomConeDiameter) {
		to << ", d1 = " << _bottomConeDiameter;
	}
	if (_hasTopConeDiameter) {
		to << ", d2 = " << _topConeDiameter;
	}
	if (_hasCenter) {
		to << std::boolalpha << ", center = " << _center;
	}
	if (_hasFragmentAngle) {
		to << ", $fa = " << _fragmentAngle;
	}
	if (_hasFragmentSize) {
		to << ", $fs = " << _fragmentSize;
	}
	if (_hasResolution) {
		to << ", $fn = " << _resolution;
	}
	to << ')';
}

} // namespace js2scad
