#include "translator_test.hxx"
#include <stdexcept>

TEST_F(TranslationCase, TranslateCylinderInvalidArguments)
{
	EXPECT_THROW(translator->translate("scad.Cylinder();", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Empty arguments"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cylinder();", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Empty arguments"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cylinder('abc');", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid height value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cylinder('abc');", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid height value"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cylinder(98.432, 'abc');", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Second argument is not of Object type"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cylinder(98.432, 'abc');", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Second argument is not of Object type"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cylinder(98.432, {r: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid radius value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cylinder(98.432, {r: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid radius value"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cylinder(98.432, {r1: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid bottom cone radius value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cylinder(98.432, {r1: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid bottom cone radius value"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cylinder(98.432, {r2: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid top cone radius value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cylinder(98.432, {r2: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid top cone radius value"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cylinder(98.432, {d: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid diameter value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cylinder(98.432, {d: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid diameter value"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cylinder(98.432, {d1: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid bottom cone diameter value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cylinder(98.432, {d1: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid bottom cone diameter value"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cylinder(98.432, {d2: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid top cone diameter value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cylinder(98.432, {d2: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid top cone diameter value"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cylinder(98.432, {center: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid center flag value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cylinder(98.432, {center: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid center flag value"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cylinder(123.456, {fa: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid fragment angle value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cylinder(123.456, {fa: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid fragment angle value"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cylinder(123.456, {fs: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid fragment size value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cylinder(123.456, {fs: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid fragment size value"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cylinder(123.456, {fn: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid resolution value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cylinder(123.456, {fn: 'abc'});", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid resolution value"));
}

TEST_F(TranslationCase, TranslateCylinder)
{
	translator->translate("scad.Cylinder(98.432);", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 98.432);", cout.str());

	resetStreams();
	translator->translate("new scad.Cylinder(98.432);", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 98.432);", cout.str());

	resetStreams();
	translator->translate("scad.Cylinder(98.432, {r: 67.5});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 98.432, r = 67.5);", cout.str());

	resetStreams();
	translator->translate("new scad.Cylinder(98.432, {r: 67.5});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 98.432, r = 67.5);", cout.str());

	resetStreams();
	translator->translate("scad.Cylinder(98.432, {r1: 67.5});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 98.432, r1 = 67.5);", cout.str());

	resetStreams();
	translator->translate("new scad.Cylinder(98.432, {r1: 67.5});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 98.432, r1 = 67.5);", cout.str());

	resetStreams();
	translator->translate("scad.Cylinder(98.432, {r2: 67.5});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 98.432, r2 = 67.5);", cout.str());

	resetStreams();
	translator->translate("new scad.Cylinder(98.432, {r2: 67.5});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 98.432, r2 = 67.5);", cout.str());

	resetStreams();
	translator->translate("scad.Cylinder(98.432, {d: 67.5});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 98.432, d = 67.5);", cout.str());

	resetStreams();
	translator->translate("new scad.Cylinder(98.432, {d: 67.5});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 98.432, d = 67.5);", cout.str());

	resetStreams();
	translator->translate("scad.Cylinder(98.432, {d1: 67.5});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 98.432, d1 = 67.5);", cout.str());

	resetStreams();
	translator->translate("new scad.Cylinder(98.432, {d1: 67.5});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 98.432, d1 = 67.5);", cout.str());

	resetStreams();
	translator->translate("scad.Cylinder(98.432, {d2: 67.5});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 98.432, d2 = 67.5);", cout.str());

	resetStreams();
	translator->translate("new scad.Cylinder(98.432, {d2: 67.5});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 98.432, d2 = 67.5);", cout.str());

	resetStreams();
	translator->translate("scad.Cylinder(98.432, {fa: 135});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 98.432, $fa = 135);", cout.str());

	resetStreams();
	translator->translate("new scad.Cylinder(98.432, {fa: 135});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 98.432, $fa = 135);", cout.str());

	resetStreams();
	translator->translate("scad.Cylinder(321.87, {fs: 1.2});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 321.87, $fs = 1.2);", cout.str());

	resetStreams();
	translator->translate("new scad.Cylinder(321.87, {fs: 1.2});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 321.87, $fs = 1.2);", cout.str());

	resetStreams();
	translator->translate("scad.Cylinder(321.87, {fn: 1.7});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 321.87, $fn = 1.7);", cout.str());

	resetStreams();
	translator->translate("new scad.Cylinder(321.87, {fn: 1.7});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 321.87, $fn = 1.7);", cout.str());

	resetStreams();
	translator->translate("scad.Cylinder(321.87, {fa: 135, fs: 1.2});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 321.87, $fa = 135, $fs = 1.2);", cout.str());

	resetStreams();
	translator->translate("new scad.Cylinder(321.87, {fa: 135, fs: 1.2});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 321.87, $fa = 135, $fs = 1.2);", cout.str());

	resetStreams();
	translator->translate("scad.Cylinder(321.87, {fa: 135, fn: 1.7});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 321.87, $fa = 135, $fn = 1.7);", cout.str());

	resetStreams();
	translator->translate("new scad.Cylinder(321.87, {fa: 135, fn: 1.7});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 321.87, $fa = 135, $fn = 1.7);", cout.str());

	resetStreams();
	translator->translate("scad.Cylinder(321.87, {fs: 1.2, fn: 1.7});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 321.87, $fs = 1.2, $fn = 1.7);", cout.str());

	resetStreams();
	translator->translate("new scad.Cylinder(321.87, {fs: 1.2, fn: 1.7});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 321.87, $fs = 1.2, $fn = 1.7);", cout.str());

	resetStreams();
	translator->translate("scad.Cylinder(321.87, {fa: 135, fs: 1.2, fn: 1.7});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 321.87, $fa = 135, $fs = 1.2, $fn = 1.7);", cout.str());

	resetStreams();
	translator->translate("new scad.Cylinder(321.87, {fa: 135, fs: 1.2, fn: 1.7});", cout, JsFilename);
	EXPECT_EQ("cylinder(h = 321.87, $fa = 135, $fs = 1.2, $fn = 1.7);", cout.str());

	resetStreams();
	translator->translate(
			"scad.Cylinder(321.87, {r: 64.78, r1: 93.67, r2: 82.93, d: 86.15, d1: 34.57, d2: 69.96, center: true, fa: 135, fs: 1.2, fn: 1.7});",
			cout, JsFilename);
	EXPECT_EQ("cylinder(h = 321.87, r = 64.78, r1 = 93.67, r2 = 82.93, d = 86.15, d1 = 34.57, d2 = 69.96, center = true, $fa = 135, $fs = 1.2, $fn = 1.7);", cout.str());

	resetStreams();
	translator->translate(
			"new scad.Cylinder(321.87, {r: 64.78, r1: 93.67, r2: 82.93, d: 86.15, d1: 34.57, d2: 69.96, center: true, fa: 135, fs: 1.2, fn: 1.7});",
			cout, JsFilename);
	EXPECT_EQ("cylinder(h = 321.87, r = 64.78, r1 = 93.67, r2 = 82.93, d = 86.15, d1 = 34.57, d2 = 69.96, center = true, $fa = 135, $fs = 1.2, $fn = 1.7);", cout.str());
}
