cmake_minimum_required(VERSION 2.6)
project(upEngine)

set(BUILD_EXTRA_WARNINGS "Warn" CACHE STRING "Set to Warn (default) or Warn-more to get additional compiler warnings")

if(CMAKE_COMPILER_IS_GNUCXX)
	include(CheckCXXCompilerFlag)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic")
	#FIXME: take out -fpermissive when fixed in code
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
	
	set(COLOR_DIAG_FLAG "-fcolor-diagnostics")
	check_cxx_compiler_flag (${COLOR_DIAG_FLAG} HAVE_COLOR_DIAG_FLAG)
	if(HAVE_COLOR_DIAG_FLAG)
		message ("forcing colored compiler output")
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COLOR_DIAG_FLAG}")
	endif()
	
	set(WARN_EVERYTHING_FLAG "-Weverything")
	# Some warnings that are of absolutely no interest
	set(WARN_NOT_FLAGS "c++98-compat" "c++98-compat-pedantic" "exit-time-destructors")
	if(${BUILD_EXTRA_WARNINGS} STREQUAL "Warn-more")
		set(BUILD_EXTRA_WARNINGS "Warn")
	else()
		# These warnings are often meaningless
		list(APPEND WARN_NOT_FLAGS "padded")
	endif()
	
	check_cxx_compiler_flag (${WARN_EVERYTHING_FLAG} HAVE_WARN_EVERYTHING_FLAG)
	if ((${BUILD_EXTRA_WARNINGS} STREQUAL "Warn") AND (HAVE_WARN_EVERYTHING_FLAG))
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_EVERYTHING_FLAG}")
	endif()
	
	foreach(WARN_FLAG ${WARN_NOT_FLAGS})
		string(REPLACE "+" "x" TEST_FLAG "TEST_W${WARN_FLAG}")
		check_cxx_compiler_flag ("-W${WARN_FLAG}" ${TEST_FLAG})
		if(${TEST_FLAG})
			message("disabling -W${WARN_FLAG}")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-${WARN_FLAG}")
		endif()
	endforeach()
elseif(MSVC)
	#FIXME: this is a guess
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

find_package(assimp REQUIRED)
find_package(FreeImage REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw REQUIRED)
find_package(OpenGL REQUIRED)
add_definitions(${ASSIMP_DEFINITIONS} ${FreeImage_DEFINITIONS} ${FREETYPE_DEFINITIONS} ${GLEW_DEFINITIONS} ${GLFW_DEFINITIONS} ${OPENGL_DEFINITIONS})
include_directories(${ASSIMP_INCLUDE_DIRS} ${FreeImage_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})
link_directories(${ASSIMP_LIBRARY_DIRS} ${FreeImage_LIBRARY_DIRS} ${FREETYPE_LIBRARY_DIRS} ${GLEW_LIBRARY_DIRS} ${GLFW_LIBRARY_DIRS} ${OPENGL_LIBRARY_DIRS})

include_directories(.)

add_executable(upEngine
	AssetManager.cpp
	Camera.cpp
	FreeTypeFont.cpp
	main.cpp
	Mesh.cpp
	Shader.cpp
	ShaderManager.cpp
	Skybox.cpp
	Terrain.cpp
	Texture.cpp
	VBO.cpp
	)
target_link_libraries(upEngine ${ASSIMP_LIBRARIES} ${FreeImage_LIBRARY} ${FREETYPE_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARY} ${OPENGL_LIBRARIES})
