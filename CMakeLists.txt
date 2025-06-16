#! base
cmake_minimum_required(VERSION "3.10")
project("game_for_school(SFML)"
			VERSION "1.2.0"
    		LANGUAGES "CXX"
		)
set(CMAKE_CXX_STANDARD "17")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)



#! dependencies
# SFML
set(SFML_TAG "2.6.1")
option(BUILD_SHARED_LIBS "Static link" OFF)
option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)

FetchContent_Declare(SFML
					GIT_REPOSITORY "https://github.com/SFML/SFML.git"
  					GIT_TAG "${SFML_TAG}"
				)
FetchContent_MakeAvailable(SFML)

# imgui
set(imgui_TAG "v1.91.0")

FetchContent_Declare(imgui
					GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
					GIT_TAG "${imgui_TAG}"
				)
FetchContent_MakeAvailable(imgui)

# imgui-sfml
set(imgui-sfml_TAG "v2.6")
set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)

FetchContent_Declare(imgui-sfml
					GIT_REPOSITORY "https://github.com/SFML/imgui-sfml.git"
					GIT_TAG "${imgui-sfml_TAG}"
				)
FetchContent_MakeAvailable(imgui-sfml)



#! compiling and linking
include_directories("${CMAKE_SOURCE_DIR}/include")
file(GLOB MY_SOURCE "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(main ${MY_SOURCE})


target_link_libraries(main 
						PRIVATE 
						sfml-graphics
						sfml-main
						sfml-system
						sfml-window
						PUBLIC
						ImGui-SFML::ImGui-SFML
					)
# target_compile_options(main 
# 						PRIVATE 
# 						"/SUBSYSTEM:WINDOWS" 
# 						"/ENTRY:mainCRTStartup"
# 					)