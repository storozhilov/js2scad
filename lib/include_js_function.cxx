#include "translator_impl.hxx"
#include <sstream>
#include <fstream>

using namespace JS;

namespace js2scad
{

typedef std::deque<std::string> FilenamesContainer;

JSBool TranslatorImpl::includeFunction(JSContext *cx, uintN argc, jsval *vp)
{
	FilenamesContainer filenamesContainer;
	for (size_t i = 0U; i < argc; ++i) {
		if (!JSVAL_IS_STRING(*(JS_ARGV(cx, vp) + i))) {
			JS_ReportError(cx, "%s: %d-th argument is not of String type", __PRETTY_FUNCTION__, i + 1U);
			return JS_FALSE;
		}
		std::string filename;
		if (!toString(cx, *(JS_ARGV(cx, vp) + i), filename)) {
			JS_ReportError(cx, "%s: Error convesion %d-th argument to string", __PRETTY_FUNCTION__, i + 1U);
			return JS_FALSE;
		}
		filenamesContainer.push_back(filename);
	}
	for (size_t i = 0U; i < filenamesContainer.size(); ++i) {
		// TODO: Include directories support
		std::ifstream in(filenamesContainer[i].c_str());
		if (!in) {
			JS_ReportError(cx, "%s: Error opening '%s' file for reading", __PRETTY_FUNCTION__, 
					filenamesContainer[i].c_str());
			return JS_FALSE;
		}
		// Reading all file to the string
		// TODO: Introduce file size limit
		std::istreambuf_iterator<char> eos;
		std::string program(std::istreambuf_iterator<char>(in), eos);
		jsval result;
		if (!JS_EvaluateScript(cx, JS_GetGlobalObject(cx), program.data(),
					program.length(), filenamesContainer[i].c_str(), 1, &result)) {
			return JS_FALSE;
		}
	}
	return JS_TRUE;
}

} // namespace js2scad

