#ifndef __JS2SCAD__CYLINDER_OBJECT__HXX
#define __JS2SCAD__CYLINDER_OBJECT__HXX

#include "abstract_solid_object.hxx"

namespace js2scad
{

class CylinderObject : public AbstractSolidObject
{
public:
	CylinderObject(ObjectsCollection& collection, double height);
	virtual ~CylinderObject();

	void setRadius(double r);
	void setBottomConeRadius(double r1);
	void setTopConeRadius(double r2);
	void setDiameter(double d);
	void setBottomConeDiameter(double d1);
	void setTopConeDiameter(double d2);
	void setCenter(bool center);
	void setFragmentAngle(double fa);
	void setFragmentSize(double fs);
	void setResolution(double res);
private:
	CylinderObject();

	virtual void toScad(std::ostream& to) const;

	double _height;
	bool _hasRadius;
	double _radius;
	bool _hasBottomConeRadius;
	double _bottomConeRadius;
	bool _hasTopConeRadius;
	double _topConeRadius;
	bool _hasDiameter;
	double _diameter;
	bool _hasBottomConeDiameter;
	double _bottomConeDiameter;
	bool _hasTopConeDiameter;
	double _topConeDiameter;
	bool _hasCenter;
	bool _center;
	bool _hasFragmentAngle;
	double _fragmentAngle;
	bool _hasFragmentSize;
	double _fragmentSize;
	bool _hasResolution;
	double _resolution;
};

} // namespace js2scad

#endif
