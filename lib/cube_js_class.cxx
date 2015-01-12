#include "translator_impl.hxx"
#include "cube_object.hxx"

using namespace JS;

namespace js2scad
{

JSClass TranslatorImpl::cubeInstanceClass = {
	"scad.CubeInstance",
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

JSBool TranslatorImpl::callCube(JSContext *cx, uintN argc, jsval *vp)
{
	// Parameters handling
	if (argc <= 0) {
		JS_ReportError(cx, "Empty arguments");
		return JS_FALSE;
	}
	std::vector<jsdouble> dimensions(3U);
	JSBool center = JS_FALSE;
	int centerArgIndex = -1;
	if (argc <= 2) {
		if (toJsDoubleVector(cx, *(JS_ARGV(cx, vp)), dimensions)) {
			if (dimensions.size() < 3) {
				JS_ReportError(cx, "Invalid size of the first argument array - should be 3 at least");
				return JS_FALSE;
			}
		} else if (toJsDouble(cx, *(JS_ARGV(cx, vp)), dimensions[0])) {
			dimensions[1] = dimensions[0];
			dimensions[2] = dimensions[0];
		} else {
			JS_ReportError(cx, "Invalid first argument value - should be Number or Array of numbers");
			return JS_FALSE;
		}
		if (argc == 2) {
			centerArgIndex = 1;
		}
	} else {
		for (size_t i = 0U; i < 3; ++i) {
			if (!toJsDouble(cx, *(JS_ARGV(cx, vp) + i), dimensions[i])) {
				JS_ReportError(cx, "Invalid cube %d-th dimension value", i + 1);
				return JS_FALSE;
			}
		}
		if (argc > 3) {
			centerArgIndex = 3;
		}
	}
	if ((centerArgIndex >= 0) && !toJsBool(cx, *(JS_ARGV(cx, vp) + centerArgIndex), center)) {
		JS_ReportError(cx, "Invalid center argument value");
		return JS_FALSE;
	}

	// Cube JS object creation
	TranslatorImpl * translator = getTranslator(cx);
	JSObject * cubeJsObject = JS_NewObject(cx, &cubeInstanceClass, translator->_abstractScadObject, NULL);
	if (cubeJsObject == NULL) {
		JS_ReportError(cx, "'scad.CubeInstance' object initialization error");
		return JS_FALSE;
	}

	// Cube SCAD object creation and linking to JS object
	CubeObject * cubeObject = new CubeObject(translator->_objectsCollection, dimensions[0], dimensions[1],
			dimensions[2], center);
	JS_SetPrivate(cx, cubeJsObject, reinterpret_cast<void *>(cubeObject));

	// Returning result
	jsval cubeObjectJsVal = OBJECT_TO_JSVAL(cubeJsObject);
	JS_SET_RVAL(cx, vp, cubeObjectJsVal);
	return JS_TRUE;
}

} // namespace js2scad
