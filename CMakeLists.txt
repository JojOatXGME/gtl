cmake_minimum_required(VERSION 3.1)
project( gtl )

# Load packages for cmake
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Create some variables
set(INCLUDE_DIR "include/")
set(SOURCE_DIR "src/")
file(GLOB_RECURSE SOURCE_FILES
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
	"src/*.c" "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
	"include/*.h" "include/*.hpp" "include/*.inc")

# Create source groups (for Visual Studio)
source_group("Headers" FILES ${HEADER_FILES})
source_group("Sources" FILES ${SOURCE_FILES})

# Add binaries
add_library("${PROJECT_NAME}" ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories("${PROJECT_NAME}" PUBLIC "${INCLUDE_DIR}")

# Add include directories of libraries
target_include_directories("${PROJECT_NAME}" PUBLIC ${OpenGL_INCLUDE_DIRS})
target_include_directories("${PROJECT_NAME}" PUBLIC ${GLEW_INCLUDE_DIRS})

# Link with libraries
target_link_libraries("${PROJECT_NAME}" ${OPENGL_LIBRARIES})
target_link_libraries("${PROJECT_NAME}" ${GLEW_LIBRARIES})

# Use C++11
set_target_properties("${PROJECT_NAME}" PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties("${PROJECT_NAME}" PROPERTIES CXX_STANDARD 11)
