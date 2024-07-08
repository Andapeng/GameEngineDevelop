add_library(Module_Platform)

set(VCPKG_ROOT "C:/Source/git/vcpkg" CACHE STRING "Vcpkg root directory")
set(CMAKE_TOOLCHAIN_FILE "C:/Source/git/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

find_package(SFML REQUIRED system window graphics network audio)

target_sources(Module_Platform
	PRIVATE
	Window.cpp
	WindowImp.cpp)

target_link_libraries(Module_Platform PUBLIC sfml-graphics sfml-window)