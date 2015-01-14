#include "translator_impl.hxx"
#include <stdexcept>
#include <sstream>
#include <iostream>

using namespace JS;

namespace js2scad
{

TranslatorImpl::TranslatorImpl(std::istream& in, std::ostream& out, std::ostream& err,
		std::ostream& log, size_t indentWidth) :
	_in(in),
	_out(out),
	_err(err),
	_log(log),
	_indentWidth(indentWidth),
	_rt(),
	_cx(),
	_errors(),
	_scadNamespace(),
	_abstractScadObject(),
	//_translateFunction(),
	_objectsCollection(*this)
{
	_rt = JS_NewRuntime(8L * 1024L * 1024L);
	if (_rt == NULL) {
		throw std::runtime_error("JS runtime initialization error");
	}
	_cx = JS_NewContext(_rt, 8192);
	if (_cx == NULL) {
		throw std::runtime_error("JS context initialization error");
	}
	JS_SetContextPrivate(_cx, this);
	JS_SetErrorReporter(_cx, errorReporter);
	static JSClass globalClass = {
		"global",
		JSCLASS_GLOBAL_FLAGS,
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
	JSObject * global = JS_NewCompartmentAndGlobalObject(_cx, &globalClass, NULL);
	if (global == NULL) {
		throw std::runtime_error("Global object initialization error");
	}
	if (!JS_InitStandardClasses(_cx, global)) {
		throw std::runtime_error("Standard classes initialization error");
	}
	_scadNamespace = JS_DefineObject(_cx, global, "scad", NULL, NULL, 0);
	if (_scadNamespace == NULL) {
		throw std::runtime_error("'scad' object initialization error");
	}
	// Registering abstract SCAD object
	_abstractScadObject = JS_DefineObject(_cx, _scadNamespace, "AbstractObject", NULL, NULL, 0);
	if (_abstractScadObject == NULL) {
		throw std::runtime_error("'scad.AbstractObject' object initialization error");
	}
	JSFunction * translateFunction = JS_DefineFunction(_cx, _abstractScadObject, "translate",
			translateMethod, 3, 0);
	if (translateFunction == NULL) {
		throw std::runtime_error("'scad.AbstractObject.translate()' function object initialization error");
	}
	JSFunction * scaleFunction = JS_DefineFunction(_cx, _abstractScadObject, "scale",
			scaleMethod, 3, 0);
	if (scaleFunction == NULL) {
		throw std::runtime_error("'scad.AbstractObject.scale()' function object initialization error");
	}
	JSFunction * mirrorFunction = JS_DefineFunction(_cx, _abstractScadObject, "mirror",
			mirrorMethod, 3, 0);
	if (mirrorFunction == NULL) {
		throw std::runtime_error("'scad.AbstractObject.mirror()' function object initialization error");
	}
	JSFunction * resizeFunction = JS_DefineFunction(_cx, _abstractScadObject, "resize",
			resizeMethod, 3, 0);
	if (resizeFunction == NULL) {
		throw std::runtime_error("'scad.AbstractObject.resize()' function object initialization error");
	}
	JSFunction * rotateFunction = JS_DefineFunction(_cx, _abstractScadObject, "rotate",
			rotateMethod, 3, 0);
	if (rotateFunction == NULL) {
		throw std::runtime_error("'scad.AbstractObject.rotate()' function object initialization error");
	}
	// Creating scad.translate() function object
	/*static JSClass translateFunctionClass = {
		"scad.translate",
		0,
		JS_PropertyStub,
		JS_PropertyStub,
		JS_PropertyStub,
		JS_StrictPropertyStub,
		JS_EnumerateStub,
		JS_ResolveStub,
		JS_ConvertStub,
		JS_FinalizeStub,
		NULL, NULL,
		translateMethod, NULL,
		NULL, NULL, NULL, NULL
	};
	_translateFunction = JS_DefineObject(_cx, _scadNamespace, "translate", &translateFunctionClass, NULL, 0);
	if (_translateFunction == NULL) {
		throw std::runtime_error("'scad.translate()' function object initialization error");
	}*/
	// Registering scad.Cube constructor/function object
	static JSClass cubeClass = {
		"scad.Cube",
		0,
		JS_PropertyStub,
		JS_PropertyStub,
		JS_PropertyStub,
		JS_StrictPropertyStub,
		JS_EnumerateStub,
		JS_ResolveStub,
		JS_ConvertStub,
		JS_FinalizeStub,
		NULL, NULL,
		callCube, callCube,
		NULL, NULL, NULL, NULL
	};
	JSObject * cubeCtor = JS_DefineObject(_cx, _scadNamespace, "Cube", &cubeClass, NULL, 0);
	if (cubeCtor == NULL) {
		throw std::runtime_error("'scad.Cube' object initialization error");
	}
	// Registering scad.Sphere constructor/function object
	static JSClass sphereClass = {
		"scad.Sphere",
		0,
		JS_PropertyStub,
		JS_PropertyStub,
		JS_PropertyStub,
		JS_StrictPropertyStub,
		JS_EnumerateStub,
		JS_ResolveStub,
		JS_ConvertStub,
		JS_FinalizeStub,
		NULL, NULL,
		callSphere, callSphere,
		NULL, NULL, NULL, NULL
	};
	JSObject * sphereCtor = JS_DefineObject(_cx, _scadNamespace, "Sphere", &sphereClass, NULL, 0);
	if (sphereCtor == NULL) {
		throw std::runtime_error("'scad.Sphere' object initialization error");
	}
	// Registering scad.Cylinder constructor/function object
	static JSClass cylinderClass = {
		"scad.Cylinder",
		0,
		JS_PropertyStub,
		JS_PropertyStub,
		JS_PropertyStub,
		JS_StrictPropertyStub,
		JS_EnumerateStub,
		JS_ResolveStub,
		JS_ConvertStub,
		JS_FinalizeStub,
		NULL, NULL,
		callCylinder, callCylinder,
		NULL, NULL, NULL, NULL
	};
	JSObject * cylinderCtor = JS_DefineObject(_cx, _scadNamespace, "Cylinder", &cylinderClass, NULL, 0);
	if (cylinderCtor == NULL) {
		throw std::runtime_error("'scad.Cylinder' object initialization error");
	}
	// Registering scad.Polyhedron constructor/function object
	static JSClass polyhedronClass = {
		"scad.Polyhedron",
		0,
		JS_PropertyStub,
		JS_PropertyStub,
		JS_PropertyStub,
		JS_StrictPropertyStub,
		JS_EnumerateStub,
		JS_ResolveStub,
		JS_ConvertStub,
		JS_FinalizeStub,
		NULL, NULL,
		callPolyhedron, callPolyhedron,
		NULL, NULL, NULL, NULL
	};
	JSObject * polyhedronCtor = JS_DefineObject(_cx, _scadNamespace, "Polyhedron", &polyhedronClass, NULL, 0);
	if (polyhedronCtor == NULL) {
		throw std::runtime_error("'scad.Polyhedron' object initialization error");
	}
	// Registering scad.Union constructor/function object
	static JSClass unionClass = {
		"scad.Union",
		0,
		JS_PropertyStub,
		JS_PropertyStub,
		JS_PropertyStub,
		JS_StrictPropertyStub,
		JS_EnumerateStub,
		JS_ResolveStub,
		JS_ConvertStub,
		JS_FinalizeStub,
		NULL, NULL,
		callUnion, callUnion,
		NULL, NULL, NULL, NULL
	};
	JSObject * unionCtor = JS_DefineObject(_cx, _scadNamespace, "Union", &unionClass, NULL, 0);
	if (unionCtor == NULL) {
		throw std::runtime_error("'scad.Union' object initialization error");
	}
	// Registering scad.Difference constructor/function object
	static JSClass differenceClass = {
		"scad.Difference",
		0,
		JS_PropertyStub,
		JS_PropertyStub,
		JS_PropertyStub,
		JS_StrictPropertyStub,
		JS_EnumerateStub,
		JS_ResolveStub,
		JS_ConvertStub,
		JS_FinalizeStub,
		NULL, NULL,
		callDifference, callDifference,
		NULL, NULL, NULL, NULL
	};
	JSObject * differenceCtor = JS_DefineObject(_cx, _scadNamespace, "Difference", &differenceClass, NULL, 0);
	if (differenceCtor == NULL) {
		throw std::runtime_error("'scad.Difference' object initialization error");
	}
	// Registering scad.Intersection constructor/function object
	static JSClass intersectionClass = {
		"scad.Intersection",
		0,
		JS_PropertyStub,
		JS_PropertyStub,
		JS_PropertyStub,
		JS_StrictPropertyStub,
		JS_EnumerateStub,
		JS_ResolveStub,
		JS_ConvertStub,
		JS_FinalizeStub,
		NULL, NULL,
		callIntersection, callIntersection,
		NULL, NULL, NULL, NULL
	};
	JSObject * intersectionCtor = JS_DefineObject(_cx, _scadNamespace, "Intersection", &intersectionClass, NULL, 0);
	if (intersectionCtor == NULL) {
		throw std::runtime_error("'scad.Intersection' object initialization error");
	}
}

TranslatorImpl::~TranslatorImpl()
{
	JS_DestroyContext(_cx);
	JS_DestroyRuntime(_rt);
}

void TranslatorImpl::translate(std::istream& in, std::ostream& out, const char * filename)
{
	std::istreambuf_iterator<char> eos;
	translate(std::string(std::istreambuf_iterator<char>(in), eos), out, filename);
}

void TranslatorImpl::translate(const std::string& program, std::ostream& out, const char * filename)
{
	_objectsCollection.reset();
	_errors.clear();
	jsval result;
	if (!JS_EvaluateScript(_cx, JS_GetGlobalObject(_cx), program.data(),
				program.length(), filename, 1, &result)) {
		// TODO:
		std::ostringstream msg;
		for (ErrorsContainer::iterator i = _errors.begin(); i != _errors.end(); ++i) {
			if (i != _errors.begin()) {
				msg << std::endl;
			}
			msg << *i;
			_err << (*i) << std::endl;
		}
		throw std::runtime_error(msg.str());
	}
	_objectsCollection.toScad(out);
}

void TranslatorImpl::errorReporter(JSContext * cx, const char * message, JSErrorReport * report)
{
	TranslatorImpl * translator = reinterpret_cast<TranslatorImpl *>(JS_GetContextPrivate(cx));
	std::ostringstream msg;
	msg << "JS program execution error at " << report->filename << ':' <<
		report->lineno << ": \"" << message << '"' << std::endl <<
		std::endl << report->linebuf;
	translator->_errors.push_back(msg.str());
}

bool TranslatorImpl::isSupportedObject(JSContext * cx, jsval obj)
{
	if (!JSVAL_IS_OBJECT(obj)) {
		return false;
	}
	JSObject * argJsObject = JSVAL_TO_OBJECT(obj);
	JSClass * argJsClass = JS_GetClass(cx, argJsObject);
	// TODO: Append classes here 
	// TODO: Maybe to think about alternate design of this check?
	return argJsClass == &cubeInstanceClass ||
		argJsClass == &sphereInstanceClass ||
		argJsClass == &cylinderInstanceClass ||
		argJsClass == &polyhedronInstanceClass ||
		argJsClass == &unionInstanceClass ||
		argJsClass == &intersectionInstanceClass ||
		argJsClass == &differenceInstanceClass;
}

bool TranslatorImpl::toJsDouble(JSContext * cx, jsval value, jsdouble& result)
{
	if (!JSVAL_IS_NUMBER(value)) {
		return false;
	}
	if (!JS_ValueToNumber(cx, value, &result)) {
		JS_ReportError(cx, "Converting Number to jsdouble error");
		return false;
	}
	return true;
}

JSObject * TranslatorImpl::toJsArray(JSContext * cx, jsval value, jsuint& len)
{
	if (!JSVAL_IS_OBJECT(value)) {
		return NULL;
	}
	JSObject * jsObject = JSVAL_TO_OBJECT(value);
	if (!JS_IsArrayObject(cx, jsObject)) {
		return NULL;
	}
	if (!JS_GetArrayLength(cx, jsObject, &len)) {
		JS_ReportError(cx, "Array length retrival error");
		return NULL;
	}
	return jsObject;
}

bool TranslatorImpl::toJsDoubleVector(JSContext * cx, jsval value, std::vector<jsdouble>& result)
{
	jsuint arrayLength;
	JSObject * jsObject = toJsArray(cx, value, arrayLength);
	if (jsObject == NULL) {
		return false;
	}
	result.resize(arrayLength);
	for (size_t i = 0U; i < arrayLength; ++i) {
		jsval itemJsVal;
		if (!JS_GetElement(cx, jsObject, i, &itemJsVal)) {
			JS_ReportError(cx, "%d-th array element retrival error", i);
			return false;
		}
		if (!toJsDouble(cx, itemJsVal, result[i])) {
			return false;
		}
	}
	return true;
}

bool TranslatorImpl::toJsDoubleVector(JSContext * cx, jsval * arr, size_t len, std::vector<jsdouble>& result)
{
	result.resize(len);
	for (size_t i = 0; i < len; ++i) {
		if (!toJsDouble(cx, *(arr + i), result[i])) {
			return false;
		}
	}
	return true;
}

bool TranslatorImpl::toJsBool(JSContext * cx, jsval value, JSBool& result)
{
	if (!JSVAL_IS_BOOLEAN(value)) {
		return false;
	}
	result = JSVAL_TO_BOOLEAN(value);
	return true;
}

} // namespace js2scad
