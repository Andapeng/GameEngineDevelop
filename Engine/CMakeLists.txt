cmake_minimum_required (VERSION 3.8)
project(Engine VERSION 0.0.1)

add_executable(Engine Source/Main.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(VCPKG_ROOT "C:/Source/git/vcpkg" CACHE STRING "Vcpkg root directory")
set(CMAKE_TOOLCHAIN_FILE "C:/Source/git/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

find_package(SFML REQUIRED system window graphics network audio)

add_subdirectory(Source)

add_subdirectory(Source/Entities)

add_subdirectory(Source/Platform)

include_directories(ThirdParty)

include_directories(ThirdParty/Eigen)

include_directories(ThirdParty/include)

include_directories(${BOOST_ROOT})

target_sources(Engine 
				PRIVATE
				Source/Component/Transform.cpp
				Source/Config/GlobalConfiguration.cpp
				Source/Entities/Camera2D.cpp
				Source/Entities/GameObject.cpp
				Source/Entities/Player.cpp
				Source/Entities/RenderableObject.cpp
				Source/Entities/Sprite.cpp)

target_link_libraries(Engine PRIVATE sfml-system sfml-network sfml-graphics sfml-window Main Module_Platform)
