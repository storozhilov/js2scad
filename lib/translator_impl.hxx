#ifndef __JS2SCAD__TRANSLATOR_IMPL__HXX
#define __JS2SCAD__TRANSLATOR_IMPL__HXX

#include "objects_collection.hxx"
#include <deque>
#include <vector>
#include <ostream>
#include <istream>
#include <jsapi.h>

namespace js2scad
{

class TranslatorImpl
{
public:
	//! Creates JS to OpenSCAD translator
	/*!
	 * \param in Reference to standard input stream
	 * \param out Reference to standard output stream
	 * \param err Reference to standard error output stream
	 * \param log Reference to error output stream
	 * \param indentWidth Indent width
	 */
	TranslatorImpl(std::istream& in, std::ostream& out, std::ostream& err,
			std::ostream& log, size_t indentWidth = 2U);
	~TranslatorImpl();

	inline size_t getIndentWidth() const
	{
		return _indentWidth;
	}

	//! Translates program from in stream to out stream
	void translate(std::istream& in, std::ostream& out, const char * filename);
	//! Translates program from string to out stream
	void translate(const std::string& program, std::ostream& out, const char * filename);
private:
	typedef std::deque<std::string> ErrorsContainer;
	// Solids
	static JSClass cubeInstanceClass;
	static JSClass sphereInstanceClass;
	static JSClass cylinderInstanceClass;
	static JSClass polyhedronInstanceClass;
	// Set operations
	static JSClass unionInstanceClass;
	static JSClass intersectionInstanceClass;
	static JSClass differenceInstanceClass;

	// General methods
	static JSBool includeFunction(JSContext *cx, uintN argc, jsval *vp);
	// Transformations
	static JSBool translateMethod(JSContext *cx, uintN argc, jsval *vp);
	static JSBool scaleMethod(JSContext *cx, uintN argc, jsval *vp);
	static JSBool mirrorMethod(JSContext *cx, uintN argc, jsval *vp);
	static JSBool resizeMethod(JSContext *cx, uintN argc, jsval *vp);
	static JSBool rotateMethod(JSContext *cx, uintN argc, jsval *vp);
	// Constructors of solids
	static JSBool callCube(JSContext *cx, uintN argc, jsval *vp);
	static JSBool callSphere(JSContext *cx, uintN argc, jsval *vp);
	static JSBool callCylinder(JSContext *cx, uintN argc, jsval *vp);
	static JSBool callPolyhedron(JSContext *cx, uintN argc, jsval *vp);
	// Constructors of set operations
	static JSBool callUnion(JSContext *cx, uintN argc, jsval *vp);
	static JSBool callIntersection(JSContext *cx, uintN argc, jsval *vp);
	static JSBool callDifference(JSContext *cx, uintN argc, jsval *vp);

	static void errorReporter(JSContext * cx, const char * message, JSErrorReport * report);
	inline static TranslatorImpl * getTranslator(JSContext * cx)
	{
		return reinterpret_cast<TranslatorImpl *>(JS_GetContextPrivate(cx));
	}

	static bool isSupportedObject(JSContext * cx, jsval obj);

	static bool toJsDouble(JSContext * cx, jsval value, jsdouble& result);
	static bool toString(JSContext * cx, jsval value, std::string& result);
	static JSObject * toJsArray(JSContext * cx, jsval value, jsuint& len);
	static bool toJsDoubleVector(JSContext * cx, jsval value, std::vector<jsdouble>& result);
	static bool toJsDoubleVector(JSContext * cx, jsval * arr, size_t len, std::vector<jsdouble>& result);
	static bool toJsBool(JSContext * cx, jsval value, JSBool& result);
	//static bool toSupportedObjectsVector(JSContext * cx, jsval value, std::vector<AbstractObject>& result);
	
	std::istream& _in;
	std::ostream& _out;
	std::ostream& _err;
	std::ostream& _log;
	size_t _indentWidth;
	JSRuntime * _rt;
	JSContext * _cx;
	ErrorsContainer _errors;
	JSObject * _scadNamespace;
	JSObject * _abstractScadObject;
	//JSObject * _translateFunction;
	ObjectsCollection _objectsCollection;
};

} // namespace js2scad

#endif
