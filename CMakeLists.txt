cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

project(PlyImporter C)

file(GLOB_RECURSE OI_SRC PlyImporter/src/*.c)
add_library(PlyImporter ${OI_SRC})
set(PLY_IMPORTER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/PlyImporter/include)
target_include_directories(PlyImporter PUBLIC 
	${PLY_IMPORTER_INCLUDE_DIR}
)

option(PLY_IMPORTER_BUILD_EXAMPLE OFF)
if (PLY_IMPORTER_BUILD_EXAMPLE)
file(GLOB_RECURSE PLY_EXAMPLE_SRC PlyExample/src/*.c)
add_executable(PlyExample ${PLY_EXAMPLE_SRC})
target_link_libraries(PlyExample PUBLIC 
	PlyImporter
)
set_target_properties( PlyExample PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
	VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
endif()

set_target_properties( PlyImporter PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)