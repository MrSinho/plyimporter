cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

project(PlyImporter C)

add_library(PlyImporter PlyImporter/src/plyimporter/plyImporter.c)
set(PLY_IMPORTER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/PlyImporter/include)
target_include_directories(PlyImporter PUBLIC 
	${PLY_IMPORTER_INCLUDE_DIR}
)

option(PLY_IMPORTER_BUILD_EXAMPLE OFF)
if (PLY_IMPORTER_BUILD_EXAMPLE)
add_executable(PlyExample PlyExample/src/plyExample.c)
target_link_libraries(PlyExample PUBLIC 
	PlyImporter
)
set_target_properties(PlyExample PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
	VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
endif()

set_target_properties( PlyImporter PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)