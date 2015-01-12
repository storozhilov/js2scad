cmake_minimum_required (VERSION 2.8)
project (js2scad)

# SpiderMonkey lookup
execute_process (COMMAND pkg-config --cflags mozjs185
	COMMAND sed s/-I//g
	OUTPUT_VARIABLE SPIDERMONKEY_INCLUDE_DIRS
	OUTPUT_STRIP_TRAILING_WHITESPACE)
string (REPLACE " " ";" SPIDERMONKEY_INCLUDE_DIRS ${SPIDERMONKEY_INCLUDE_DIRS})

execute_process (COMMAND pkg-config --libs mozjs185
	COMMAND sed s/-l//g
	OUTPUT_VARIABLE SPIDERMONKEY_LIBRARIES
	OUTPUT_STRIP_TRAILING_WHITESPACE)
string (REPLACE " " ";" SPIDERMONKEY_LIBRARIES ${SPIDERMONKEY_LIBRARIES})

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} --coverage -O0")

set (JS2SCAD_LIBRARY_SHARED ${PROJECT_NAME}_library_shared)
set (JS2SCAD_LIBRARY_STATIC ${PROJECT_NAME}_library_static)

# Library
add_subdirectory (lib)

# CLI frontend to library
add_subdirectory (bin)

# Testing
enable_testing ()
add_subdirectory (tests)

# Coverage
find_program (GCOVR_PATH gcovr)
if (GCOVR_PATH)
	add_custom_target (coverage-xml
		COMMAND ${GCOVR_PATH} --xml -r "${CMAKE_SOURCE_DIR}" --object-directory "${CMAKE_BINARY_DIR}" -o coverage.xml -e test_* 2>&1 >/dev/null
		WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
	add_custom_target (coverage
		COMMAND ${CMAKE_COMMAND} -E remove -f coverage*.html
		COMMAND ${GCOVR_PATH} --html --html-details -r "${CMAKE_SOURCE_DIR}" --object-directory "${CMAKE_BINARY_DIR}" -o coverage.html 2>&1 -e test_* >/dev/null
		WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
else ()
	message (WARNING "GCovr executable not found - coverage report is not available")
endif ()
