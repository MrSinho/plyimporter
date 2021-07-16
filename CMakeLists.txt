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


option(PLY_BUILD_EXAMPLE ON)
if (PLY_BUILD_EXAMPLE)
file(GLOB_RECURSE EXAMPLE_SRC Example/src/*.c)
add_executable(Example ${EXAMPLE_SRC})
target_link_libraries(Example PUBLIC 
	PlyImporter
)
endif(PLY_BUILD_EXAMPLE)

#OUTPUT
set_target_properties( PlyImporter Example PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
	VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)