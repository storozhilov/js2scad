#include "translator_test.hxx"
#include <stdexcept>
#include <fstream>

TEST_F(TranslationCase, TranslateIncludeOperationInvalidArguments)
{
	EXPECT_THROW(translator->translate("scad.include(\"include_file.js\", 1.23);",
				std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("2-th argument is not of String type"));
}

TEST_F(TranslationCase, TranslateIncludeOperation)
{

	std::ofstream includeFile1("include_file_01.js");
	includeFile1 << "function makeCube(x, y, z) { return scad.Cube(x, y, z).rotate(98.7, 65.4, 32.1); }";
	includeFile1.close();

	std::ofstream includeFile2("include_file_02.js");
	includeFile2 << "function makeSphere(r) { return scad.Sphere(r).rotate(64, 86, 25); }";
	includeFile2.close();

	translator->translate(
			"scad.include(\"include_file_01.js\", \"include_file_02.js\");\n"
			"makeCube(12.3, 45.6, 78);\n"
			"makeSphere(765.4);", cout, JsFilename);
	EXPECT_EQ("rotate(a = [98.7, 65.4, 32.1]) cube([12.3, 45.6, 78], center = false);\n"
		"rotate(a = [64, 86, 25]) sphere(r = 765.4);", cout.str());
}
