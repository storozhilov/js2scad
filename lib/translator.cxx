#include "js2scad.hxx"
#include "translator_impl.hxx"

namespace js2scad
{

Translator::Translator(std::ostream& cerr, size_t indentWidth) :
	_translatorImpl(new TranslatorImpl(cerr, indentWidth))
{}

Translator::~Translator()
{
	delete _translatorImpl;
}

void Translator::translate(std::istream& cin, std::ostream& cout, const char * filename)
{
	_translatorImpl->translate(cin, cout, filename);
}

void Translator::translate(const std::string& program, std::ostream& cout, const char * filename)
{
	_translatorImpl->translate(program, cout, filename);
}

} // namespace js2scad
