cmake_minimum_required(VERSION 3.5)
project(convex_hull_visualization)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/source")
include_directories("${PROJECT_SOURCE_DIR}/source/visualizer")

add_subdirectory(source/visualizer)

add_executable(cvxhull ./source/cvxhull.cpp)
add_executable(gltest ./source/gltest.cpp)

target_link_libraries(cvxhull
	visualizer
	${GLUT_LIBRARIES}
	${OPENGL_LIBRARIES}
)

target_link_libraries(gltest
	${GLUT_LIBRARIES}
	${OPENGL_LIBRARIES}
)

set(CMAKE_BUILD_TYPE Release)