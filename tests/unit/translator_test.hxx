#ifndef __JS2SCAD__TRANSLATOR_TEST__HXX
#define __JS2SCAD__TRANSLATOR_TEST__HXX

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include "js2scad.hxx"

using namespace js2scad;

const char * const JsFilename = "[translator_unit_test]";

class TranslationCase : public testing::Test
{
protected:

	inline void resetStreams()
	{
		cout.str("");
		cout.clear();
		cerr.str("");
		cerr.clear();
	}

	virtual void SetUp()
	{
		resetStreams();
		translator.reset(new Translator(cin, cout, cerr, clog));
	}
	virtual void TearDown()
	{}

	std::istringstream cin;
	std::ostringstream cout;
	std::ostringstream cerr;
	std::ostringstream clog;
	std::auto_ptr<Translator> translator;	
};

#endif
