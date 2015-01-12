#ifndef __JS2SCAD__CUBE_OBJECT__HXX
#define __JS2SCAD__CUBE_OBJECT__HXX

#include "abstract_solid_object.hxx"

namespace js2scad
{

class CubeObject : public AbstractSolidObject
{
public:
	CubeObject(ObjectsCollection& collection, double x, double y, double z, bool center);
	virtual ~CubeObject();
private:
	CubeObject();

	virtual void toScad(std::ostream& to) const;

	double _x;
	double _y;
	double _z;
	bool _center;
};

} // namespace js2scad

#endif
