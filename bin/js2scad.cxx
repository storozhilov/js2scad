#include "js2scad.hxx"
#include <iostream>
#include <fstream>
#include <unistd.h>

void printUsage()
{
	std::cout << "js2scad - JavaScript to OpenSCAD translator" << std::endl <<
		"Usage: js2scad -i <in_file.js> -o <out_file.scad>" << std::endl;
}

int main(int argc, char* argv[])
{
	std::string inFileName;
	std::string outFileName;

	// CLI options parsing
	int opt;
	while ((opt = getopt(argc, argv, "i:o:h")) != -1) {
		switch (opt) {
			case 'i':
				inFileName = optarg;
				break;
			case 'o':
				outFileName = optarg;
				break;
			case 'h':
				printUsage();
				return 0;
			default:
				std::cerr << "Invalid option: '" << opt << '\'' << std::endl;
				printUsage();
				return 1;
		}
	}
	bool hasError = false;
	if (inFileName.empty()) {
		std::cerr << "Error: Option '-i' is mandatory"<< std::endl;
		hasError = true;
	}
	if (outFileName.empty()) {
		std::cerr << "Error: Option '-o' is mandatory"<< std::endl;
		hasError = true;
	}
	if (hasError) {
		printUsage();
		return 1;
	}

	// Opening I/O files and running translator
	std::ifstream in;
	in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::ofstream out;
	out.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		in.open(inFileName.c_str());
		out.open(outFileName.c_str(), std::ios_base::in | std::ios_base::trunc);
		js2scad::Translator translator(std::cin, std::cout, std::cerr, std::clog);
		translator.translate(in, out, inFileName.c_str());
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
