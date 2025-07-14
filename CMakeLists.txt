#! base
cmake_minimum_required(VERSION "${CMAKE_MINIMUM_REQUIRED_VERSION}")
project("game_for_school(SFML)"
			VERSION "1.2.0"
    		LANGUAGES "CXX"
		)
set(CMAKE_CXX_STANDARD "17")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)


#! dependencies
# SFML
set(SFML_TAG "2.6.2")
option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)

FetchContent_Declare(	
	SFML
	GIT_REPOSITORY "https://github.com/SFML/SFML.git"
  	GIT_TAG "${SFML_TAG}"
)
FetchContent_MakeAvailable(SFML)

# Tgui
set(TGUI_TAG "v1.10.0")
set(BUILD_SHARED_LIBS OFF)
set(TGUI_BACKEND SFML_GRAPHICS)

FetchContent_Declare(	
	TGUI
	GIT_REPOSITORY "https://github.com/texus/TGUI.git"
	GIT_TAG "${TGUI_TAG}"
)
FetchCOntent_MakeAvailable(TGUI)


#! compiling and linking
include_directories("${CMAKE_SOURCE_DIR}/include")
file(GLOB MY_SOURCE "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(main ${MY_SOURCE})

target_link_libraries(  
	main 				
	PRIVATE 
	sfml-graphics
	sfml-main
	sfml-system
	sfml-window
	TGUI::TGUI
)
# target_compile_options(main 
# 						PRIVATE 
# 						"/SUBSYSTEM:WINDOWS" 
# 						"/ENTRY:mainCRTStartup"
# 					)