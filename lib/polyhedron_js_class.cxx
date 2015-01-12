#include "translator_impl.hxx"
#include "polyhedron_object.hxx"

using namespace JS;

namespace js2scad
{

JSClass TranslatorImpl::polyhedronInstanceClass = {
	"scad.PolyhedronInstance",
	0,
	JS_PropertyStub,
	JS_PropertyStub,
	JS_PropertyStub,
	JS_StrictPropertyStub,
	JS_EnumerateStub,
	JS_ResolveStub,
	JS_ConvertStub,
	JS_FinalizeStub,
	NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL
};

JSBool TranslatorImpl::callPolyhedron(JSContext *cx, uintN argc, jsval *vp)
{
	// Parameters handling
	if (argc <= 1) {
		JS_ReportError(cx, "Insufficient amount of arguments - should be 2 at least");
		return JS_FALSE;
	}
	// Processing points
	jsuint pointsJsObjLen;
	JSObject * pointsJsObj = toJsArray(cx, *(JS_ARGV(cx, vp)), pointsJsObjLen);
	if (pointsJsObj == NULL) {
		JS_ReportError(cx, "First argument is not of Array type");
		return JS_FALSE;
	}
	PolyhedronObject::PointsContainer points;
	for (size_t i = 0U; i < pointsJsObjLen; ++i) {
		jsval pointJsVal;
		if (!JS_GetElement(cx, pointsJsObj, i, &pointJsVal)) {
			JS_ReportError(cx, "%d-th point retrival error", i);
			return JS_FALSE;
		}
		std::vector<jsdouble> point;
		if (!toJsDoubleVector(cx, pointJsVal, point)) {
			JS_ReportError(cx, "%d-th point is not Array of Number", i);
			return JS_FALSE;
		}
		if (point.size() < 3) {
			JS_ReportError(cx, "%d-th point has less than 3 coordinates", i);
			return JS_FALSE;
		}
		points.push_back(PolyhedronObject::Point(point[0], point[1], point[2]));
	}
	// Processing faces
	jsuint facesJsObjLen;
	JSObject * facesJsObj = toJsArray(cx, *(JS_ARGV(cx, vp) + 1), facesJsObjLen);
	if (facesJsObj == NULL) {
		JS_ReportError(cx, "Second argument is not of Array type");
		return JS_FALSE;
	}
	PolyhedronObject::FacesContainer faces;
	for (size_t i = 0U; i < facesJsObjLen; ++i) {
		jsval faceJsVal;
		if (!JS_GetElement(cx, facesJsObj, i, &faceJsVal)) {
			JS_ReportError(cx, "%d-th face retrival error", i);
			return JS_FALSE;
		}
		std::vector<jsdouble> face;
		if (!toJsDoubleVector(cx, faceJsVal, face)) {
			JS_ReportError(cx, "%d-th face is not Array of Number", i);
			return JS_FALSE;
		}
		if (face.size() < 3) {
			JS_ReportError(cx, "%d-th face has less than 3 points", i);
			return JS_FALSE;
		}
		faces.push_back(PolyhedronObject::Face(face[0], face[1], face[2]));
	}
	bool hasConvexity = false;
	jsdouble convexity;
	if (argc >= 3) {
		if (!toJsDouble(cx, *(JS_ARGV(cx, vp) + 2), convexity)) {
			JS_ReportError(cx, "Third argument is not of Number type");
			return JS_FALSE;
		}
		hasConvexity = true;
	}

	// Polyhedron JS object creation
	TranslatorImpl * translator = getTranslator(cx);
	JSObject * polyhedronJsObject = JS_NewObject(cx, &polyhedronInstanceClass, translator->_abstractScadObject, NULL);
	if (polyhedronJsObject == NULL) {
		JS_ReportError(cx, "'scad.PolyhedronInstance' object initialization error");
		return JS_FALSE;
	}

	// Polyhedron SCAD object creation and linking to JS object
	PolyhedronObject * polyhedronObject;
	if (hasConvexity) {
		polyhedronObject = new PolyhedronObject(translator->_objectsCollection, 
				points, faces, convexity);
	} else {
		polyhedronObject = new PolyhedronObject(translator->_objectsCollection, 
				points, faces);
	}
	JS_SetPrivate(cx, polyhedronJsObject, reinterpret_cast<void *>(polyhedronObject));

	// Returning result
	jsval polyhedronObjectJsVal = OBJECT_TO_JSVAL(polyhedronJsObject);
	JS_SET_RVAL(cx, vp, polyhedronObjectJsVal);
	return JS_TRUE;
}

} // namespace js2scad
