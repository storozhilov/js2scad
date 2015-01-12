#ifndef __JS2SCAD__SPHERE_OBJECT__HXX
#define __JS2SCAD__SPHERE_OBJECT__HXX

#include "abstract_solid_object.hxx"

namespace js2scad
{

class SphereObject : public AbstractSolidObject
{
public:
	SphereObject(ObjectsCollection& collection, double radius);
	virtual ~SphereObject();

	void setFragmentAngle(double fa);
	void setFragmentSize(double fs);
	void setResolution(double res);
private:
	SphereObject();

	virtual void toScad(std::ostream& to) const;

	double _radius;
	bool _hasFragmentAngle;
	double _fragmentAngle;
	bool _hasFragmentSize;
	double _fragmentSize;
	bool _hasResolution;
	double _resolution;
};

} // namespace js2scad

#endif
