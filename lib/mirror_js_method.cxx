#include "translator_impl.hxx"
#include "abstract_object.hxx"

using namespace JS;

namespace js2scad
{

JSBool TranslatorImpl::mirrorMethod(JSContext *cx, uintN argc, jsval *vp)
{
	//std::clog << __PRETTY_FUNCTION__ << " is called" << std::endl;
	// Parameters handling
	if (argc == 0 || argc == 2) {
		JS_ReportError(cx, "Insufficient amount of arguments: %d - should be 1 or 3", argc);
		return JS_FALSE;
	}
	//jsdouble shifts[3];
	std::vector<jsdouble> shifts;
	if (argc == 1) {
		// Processing array argument
		if (!toJsDoubleVector(cx, *JS_ARGV(cx, vp), shifts)) {
			JS_ReportError(cx, "Invalid first argument - should be array of numbers");
			return JS_FALSE;
		}
		if (shifts.size() < 3) {
			JS_ReportError(cx, "Invalid size of first argument array: %d - should be 3 at least", shifts.size());
			return JS_FALSE;
		}
	} else {
		if (!toJsDoubleVector(cx, JS_ARGV(cx, vp), 3, shifts)) {
			JS_ReportError(cx, "Error converting Arguments to Array of Numbers");
			return JS_FALSE;
		}
	}
	// Checking if this object is of supported type
	if (!isSupportedObject(cx, JS_THIS(cx, vp))) {
		JS_ReportError(cx, "This Object is not of supported type");
		return JS_FALSE;
	}
	// Applying mirror operation to SCAD object and returning this Object
	reinterpret_cast<AbstractObject *>(JS_GetPrivate(cx, JS_THIS_OBJECT(cx, vp)))->mirror(
			shifts[0], shifts[1], shifts[2]);
	JS_SET_RVAL(cx, vp, JS_THIS(cx, vp));
	return JS_TRUE;
}

} // namespace js2scad
