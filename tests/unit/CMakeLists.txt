if ("${GMOCK_SOURCE_DIR}" STREQUAL "")
	message (WARNING "GMOCK_SOURCE_DIR variable not set - unit-tests are not available. Use '-DGMOCK_SOURCE_DIR=<path_to_gmock_sources>' param for CMake")
else ()
	set (gmock_force_shared_crt true CACHE INTERNAL "")
	set (BUILD_SHARED_LIBS false CACHE INTERNAL "")
	add_subdirectory (${GMOCK_SOURCE_DIR} ${CMAKE_BINARY_DIR}/gmock)
	set (GMOCK_LIBRARIES gmock)
	set (GMOCK_INCLUDE_DIRS "${GMOCK_SOURCE_DIR}/include"
		"${GMOCK_SOURCE_DIR}/gtest/include")

	project (js2scad_unit_test)
	include_directories (
		${CMAKE_SOURCE_DIR}/include
		${SPIDERMONKEY_INCLUDE_DIRS}
		${GMOCK_INCLUDE_DIRS}
		${GMOCK_SOURCE_DIR})
	file (GLOB SRC_LIST "*.cxx")
	add_executable (${PROJECT_NAME} ${SRC_LIST})
	target_link_libraries (${PROJECT_NAME}
		${JS2SCAD_LIBRARY_SHARED}
		${SPIDERMONKEY_LIBRARIES}
		${GMOCK_LIBRARIES})
	add_test (${PROJECT_NAME} ${PROJECT_NAME})
endif ()

