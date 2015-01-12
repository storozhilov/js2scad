#include "sphere_object.hxx"

namespace js2scad
{

SphereObject::SphereObject(ObjectsCollection& collection, double radius) :
	AbstractSolidObject(collection),
	_radius(radius),
	_hasFragmentAngle(false),
	_fragmentAngle(),
	_hasFragmentSize(false),
	_fragmentSize(),
	_hasResolution(false),
	_resolution()
{}

SphereObject::~SphereObject()
{}

void SphereObject::setFragmentAngle(double fa)
{
	_hasFragmentAngle = true;
	_fragmentAngle = fa;
}

void SphereObject::setFragmentSize(double fs)
{
	_hasFragmentSize = true;
	_fragmentSize = fs;
}

void SphereObject::setResolution(double res)
{
	_hasResolution = true;
	_resolution = res;
}

void SphereObject::toScad(std::ostream& to) const
{
	to << "sphere(r = " << _radius;
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
