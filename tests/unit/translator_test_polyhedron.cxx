#include "translator_test.hxx"
#include <stdexcept>

TEST_F(TranslationCase, TranslatePolyhedronInvalidArguments)
{
	EXPECT_THROW(translator->translate("scad.Polyhedron();", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Insufficient amount of arguments - should be 2 at least"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Polyhedron();", std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Insufficient amount of arguments - should be 2 at least"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Polyhedron([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]]);",
				std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Insufficient amount of arguments - should be 2 at least"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Polyhedron([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]]);",
				std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Insufficient amount of arguments - should be 2 at least"));

	resetStreams();
	EXPECT_THROW(translator->translate("scad.Polyhedron('abc', [[0, 1, 2], [0, 1, 3], [1, 2, 3], [0, 2, 3]]);",
				std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("First argument is not of Array type"));

	resetStreams();
	EXPECT_THROW(translator->translate("new scad.Polyhedron('abc', [[0, 1, 2], [0, 1, 3], [1, 2, 3], [0, 2, 3]]);",
				std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("First argument is not of Array type"));

	resetStreams();
	EXPECT_THROW(translator->translate(
				"scad.Polyhedron([[1, 2, 3], [4, 5, 6], 'abc', [10, 11, 12]],\n"
				"  [[0, 1, 2], [0, 1, 3], [1, 2, 3], [0, 2, 3]]);",
				std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("2-th point is not Array of Number"));

	resetStreams();
	EXPECT_THROW(translator->translate(
				"new scad.Polyhedron([[1, 2, 3], [4, 5, 6], 'abc', [10, 11, 12]],\n"
				"  [[0, 1, 2], [0, 1, 3], [1, 2, 3], [0, 2, 3]]);",
				std::cout, JsFilename), std::runtime_error);

	resetStreams();
	EXPECT_THROW(translator->translate(
				"scad.Polyhedron([[1, 2, 3], [4, 5, 6], [7, 8], [10, 11, 12]],\n"
				"  [[0, 1, 2], [0, 1, 3], [1, 2, 3], [0, 2, 3]]);",
				std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("2-th point has less than 3 coordinates"));

	resetStreams();
	EXPECT_THROW(translator->translate(
				"new scad.Polyhedron([[1, 2, 3], [4, 5, 6], [7, 8], [10, 11, 12]],\n"
				"  [[0, 1, 2], [0, 1, 3], [1, 2, 3], [0, 2, 3]]);",
				std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("2-th point has less than 3 coordinates"));

	resetStreams();
	EXPECT_THROW(translator->translate(
				"scad.Polyhedron([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]], 'abc');",
				std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Second argument is not of Array type"));

	resetStreams();
	EXPECT_THROW(translator->translate(
				"new scad.Polyhedron([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]], 'abc');",
				std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Second argument is not of Array type"));

	resetStreams();
	EXPECT_THROW(translator->translate(
				"scad.Polyhedron([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]],\n"
				"  [[0, 1, 2], 'abc', [1, 2, 3], [0, 2, 3]]);",
				std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("1-th face is not Array of Number"));

	resetStreams();
	EXPECT_THROW(translator->translate(
				"new scad.Polyhedron([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]],\n"
				"  [[0, 1, 2], 'abc', [1, 2, 3], [0, 2, 3]]);",
				std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("1-th face is not Array of Number"));

	resetStreams();
	EXPECT_THROW(translator->translate(
				"scad.Polyhedron([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]],\n"
				"  [[0, 1, 2], [0, 1], [1, 2, 3], [0, 2, 3]]);",
				std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("1-th face has less than 3 points"));

	resetStreams();
	EXPECT_THROW(translator->translate(
				"new scad.Polyhedron([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]],\n"
				"  [[0, 1, 2], [0, 1], [1, 2, 3], [0, 2, 3]]);",
				std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("1-th face has less than 3 points"));

	resetStreams();
	EXPECT_THROW(translator->translate(
				"scad.Polyhedron([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]],\n"
				"  [[0, 1, 2], [0, 1, 3], [1, 2, 3], [0, 2, 3]], 'abc');",
				std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Third argument is not of Number type"));

	resetStreams();
	EXPECT_THROW(translator->translate(
				"new scad.Polyhedron([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]],\n"
				"  [[0, 1, 2], [0, 1, 3], [1, 2, 3], [0, 2, 3]], 'abc');",
				std::cout, JsFilename), std::runtime_error);
	EXPECT_NE(std::string::npos, cerr.str().find("Third argument is not of Number type"));
}

TEST_F(TranslationCase, TranslatePolyhedron)
{
	translator->translate(
			"scad.Polyhedron([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]],\n"
			"  [[0, 1, 2], [0, 1, 3], [1, 2, 3], [0, 2, 3]]);",
			cout, JsFilename);
	EXPECT_EQ("polyhedron(points = [[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]], faces = [[0, 1, 2], [0, 1, 3], [1, 2, 3], [0, 2, 3]]);", cout.str());

	resetStreams();
	translator->translate(
			"new scad.Polyhedron([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]],\n"
			"  [[0, 1, 2], [0, 1, 3], [1, 2, 3], [0, 2, 3]]);",
			cout, JsFilename);
	EXPECT_EQ("polyhedron(points = [[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]], faces = [[0, 1, 2], [0, 1, 3], [1, 2, 3], [0, 2, 3]]);", cout.str());

	resetStreams();
	translator->translate(
			"scad.Polyhedron([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]],\n"
			"  [[0, 1, 2], [0, 1, 3], [1, 2, 3], [0, 2, 3]], 3);",
			cout, JsFilename);
	EXPECT_EQ("polyhedron(points = [[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]], faces = [[0, 1, 2], [0, 1, 3], [1, 2, 3], [0, 2, 3]], convexity = 3);", cout.str());

	resetStreams();
	translator->translate(
			"new scad.Polyhedron([[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]],\n"
			"  [[0, 1, 2], [0, 1, 3], [1, 2, 3], [0, 2, 3]], 3);",
			cout, JsFilename);
	EXPECT_EQ("polyhedron(points = [[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12]], faces = [[0, 1, 2], [0, 1, 3], [1, 2, 3], [0, 2, 3]], convexity = 3);", cout.str());
}
