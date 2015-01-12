#ifndef __JS2SCAD__UNION_OBJECT__HXX
#define __JS2SCAD__UNION_OBJECT__HXX

#include "abstract_collection_object.hxx"

namespace js2scad
{

class UnionObject : public AbstractCollectionObject
{
public:
	UnionObject(ObjectsCollection& collection);
	//virtual ~UnionObject();

	//virtual void toScad(std::ostream& to, size_t indent) const;
private:
	UnionObject();

	virtual void toScad(std::ostream& to) const;
};

} // namespace js2scad

#endif
