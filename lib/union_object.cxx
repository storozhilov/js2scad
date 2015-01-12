#include "union_object.hxx"

namespace js2scad
{

UnionObject::UnionObject(ObjectsCollection& collection) :
	AbstractCollectionObject(collection)
{}

//UnionObject::~UnionObject()
//{}

void UnionObject::toScad(std::ostream& to) const
{
	to << "union()";
}

} // namespace js2scad
