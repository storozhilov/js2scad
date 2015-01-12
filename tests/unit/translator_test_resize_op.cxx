#include "translator_test.hxx"
#include <stdexcept>

TEST_F(TranslationCase, TranslateResizeOperationInvalidArguments)
{
	EXPECT_THROW(translator->translate("scad.Cube(12.3, 45.6, 78).resize();", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Insufficient amount of arguments: 0 - should be 1 or 3"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Sphere(12.3).resize(12.3, 45.6);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Insufficient amount of arguments: 2 - should be 1 or 3"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Sphere(12.3).resize(12.3, 45.6, 'abc');", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Error converting Arguments to Array of Numbers"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Sphere(12.3).resize([12.3, 45.6, 'abc']);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid first argument - should be array of numbers"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Sphere(12.3).resize([12.3, 45.6]);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid size of first argument array: 2 - should be 3 at least"));

	resetStreams();
	EXPECT_THROW(translator->translate("var o = {r: scad.Cube(12.3).resize}; o.r(12.3, 45.6, 78);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("This Object is not of supported type"));
}

TEST_F(TranslationCase, TranslateResizeOperation)
{
	translator->translate("scad.Cube(12.3, 45.6, 78).resize(98.7, 65.4, 32.1);", cout, JsFilename);
	EXPECT_EQ("resize([98.7, 65.4, 32.1]) cube([12.3, 45.6, 78], center = false);", cout.str());

	resetStreams();
	translator->translate(
		"var cube = scad.Cube(12.3, 45.6, 78).resize(98.7, 65.4, 32.1).resize(12.3, 45.6, 78.9);",
		cout, JsFilename);
	EXPECT_EQ("resize([12.3, 45.6, 78.9]) resize([98.7, 65.4, 32.1]) cube([12.3, 45.6, 78], center = false);",
		cout.str());

	resetStreams();
	translator->translate(
		"var sphere = scad.Sphere(765.4).resize(64, 86, 25);\n"
		"var union = scad.Union(scad.Cube(12.3, 45.6, 78).resize([6.5, 8.7, 3.4]), sphere, scad.Union(sphere).resize(98.7, 65.4, 32.1));\n"
		"union.resize(98.7, 65.4, 32.1);\n"
		"union.resize(12.3, 45.6, 78.9);",
		cout, JsFilename);
	EXPECT_EQ(
		"resize([12.3, 45.6, 78.9]) resize([98.7, 65.4, 32.1]) union() {\n"
		"  resize([6.5, 8.7, 3.4]) cube([12.3, 45.6, 78], center = false);\n"
		"  resize([64, 86, 25]) sphere(r = 765.4);\n"
		"  resize([98.7, 65.4, 32.1]) union() {\n"
		"    resize([64, 86, 25]) sphere(r = 765.4);\n"
		"  }\n"
		"}",
		cout.str());
}
