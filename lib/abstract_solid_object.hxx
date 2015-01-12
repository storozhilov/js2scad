#ifndef __JS2SCAD__ABSTRACT_SOLID_OBJECT__HXX
#define __JS2SCAD__ABSTRACT_SOLID_OBJECT__HXX

#include "abstract_object.hxx"

namespace js2scad
{

class AbstractSolidObject : public AbstractObject
{
public:
	AbstractSolidObject(ObjectsCollection& collection);

	virtual void toScad(std::ostream& to, size_t indent) const;
protected:
	virtual void toScad(std::ostream& to) const = 0;
private:
	AbstractSolidObject();
};

} // namespace js2scad

#endif
