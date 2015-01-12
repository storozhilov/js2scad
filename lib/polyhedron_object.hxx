#ifndef __JS2SCAD__POLYHEDRON_OBJECT__HXX
#define __JS2SCAD__POLYHEDRON_OBJECT__HXX

#include "abstract_solid_object.hxx"

namespace js2scad
{

class PolyhedronObject : public AbstractSolidObject
{
public:
	struct Point
	{
		double x;
		double y;
		double z;

		Point(double x, double y, double z) :
			x(x),
			y(y),
			z(z)
		{}
	};
	typedef std::deque<Point> PointsContainer;

	struct Face
	{
		size_t pt1;
		size_t pt2;
		size_t pt3;

		Face(size_t pt1, size_t pt2, size_t pt3) :
			pt1(pt1),
			pt2(pt2),
			pt3(pt3)
		{}
	};
	typedef std::deque<Face> FacesContainer;

	PolyhedronObject(ObjectsCollection& collection, const PointsContainer& points,
			const FacesContainer& faces);
	PolyhedronObject(ObjectsCollection& collection, const PointsContainer& points,
			const FacesContainer& faces, size_t convexity);
private:
	PolyhedronObject();

	virtual void toScad(std::ostream& to) const;

	PointsContainer _points;
	FacesContainer _faces;
	bool _hasConvexity;
	double _convexity;
};

} // namespace js2scad

#endif
