#ifndef __JS2SCAD__HXX
#define __JS2SCAD__HXX

#include <ostream>
#include <istream>

namespace js2scad
{

class TranslatorImpl;

class Translator
{
public:
	//! Creates JS to OpenSCAD translator
	/*!
	 * \param cerr Reference to error output stream to write error messages to
	 * \param indentWidth Result indent width
	 */
	Translator(std::ostream& cerr, size_t indentWidth = 2U);
	//! Destroys JS to OpenSCAD translator
	~Translator();

	//! Translates program from input stream to output stream
	/*!
	 * \note Throws std::runtime_error exception on error
	 * \param cin Reference to input stream to read program from
	 * \param cout Reference to input stream to write result to
	 * \param filename Name of the input file (informational - used in JS egnine)
	 */
	void translate(std::istream& cin, std::ostream& cout, const char * filename);
	//! Translates program from string to out stream
	/*!
	 * \note Throws std::runtime_error exception on error
	 * \param program Reference to input stream to read program from
	 * \param cout Reference to input stream to write result to
	 * \param filename Name of the input file (informational - used in JS egnine)
	 */
	void translate(const std::string& program, std::ostream& cout, const char * filename);
private:
	TranslatorImpl * _translatorImpl;
};

} // namespace js2scad

#endif
