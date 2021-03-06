#include "translator_test.hxx"
#include <stdexcept>

TEST_F(TranslationCase, TranslateCubeInvalidArguments)
{
	EXPECT_THROW(translator->translate("scad.Cube();", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Empty arguments"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cube();", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Empty arguments"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cube('abc', false);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid first argument value - should be Number or Array of numbers"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cube('abc', false);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid first argument value - should be Number or Array of numbers"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cube(123, 456, false);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid cube 3-th dimension value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cube(123, 456, false);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid cube 3-th dimension value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cube('abc', 123.5, 456, false);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid cube 1-th dimension value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cube(123, 'abc', 456, false);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid cube 2-th dimension value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cube(123, 456, 'abc', false);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid cube 3-th dimension value"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Cube([123, 456], false);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid size of the first argument array"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cube([123, 456], false);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid size of the first argument array"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cube(['abc', 123.5, 456], false);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid first argument value - should be Number or Array of numbers"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cube([123, [], 456], false);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid first argument value - should be Number or Array of numbers"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cube([123, 456, {}], false);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid first argument value - should be Number or Array of numbers"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cube(123, 456);", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid center argument value"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Cube([123, 456, 789], 'abc');", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Invalid center argument value"));
}

TEST_F(TranslationCase, TranslateCube)
{
	translator->translate("scad.Cube(98.432);", cout, JsFilename);
	EXPECT_EQ("cube([98.432, 98.432, 98.432], center = false);", cout.str());

	resetStreams();
	translator->translate("new scad.Cube(98.432, true);", cout, JsFilename);
	EXPECT_EQ("cube([98.432, 98.432, 98.432], center = true);", cout.str());

	resetStreams();
	translator->translate("scad.Cube(123, 456.78, 98.432);", cout, JsFilename);
	EXPECT_EQ("cube([123, 456.78, 98.432], center = false);", cout.str());

	resetStreams();
	translator->translate("new scad.Cube(123, 456.78, 98.432);", cout, JsFilename);
	EXPECT_EQ("cube([123, 456.78, 98.432], center = false);", cout.str());

	resetStreams();
	translator->translate("scad.Cube(123, 456.78, 98.432, false);", cout, JsFilename);
	EXPECT_EQ("cube([123, 456.78, 98.432], center = false);", cout.str());

	resetStreams();
	translator->translate("new scad.Cube(123, 456.78, 98.432, true);", cout, JsFilename);
	EXPECT_EQ("cube([123, 456.78, 98.432], center = true);", cout.str());

	resetStreams();
	translator->translate("scad.Cube([123, 456.78, 98.432]);", cout, JsFilename);
	EXPECT_EQ("cube([123, 456.78, 98.432], center = false);", cout.str());

	resetStreams();
	translator->translate("new scad.Cube([123, 456.78, 98.432]);", cout, JsFilename);
	EXPECT_EQ("cube([123, 456.78, 98.432], center = false);", cout.str());

	resetStreams();
	translator->translate("scad.Cube([123, 456.78, 98.432], false);", cout, JsFilename);
	EXPECT_EQ("cube([123, 456.78, 98.432], center = false);", cout.str());

	resetStreams();
	translator->translate("new scad.Cube([123, 456.78, 98.432], true);", cout, JsFilename);
	EXPECT_EQ("cube([123, 456.78, 98.432], center = true);", cout.str());
}
