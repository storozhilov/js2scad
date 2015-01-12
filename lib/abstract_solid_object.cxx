#include "abstract_solid_object.hxx"

namespace js2scad
{

AbstractSolidObject::AbstractSolidObject(ObjectsCollection& collection) :
	AbstractObject(collection)
{}

void AbstractSolidObject::toScad(std::ostream& to, size_t indent) const
{
	printIndent(to, indent);
	operationsToScad(to);
	toScad(to);
	to << ';';
}

} // namespace js2scad

