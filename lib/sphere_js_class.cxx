#include "translator_impl.hxx"
#include "sphere_object.hxx"

using namespace JS;

namespace js2scad
{

JSClass TranslatorImpl::sphereInstanceClass = {
	"scad.SphereInstance",
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

JSBool TranslatorImpl::callSphere(JSContext *cx, uintN argc, jsval *vp)
{
	// Parameters handling
	if (argc < 1) {
		JS_ReportError(cx, "Insufficient amount of arguments: %d - should be 1 or 2", argc);
		return JS_FALSE;
	}
	jsdouble radius;
	if (!toJsDouble(cx, *(JS_ARGV(cx, vp)), radius)) {
		JS_ReportError(cx, "Invalid radius value");
		return JS_FALSE;
	}
	bool hasFragmentAngle = false;
	jsdouble fragmentAngle = 0.0;
	bool hasFragmentSize = false;
	jsdouble fragmentSize = 0.0;
	bool hasResolution = false;
	jsdouble resolution = 0.0;
	if (argc >= 2) {
		if (!JSVAL_IS_OBJECT(*(JS_ARGV(cx, vp) + 1))) {
			JS_ReportError(cx, "Second argument is not of Object type");
			return JS_FALSE;
		}
		JSObject * jsObject = JSVAL_TO_OBJECT(*(JS_ARGV(cx, vp) + 1));
		// Extracting fragment angle
		jsval val;
		if (!JS_GetProperty(cx, jsObject, "fa", &val)) {
			JS_ReportError(cx, "Property existence check error");
			return JS_FALSE;
		}
		if (val != JSVAL_VOID) {
			if (!toJsDouble(cx, val, fragmentAngle)) {
				JS_ReportError(cx, "Invalid fragment angle value");
				return JS_FALSE;
			}
			hasFragmentAngle = true;
		}
		// Extracting fragment size
		if (!JS_GetProperty(cx, jsObject, "fs", &val)) {
			JS_ReportError(cx, "Property existence check error");
			return JS_FALSE;
		}
		if (val != JSVAL_VOID) {
			if (!toJsDouble(cx, val, fragmentSize)) {
				JS_ReportError(cx, "Invalid fragment size value");
				return JS_FALSE;
			}
			hasFragmentSize = true;
		}
		// Extracting resolution
		if (!JS_GetProperty(cx, jsObject, "fn", &val)) {
			JS_ReportError(cx, "Property existence check error");
			return JS_FALSE;
		}
		if (val != JSVAL_VOID) {
			if (!toJsDouble(cx, val, resolution)) {
				JS_ReportError(cx, "Invalid resolution value");
				return JS_FALSE;
			}
			hasResolution = true;
		}
	}

	// Sphere JS object creation
	TranslatorImpl * translator = getTranslator(cx);
	JSObject * sphereJsObject = JS_NewObject(cx, &sphereInstanceClass, translator->_abstractScadObject, NULL);
	if (sphereJsObject == NULL) {
		JS_ReportError(cx, "'scad.SphereInstance' object initialization error");
		return JS_FALSE;
	}

	// Sphere SCAD object creation and linking to JS object
	SphereObject * sphereObject = new SphereObject(translator->_objectsCollection, radius);
	if (hasFragmentAngle) {
		sphereObject->setFragmentAngle(fragmentAngle);
	}
	if (hasFragmentSize) {
		sphereObject->setFragmentSize(fragmentSize);
	}
	if (hasResolution) {
		sphereObject->setResolution(resolution);
	}
	JS_SetPrivate(cx, sphereJsObject, reinterpret_cast<void *>(sphereObject));

	// Returning result
	jsval sphereObjectJsVal = OBJECT_TO_JSVAL(sphereJsObject);
	JS_SET_RVAL(cx, vp, sphereObjectJsVal);
	return JS_TRUE;
}

} // namespace js2scad
