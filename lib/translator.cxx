#include "js2scad.hxx"
#include "translator_impl.hxx"

namespace js2scad
{

Translator::Translator(std::istream& in, std::ostream& out,
			std::ostream& err, std::ostream& log, size_t indentWidth) :
	_translatorImpl(new TranslatorImpl(in, out, err, log, indentWidth))
{}

Translator::~Translator()
{
	delete _translatorImpl;
}

void Translator::translate(std::istream& in, std::ostream& out, const char * filename)
{
	_translatorImpl->translate(in, out, filename);
}

void Translator::translate(const std::string& program, std::ostream& out, const char * filename)
{
	_translatorImpl->translate(program, out, filename);
}

} // namespace js2scad
