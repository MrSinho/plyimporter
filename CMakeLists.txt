cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

project(PlyImporter C)

add_library(plyimporter PlyImporter/src/plyimporter/plyImporter.c)
set(PLY_IMPORTER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/PlyImporter/include)
target_include_directories(plyimporter PUBLIC 
	${PLY_IMPORTER_INCLUDE_DIR}
)

option(PLY_IMPORTER_BUILD_EXAMPLE OFF)
if (PLY_IMPORTER_BUILD_EXAMPLE)
add_executable(plyexample PlyExample/src/plyExample.c)
target_link_libraries(plyexample PUBLIC 
	plyimporter
)
set_target_properties(plyexample PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
	VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
endif()

set_target_properties( plyimporter PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)