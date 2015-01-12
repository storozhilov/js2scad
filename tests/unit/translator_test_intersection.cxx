#include "translator_test.hxx"
#include <stdexcept>

TEST_F(TranslationCase, TranslateIntersectionInvalidArguments)
{
	// Arguments array API
	EXPECT_THROW(translator->translate("scad.Intersection(123, 'abc');", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("1-th argument is not of supported type"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Intersection(123, 'abc');", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("1-th argument is not of supported type"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Intersection({foo: 'bar'}, 'abc');", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("1-th argument is not of supported type"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Intersection({foo: 'bar'}, 'abc');", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("1-th argument is not of supported type"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Intersection(scad.Cube(123, 456, 789), 'abc');", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("2-th argument is not of supported type"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Intersection(scad.Cube(123, 456, 789), 'abc');", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("2-th argument is not of supported type"));

	// Array API
	resetStreams();
	EXPECT_THROW(translator->translate("scad.Intersection([123, 'abc']);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("1-th array element is not of supported type"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Intersection([{foo: 'bar'}, 'abc']);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("1-th array element is not of supported type"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Intersection([scad.Cube(123, 456, 789), 'abc']);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("2-th array element is not of supported type"));
}

TEST_F(TranslationCase, TranslateIntersection)
{
	translator->translate("scad.Intersection();", cout, JsFilename);
	EXPECT_EQ("intersection() {}", cout.str());

	// Arguments array API
	resetStreams();
	translator->translate(
		"scad.Intersection(\n"
		"  scad.Cube(98.432, 56.34, 765.87),\n"
		"  scad.Sphere(123.45),\n"
		"  scad.Cylinder(34.5, {r1: 56.2, r2: 92.5})\n"
		");",
		cout, JsFilename);
	EXPECT_EQ(
		"intersection() {\n"
		"  cube([98.432, 56.34, 765.87], center = false);\n"
		"  sphere(r = 123.45);\n"
		"  cylinder(h = 34.5, r1 = 56.2, r2 = 92.5);\n"
		"}",
		cout.str());

	resetStreams();
	translator->translate(
		"new scad.Intersection(\n"
		"  scad.Cube(98.432, 56.34, 765.87),\n"
		"  scad.Sphere(123.45),\n"
		"  scad.Cylinder(34.5, {r1: 56.2, r2: 92.5})\n"
		");",
		cout, JsFilename);
	EXPECT_EQ(
		"intersection() {\n"
		"  cube([98.432, 56.34, 765.87], center = false);\n"
		"  sphere(r = 123.45);\n"
		"  cylinder(h = 34.5, r1 = 56.2, r2 = 92.5);\n"
		"}",
		cout.str());
	
	// Array API
	resetStreams();
	translator->translate(
		"scad.Intersection([\n"
		"  scad.Cube(98.432, 56.34, 765.87),\n"
		"  scad.Sphere(123.45),\n"
		"  scad.Cylinder(34.5, {r1: 56.2, r2: 92.5})\n"
		"]);",
		cout, JsFilename);
	EXPECT_EQ(
		"intersection() {\n"
		"  cube([98.432, 56.34, 765.87], center = false);\n"
		"  sphere(r = 123.45);\n"
		"  cylinder(h = 34.5, r1 = 56.2, r2 = 92.5);\n"
		"}",
		cout.str());

	resetStreams();
	translator->translate(
		"new scad.Intersection([\n"
		"  scad.Cube(98.432, 56.34, 765.87),\n"
		"  scad.Sphere(123.45),\n"
		"  scad.Cylinder(34.5, {r1: 56.2, r2: 92.5})\n"
		"]);",
		cout, JsFilename);
	EXPECT_EQ(
		"intersection() {\n"
		"  cube([98.432, 56.34, 765.87], center = false);\n"
		"  sphere(r = 123.45);\n"
		"  cylinder(h = 34.5, r1 = 56.2, r2 = 92.5);\n"
		"}",
		cout.str());
}
