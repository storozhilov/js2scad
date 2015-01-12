#include "translator_impl.hxx"
#include "abstract_object.hxx"

using namespace JS;

namespace js2scad
{

JSBool TranslatorImpl::rotateMethod(JSContext *cx, uintN argc, jsval *vp)
{
	//std::clog << __PRETTY_FUNCTION__ << " is called" << std::endl;
	// Parameters handling
	if (argc <= 0) {
		JS_ReportError(cx, "Empty arguments", argc);
		return JS_FALSE;
	}
	bool hasAngle = false;
	jsdouble angle;
	std::vector<jsdouble> coordinates;
	if (argc == 1) {
		// Processing array argument
		if (!toJsDoubleVector(cx, *JS_ARGV(cx, vp), coordinates)) {
			JS_ReportError(cx, "Invalid first argument - should be array of numbers");
			return JS_FALSE;
		}
		if (coordinates.size() < 3) {
			JS_ReportError(cx, "Invalid size of first argument array: %d - should be 3 at least", coordinates.size());
			return JS_FALSE;
		}
	} else if (argc == 2) {
		if (!toJsDouble(cx, *JS_ARGV(cx, vp), angle)) {
			JS_ReportError(cx, "First argument is not of Number type");
			return JS_FALSE;
		}
		if (!toJsDoubleVector(cx, *(JS_ARGV(cx, vp) + 1), coordinates)) {
			JS_ReportError(cx, "Invalid second argument - should be array of numbers");
			return JS_FALSE;
		}
		if (coordinates.size() < 3) {
			JS_ReportError(cx, "Invalid size of second argument array: %d - should be 3 at least", coordinates.size());
			return JS_FALSE;
		}
		hasAngle = true;
	} else if (argc == 3) {
		if (!toJsDoubleVector(cx, JS_ARGV(cx, vp), 3, coordinates)) {
			JS_ReportError(cx, "Error converting Arguments to Array of Numbers");
			return JS_FALSE;
		}
	} else {
		if (!toJsDouble(cx, *JS_ARGV(cx, vp), angle)) {
			JS_ReportError(cx, "First argument is not of Number type");
			return JS_FALSE;
		}
		if (!toJsDoubleVector(cx, JS_ARGV(cx, vp) + 1, 3, coordinates)) {
			JS_ReportError(cx, "Error converting Arguments to Array of Numbers");
			return JS_FALSE;
		}
		hasAngle = true;
	}
	// Checking if this object is of supported type
	if (!isSupportedObject(cx, JS_THIS(cx, vp))) {
		JS_ReportError(cx, "This Object is not of supported type");
		return JS_FALSE;
	}
	// Applying rotate operation to SCAD object and returning this Object
	if (hasAngle) {
		reinterpret_cast<AbstractObject *>(JS_GetPrivate(cx, JS_THIS_OBJECT(cx, vp)))->rotate(
				angle, coordinates[0], coordinates[1], coordinates[2]);
	} else {
		reinterpret_cast<AbstractObject *>(JS_GetPrivate(cx, JS_THIS_OBJECT(cx, vp)))->rotate(
				coordinates[0], coordinates[1], coordinates[2]);
	}
	JS_SET_RVAL(cx, vp, JS_THIS(cx, vp));
	return JS_TRUE;
}

} // namespace js2scad
