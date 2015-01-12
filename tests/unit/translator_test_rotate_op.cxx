#include "translator_test.hxx"
#include <stdexcept>

TEST_F(TranslationCase, TranslateRotateOperationInvalidArguments)
{
	EXPECT_THROW(translator->translate("scad.Cube(12.3, 45.6, 78).rotate();", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Empty arguments"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cube(12.3, 45.6, 78).rotate([12.3, 'abc', 7.4]);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid first argument - should be array of numbers"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cube(12.3, 45.6, 78).rotate([12.3, 45.6]);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid size of first argument array: 2 - should be 3 at least"));
	
	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cube(12.3, 45.6, 78).rotate('abc', [12.3, 45.6, 7.4]);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("First argument is not of Number type"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cube(12.3, 45.6, 78).rotate(54.2, [12.3, 'abc', 7.4]);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid second argument - should be array of numbers"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cube(12.3, 45.6, 78).rotate(54.2, [12.3]);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid size of second argument array: 1 - should be 3 at least"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cube(12.3, 45.6, 78).rotate(12.3, 'abc', 7.4);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Error converting Arguments to Array of Numbers"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cube(12.3, 45.6, 78).rotate('abc', 12.3, 82.5, 7.4);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("First argument is not of Number type"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cube(12.3, 45.6, 78).rotate(93.6, 12.3, 'abc', 7.4);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Error converting Arguments to Array of Numbers"));

	resetStreams();
	EXPECT_THROW(translator->translate("var o = {r: scad.Cube(12.3).rotate}; o.r(12.3, 45.6, 78);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("This Object is not of supported type"));
}

TEST_F(TranslationCase, TranslateRotateOperation)
{
	translator->translate("scad.Cube(12.3, 45.6, 78).rotate(98.7, 65.4, 32.1);", cout, JsFilename);
	EXPECT_EQ("rotate(a = [98.7, 65.4, 32.1]) cube([12.3, 45.6, 78], center = false);", cout.str());

	resetStreams();
	translator->translate("scad.Cube(12.3, 45.6, 78).rotate([98.7, 65.4, 32.1]);", cout, JsFilename);
	EXPECT_EQ("rotate(a = [98.7, 65.4, 32.1]) cube([12.3, 45.6, 78], center = false);", cout.str());

	resetStreams();
	translator->translate("scad.Cube(12.3, 45.6, 78).rotate(45.6, 98.7, 65.4, 32.1);", cout, JsFilename);
	EXPECT_EQ("rotate(a = 45.6, v = [98.7, 65.4, 32.1]) cube([12.3, 45.6, 78], center = false);", cout.str());

	resetStreams();
	translator->translate("scad.Cube(12.3, 45.6, 78).rotate(45.6, [98.7, 65.4, 32.1]);", cout, JsFilename);
	EXPECT_EQ("rotate(a = 45.6, v = [98.7, 65.4, 32.1]) cube([12.3, 45.6, 78], center = false);", cout.str());

	//-----------------------------------------------------------------------------

	resetStreams();
	translator->translate(
		"var cube = scad.Cube(12.3, 45.6, 78).rotate([98.7, 65.4, 32.1]).rotate(12.3, 45.6, 78.9);",
		cout, JsFilename);
	EXPECT_EQ("rotate(a = [12.3, 45.6, 78.9]) rotate(a = [98.7, 65.4, 32.1]) cube([12.3, 45.6, 78], center = false);",
		cout.str());

	resetStreams();
	translator->translate(
		"var cube = scad.Cube(12.3, 45.6, 78).rotate(45.6, 98.7, 65.4, 32.1).rotate(45.6, [12.3, 45.6, 78.9]);",
		cout, JsFilename);
	EXPECT_EQ("rotate(a = 45.6, v = [12.3, 45.6, 78.9]) rotate(a = 45.6, v = [98.7, 65.4, 32.1]) cube([12.3, 45.6, 78], center = false);",
		cout.str());

	//-----------------------------------------------------------------------------

	resetStreams();
	translator->translate(
		"var sphere = scad.Sphere(765.4).rotate(64, 86, 25);\n"
		"var union = scad.Union(scad.Cube(12.3, 45.6, 78).rotate([6.5, 8.7, 3.4]), sphere, scad.Union(sphere).rotate(43.2, 98.7, 65.4, 32.1));\n"
		"union.rotate(65.9, [98.7, 65.4, 32.1]);\n"
		"union.rotate(12.3, 45.6, 78.9);",
		cout, JsFilename);
	EXPECT_EQ(
		"rotate(a = [12.3, 45.6, 78.9]) rotate(a = 65.9, v = [98.7, 65.4, 32.1]) union() {\n"
		"  rotate(a = [6.5, 8.7, 3.4]) cube([12.3, 45.6, 78], center = false);\n"
		"  rotate(a = [64, 86, 25]) sphere(r = 765.4);\n"
		"  rotate(a = 43.2, v = [98.7, 65.4, 32.1]) union() {\n"
		"    rotate(a = [64, 86, 25]) sphere(r = 765.4);\n"
		"  }\n"
		"}",
		cout.str());

}
