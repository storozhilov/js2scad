#include "translator_test.hxx"

int main(int argc, char** argv)
{
	setenv("LANG", "C", 1);
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
