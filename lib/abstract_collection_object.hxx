#ifndef __JS2SCAD__ABSTRACT_COLLECTION_OBJECT__HXX
#define __JS2SCAD__ABSTRACT_COLLECTION_OBJECT__HXX

#include "abstract_object.hxx"
#include <vector>

namespace js2scad
{

class AbstractCollectionObject : public AbstractObject
{
public:
	AbstractCollectionObject(ObjectsCollection& collection);
	virtual ~AbstractCollectionObject();

	void addChild(AbstractObject& child);

	virtual void toScad(std::ostream& to, size_t indent) const;
protected:
	virtual void toScad(std::ostream& to) const = 0;
private:
	AbstractCollectionObject();

	typedef std::vector<AbstractObject *> Children;

	ObjectsCollection& _objectsCollection;
	Children _children;
};

} // namespace js2scad

#endif
