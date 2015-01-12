#include "js2scad.hxx"
#include <iostream>

int main(int argc, char* argv[])
{
	try {
		js2scad::Translator translator(std::cerr);
		translator.translate(std::cin, std::cout, "[stdin]");
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
