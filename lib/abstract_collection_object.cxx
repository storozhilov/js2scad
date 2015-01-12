#include "abstract_collection_object.hxx"
#include "objects_collection.hxx"

namespace js2scad
{

AbstractCollectionObject::AbstractCollectionObject(ObjectsCollection& collection) :
	AbstractObject(collection),
	_objectsCollection(collection),
	_children()
{}

AbstractCollectionObject::~AbstractCollectionObject()
{}

void AbstractCollectionObject::addChild(AbstractObject& child)
{
	_children.push_back(&child);
	_objectsCollection.setNonRoot(child);
}

void AbstractCollectionObject::toScad(std::ostream& to, size_t indent) const
{
	printIndent(to, indent);
	operationsToScad(to);
	toScad(to);
	to << " {";
	if (!_children.empty()) {
		to << std::endl;
	}
	for (Children::const_iterator i = _children.begin(); i != _children.end(); ++i) {
		if (i != _children.begin()) {
			to << std::endl;
		}
		(*i)->toScad(to, indent + 1);
	}
	if (!_children.empty()) {
		to << std::endl;
		printIndent(to, indent);
	}
	to << '}';
}

} // namespace js2scad
