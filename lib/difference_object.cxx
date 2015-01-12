#include "difference_object.hxx"

namespace js2scad
{

DifferenceObject::DifferenceObject(ObjectsCollection& collection) :
	AbstractCollectionObject(collection)
{}

//DifferenceObject::~DifferenceObject()
//{}

void DifferenceObject::toScad(std::ostream& to) const
{
	to << "difference()";
}

} // namespace js2scad
