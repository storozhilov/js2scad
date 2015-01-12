#include "translator_impl.hxx"
#include "cylinder_object.hxx"

using namespace JS;

namespace js2scad
{

JSClass TranslatorImpl::cylinderInstanceClass = {
	"scad.CylinderInstance",
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

JSBool TranslatorImpl::callCylinder(JSContext *cx, uintN argc, jsval *vp)
{
	// Parameters handling
	if (argc <= 0) {
		JS_ReportError(cx, "Empty arguments");
		return JS_FALSE;
	}
	jsdouble height;
	if (!toJsDouble(cx, *(JS_ARGV(cx, vp)), height)) {
		JS_ReportError(cx, "Invalid height value");
		return JS_FALSE;
	}
	bool hasRadius = false;
	jsdouble radius = 0.0;
	bool hasBottomConeRadius = false;
	jsdouble bottomConeRadius = 0.0;
	bool hasTopConeRadius = false;
	jsdouble topConeRadius = 0.0;
	bool hasDiameter = false;
	jsdouble diameter = 0.0;
	bool hasBottomConeDiameter = false;
	jsdouble bottomConeDiameter = 0.0;
	bool hasTopConeDiameter = false;
	jsdouble topConeDiameter = 0.0;
	bool hasCenter = false;
	JSBool center = JS_FALSE;
	bool hasFragmentAngle = false;
	jsdouble fragmentAngle = 0.0;
	bool hasFragmentSize = false;
	jsdouble fragmentSize = 0.0;
	bool hasResolution = false;
	jsdouble resolution = 0.0;
	if (argc > 1) {
		// Second argument handling
		if (!JSVAL_IS_OBJECT(*(JS_ARGV(cx, vp) + 1))) {
			JS_ReportError(cx, "Second argument is not of Object type");
			return JS_FALSE;
		}
		JSObject * jsObject = JSVAL_TO_OBJECT(*(JS_ARGV(cx, vp) + 1));
		// Extracting radius
		jsval val;
		if (!JS_GetProperty(cx, jsObject, "r", &val)) {
			JS_ReportError(cx, "Property existence check error");
			return JS_FALSE;
		}
		if (val != JSVAL_VOID) {
			if (!toJsDouble(cx, val, radius)) {
				JS_ReportError(cx, "Invalid radius value");
				return JS_FALSE;
			}
			hasRadius = true;
		}
		// Extracting bottom cone radius
		if (!JS_GetProperty(cx, jsObject, "r1", &val)) {
			JS_ReportError(cx, "Property existence check error");
			return JS_FALSE;
		}
		if (val != JSVAL_VOID) {
			if (!toJsDouble(cx, val, bottomConeRadius)) {
				JS_ReportError(cx, "Invalid bottom cone radius value");
				return JS_FALSE;
			}
			hasBottomConeRadius = true;
		}
		// Extracting top cone radius
		if (!JS_GetProperty(cx, jsObject, "r2", &val)) {
			JS_ReportError(cx, "Property existence check error");
			return JS_FALSE;
		}
		if (val != JSVAL_VOID) {
			if (!toJsDouble(cx, val, topConeRadius)) {
				JS_ReportError(cx, "Invalid top cone radius value");
				return JS_FALSE;
			}
			hasTopConeRadius = true;
		}
		// Extracting diameter
		if (!JS_GetProperty(cx, jsObject, "d", &val)) {
			JS_ReportError(cx, "Property existence check error");
			return JS_FALSE;
		}
		if (val != JSVAL_VOID) {
			if (!toJsDouble(cx, val, diameter)) {
				JS_ReportError(cx, "Invalid diameter value");
				return JS_FALSE;
			}
			hasDiameter = true;
		}
		// Extracting bottom cone diameter
		if (!JS_GetProperty(cx, jsObject, "d1", &val)) {
			JS_ReportError(cx, "Property existence check error");
			return JS_FALSE;
		}
		if (val != JSVAL_VOID) {
			if (!toJsDouble(cx, val, bottomConeDiameter)) {
				JS_ReportError(cx, "Invalid bottom cone diameter value");
				return JS_FALSE;
			}
			hasBottomConeDiameter = true;
		}
		// Extracting top cone diameter
		if (!JS_GetProperty(cx, jsObject, "d2", &val)) {
			JS_ReportError(cx, "Property existence check error");
			return JS_FALSE;
		}
		if (val != JSVAL_VOID) {
			if (!toJsDouble(cx, val, topConeDiameter)) {
				JS_ReportError(cx, "Invalid top cone diameter value");
				return JS_FALSE;
			}
			hasTopConeDiameter = true;
		}
		// Extracting center flag
		if (!JS_GetProperty(cx, jsObject, "center", &val)) {
			JS_ReportError(cx, "Property existence check error");
			return JS_FALSE;
		}
		if (val != JSVAL_VOID) {
			if (!toJsBool(cx, val, center)) {
				JS_ReportError(cx, "Invalid center flag value");
				return JS_FALSE;
			}
			hasCenter = true;
		}
		// Extracting fragment angle
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

	// Cylinder JS object creation
	TranslatorImpl * translator = getTranslator(cx);
	JSObject * cylinderJsObject = JS_NewObject(cx, &cylinderInstanceClass, translator->_abstractScadObject, NULL);
	if (cylinderJsObject == NULL) {
		JS_ReportError(cx, "'scad.CylinderInstance' object initialization error");
		return JS_FALSE;
	}

	// Cylinder SCAD object creation and linking to JS object
	CylinderObject * cylinderObject = new CylinderObject(translator->_objectsCollection, height);
	if (hasRadius) {
		cylinderObject->setRadius(radius);
	}
	if (hasBottomConeRadius) {
		cylinderObject->setBottomConeRadius(bottomConeRadius);
	}
	if (hasTopConeRadius) {
		cylinderObject->setTopConeRadius(topConeRadius);
	}
	if (hasDiameter) {
		cylinderObject->setDiameter(diameter);
	}
	if (hasBottomConeDiameter) {
		cylinderObject->setBottomConeDiameter(bottomConeDiameter);
	}
	if (hasTopConeDiameter) {
		cylinderObject->setTopConeDiameter(topConeDiameter);
	}
	if (hasCenter) {
		cylinderObject->setCenter(center);
	}
	if (hasFragmentAngle) {
		cylinderObject->setFragmentAngle(fragmentAngle);
	}
	if (hasFragmentSize) {
		cylinderObject->setFragmentSize(fragmentSize);
	}
	if (hasResolution) {
		cylinderObject->setResolution(resolution);
	}
	JS_SetPrivate(cx, cylinderJsObject, reinterpret_cast<void *>(cylinderObject));

	// Returning result
	jsval cylinderObjectJsVal = OBJECT_TO_JSVAL(cylinderJsObject);
	JS_SET_RVAL(cx, vp, cylinderObjectJsVal);
	return JS_TRUE;
}

} // namespace js2scad
