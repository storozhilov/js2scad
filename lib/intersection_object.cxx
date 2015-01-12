#include "intersection_object.hxx"

namespace js2scad
{

IntersectionObject::IntersectionObject(ObjectsCollection& collection) :
	AbstractCollectionObject(collection)
{}

//IntersectionObject::~IntersectionObject()
//{}

void IntersectionObject::toScad(std::ostream& to) const
{
	to << "intersection()";
}

} // namespace js2scad
