#ifndef __JS2SCAD__UNION_OBJECT__HXX
#define __JS2SCAD__UNION_OBJECT__HXX

#include "abstract_collection_object.hxx"

namespace js2scad
{

class DifferenceObject : public AbstractCollectionObject
{
public:
	DifferenceObject(ObjectsCollection& collection);
	//virtual ~DifferenceObject();

	//virtual void toScad(std::ostream& to, size_t indent) const;
private:
	DifferenceObject();

	virtual void toScad(std::ostream& to) const;
};

} // namespace js2scad

#endif
