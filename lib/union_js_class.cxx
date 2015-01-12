#include "translator_impl.hxx"
#include "union_object.hxx"

using namespace JS;

namespace js2scad
{

JSClass TranslatorImpl::unionInstanceClass = {
	"scad.UnionInstance",
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

JSBool TranslatorImpl::callUnion(JSContext *cx, uintN argc, jsval *vp)
{
	//std::clog << __PRETTY_FUNCTION__ << " is called" << std::endl;
	std::vector<AbstractObject *> children;
	// Parameters handling
	if (argc == 1U && JSVAL_IS_OBJECT(*JS_ARGV(cx, vp)) && JS_IsArrayObject(cx, JSVAL_TO_OBJECT(*JS_ARGV(cx, vp)))) {
		// Handling array param
		JSObject * jsObject = JSVAL_TO_OBJECT(*JS_ARGV(cx, vp)); 
		jsuint arrayLength;
		if (!JS_GetArrayLength(cx, jsObject, &arrayLength)) {
			JS_ReportError(cx, "Array length retrival error");
			return JS_FALSE;
		}
		children.resize(arrayLength);
		for (size_t i = 0U; i < arrayLength; ++i) {
			jsval itemJsVal;
			if (!JS_GetElement(cx, jsObject, i, &itemJsVal)) {
				JS_ReportError(cx, "%d-th array element retrival error", i + 1);
				return false;
			}
			if (!isSupportedObject(cx, itemJsVal)) {
				JS_ReportError(cx, "%d-th array element is not of supported type", i + 1);
				return JS_FALSE;
			}
			children[i] = reinterpret_cast<AbstractObject *>(JS_GetPrivate(cx, JSVAL_TO_OBJECT(itemJsVal)));
		}
	} else {
		// Handling Arguments array
		children.resize(argc);
		for (size_t i = 0U; i < argc; ++i) {
			if (!isSupportedObject(cx, *(JS_ARGV(cx, vp) + i))) {
				JS_ReportError(cx, "%d-th argument is not of supported type", i + 1);
				return JS_FALSE;
			}
			children[i] = reinterpret_cast<AbstractObject *>(JS_GetPrivate(cx,
							JSVAL_TO_OBJECT(*(JS_ARGV(cx, vp) + i))));
		}
	}

	// Union JS object creation
	TranslatorImpl * translator = getTranslator(cx);
	JSObject * unionJsObject = JS_NewObject(cx, &unionInstanceClass, translator->_abstractScadObject, NULL);
	if (unionJsObject == NULL) {
		JS_ReportError(cx, "'scad.UnionInstance' object initialization error");
		return JS_FALSE;
	}

	// Union SCAD object creation and linking to JS object
	UnionObject * unionObject = new UnionObject(translator->_objectsCollection);
	for (size_t i = 0; i < children.size(); ++i) {
		unionObject->addChild(*children[i]);
	}
	JS_SetPrivate(cx, unionJsObject, reinterpret_cast<void *>(unionObject));

	// Returning result
	jsval unionObjectJsVal = OBJECT_TO_JSVAL(unionJsObject);
	JS_SET_RVAL(cx, vp, unionObjectJsVal);
	return JS_TRUE;
}

} // namespace js2scad
