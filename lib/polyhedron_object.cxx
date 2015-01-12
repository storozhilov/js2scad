#include "polyhedron_object.hxx"

namespace js2scad
{

PolyhedronObject::PolyhedronObject(ObjectsCollection& collection,
			const PointsContainer& points, const FacesContainer& faces) :
	AbstractSolidObject(collection),
	_points(points),
	_faces(faces),
	_hasConvexity(false),
	_convexity()
{}

PolyhedronObject::PolyhedronObject(ObjectsCollection& collection,
			const PointsContainer& points, const FacesContainer& faces,
			size_t convexity) :
	AbstractSolidObject(collection),
	_points(points),
	_faces(faces),
	_hasConvexity(true),
	_convexity(convexity)
{}

void PolyhedronObject::toScad(std::ostream& to) const
{
	to << "polyhedron(points = [";
	for (size_t i = 0U; i < _points.size(); ++i) {
		if (i > 0U) {
			to << ", ";
		}
		to << '[' << _points[i].x << ", " << _points[i].y << ", " << _points[i].z << ']';
	}
	to << "], faces = [";
	for (size_t i = 0U; i < _faces.size(); ++i) {
		if (i > 0U) {
			to << ", ";
		}
		to << '[' << _faces[i].pt1 << ", " << _faces[i].pt2 << ", " << _faces[i].pt3 << ']';
	}
	to << ']';
	if (_hasConvexity) {
		to << ", convexity = " << _convexity;
	}
	to << ')';
}

} // namespace js2scad
