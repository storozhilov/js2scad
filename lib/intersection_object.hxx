#ifndef __JS2SCAD__INTERSECTION_OBJECT__HXX
#define __JS2SCAD__INTERSECTION_OBJECT__HXX

#include "abstract_collection_object.hxx"

namespace js2scad
{

class IntersectionObject : public AbstractCollectionObject
{
public:
	IntersectionObject(ObjectsCollection& collection);
	//virtual ~IntersectionObject();

	//virtual void toScad(std::ostream& to, size_t indent) const;
private:
	IntersectionObject();

	virtual void toScad(std::ostream& to) const;
};

} // namespace js2scad

#endif
