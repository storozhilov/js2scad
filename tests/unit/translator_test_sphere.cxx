#include "translator_test.hxx"
#include <stdexcept>

TEST_F(TranslationCase, TranslateSphereInvalidArguments)
{
	EXPECT_THROW(translator->translate("scad.Sphere();", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Insufficient amount of arguments"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Sphere();", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Insufficient amount of arguments"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Sphere('abc');", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid radius value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Sphere('abc');", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid radius value"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Sphere({foo:'bar',bar:123});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid radius value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Sphere({foo:'bar',bar:123});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid radius value"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Sphere(123.456, 'foobar');", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Second argument is not of Object type"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Sphere(123.456, 'foobar');", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Second argument is not of Object type"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Sphere(123.456, {fa: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid fragment angle value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Sphere(123.456, {fa: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid fragment angle value"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Sphere(123.456, {fs: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid fragment size value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Sphere(123.456, {fs: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid fragment size value"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Sphere(123.456, {fn: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid resolution value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Sphere(123.456, {fn: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid resolution value"));
}

TEST_F(TranslationCase, TranslateSphere)
{
	translator->translate("scad.Sphere(98.432);", cout, JsFilename);
	EXPECT_EQ("sphere(r = 98.432);", cout.str());

	resetStreams();
	translator->translate("new scad.Sphere(98.432);", cout, JsFilename);
	EXPECT_EQ("sphere(r = 98.432);", cout.str());

	resetStreams();
	translator->translate("scad.Sphere(98.432, {fa: 135});", cout, JsFilename);
	EXPECT_EQ("sphere(r = 98.432, $fa = 135);", cout.str());

	resetStreams();
	translator->translate("new scad.Sphere(98.432, {fa: 135});", cout, JsFilename);
	EXPECT_EQ("sphere(r = 98.432, $fa = 135);", cout.str());

	resetStreams();
	translator->translate("scad.Sphere(321.87, {fs: 1.2});", cout, JsFilename);
	EXPECT_EQ("sphere(r = 321.87, $fs = 1.2);", cout.str());

	resetStreams();
	translator->translate("new scad.Sphere(321.87, {fs: 1.2});", cout, JsFilename);
	EXPECT_EQ("sphere(r = 321.87, $fs = 1.2);", cout.str());

	resetStreams();
	translator->translate("scad.Sphere(321.87, {fn: 1.7});", cout, JsFilename);
	EXPECT_EQ("sphere(r = 321.87, $fn = 1.7);", cout.str());

	resetStreams();
	translator->translate("new scad.Sphere(321.87, {fn: 1.7});", cout, JsFilename);
	EXPECT_EQ("sphere(r = 321.87, $fn = 1.7);", cout.str());

	resetStreams();
	translator->translate("scad.Sphere(321.87, {fa: 135, fs: 1.2});", cout, JsFilename);
	EXPECT_EQ("sphere(r = 321.87, $fa = 135, $fs = 1.2);", cout.str());

	resetStreams();
	translator->translate("new scad.Sphere(321.87, {fa: 135, fs: 1.2});", cout, JsFilename);
	EXPECT_EQ("sphere(r = 321.87, $fa = 135, $fs = 1.2);", cout.str());

	resetStreams();
	translator->translate("scad.Sphere(321.87, {fa: 135, fn: 1.7});", cout, JsFilename);
	EXPECT_EQ("sphere(r = 321.87, $fa = 135, $fn = 1.7);", cout.str());

	resetStreams();
	translator->translate("new scad.Sphere(321.87, {fa: 135, fn: 1.7});", cout, JsFilename);
	EXPECT_EQ("sphere(r = 321.87, $fa = 135, $fn = 1.7);", cout.str());

	resetStreams();
	translator->translate("scad.Sphere(321.87, {fs: 1.2, fn: 1.7});", cout, JsFilename);
	EXPECT_EQ("sphere(r = 321.87, $fs = 1.2, $fn = 1.7);", cout.str());

	resetStreams();
	translator->translate("new scad.Sphere(321.87, {fs: 1.2, fn: 1.7});", cout, JsFilename);
	EXPECT_EQ("sphere(r = 321.87, $fs = 1.2, $fn = 1.7);", cout.str());

	resetStreams();
	translator->translate("scad.Sphere(321.87, {fa: 135, fs: 1.2, fn: 1.7});", cout, JsFilename);
	EXPECT_EQ("sphere(r = 321.87, $fa = 135, $fs = 1.2, $fn = 1.7);", cout.str());

	resetStreams();
	translator->translate("new scad.Sphere(321.87, {fa: 135, fs: 1.2, fn: 1.7});", cout, JsFilename);
	EXPECT_EQ("sphere(r = 321.87, $fa = 135, $fs = 1.2, $fn = 1.7);", cout.str());
}
