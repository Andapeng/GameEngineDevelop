cmake_minimum_required (VERSION 3.8)

project(GameClient VERSION 0.0.1)

add_executable(GameClient Main.cpp "Game/Snake/Source/SnakeGameInstance.h" "Game/Snake/Source/SnakeGameInstance.cpp")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(VCPKG_ROOT "C:/Source/git/vcpkg" CACHE STRING "Vcpkg root directory")
set(CMAKE_TOOLCHAIN_FILE "C:/Source/git/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

target_include_directories(GameClient
PRIVATE 
../Engine/ThirdParty)
target_include_directories(GameClient
PRIVATE 
../Engine/ThirdParty/include)
target_include_directories(GameClient
PRIVATE 
../Engine/ThirdParty/Eigen)
target_include_directories(GameClient 
PRIVATE 
../Engine/Source
)
target_link_directories(GameClient
						PUBLIC
						"../Engine/ThirdParty/lib")
target_include_directories(GameClient
PUBLIC 
"C:/Source/git/vcpkg/installed/x64-windows/include/")
target_include_directories(GameClient
PUBLIC 
"C:/Source/boost/boost_1_72_0/boost_1_72_0")

target_link_directories(GameClient
						PUBLIC
						"C:/Source/boost/boost_1_72_0/boost_1_72_0/stage/lib")

target_link_directories(GameClient
						PUBLIC
						"C:/Source/git/vcpkg/installed/x64-windows/lib")

target_link_libraries(GameClient
					PUBLIC
					gtest.lib
					glad.lib
					sfml-window.lib
					sfml-graphics.lib
					sfml-audio.lib
					sfml-network.lib
					sfml-system.lib
					freetype.lib
					box2d.lib
					fmtd.lib
					LibEngine.lib
)

target_sources(GameClient
PUBLIC
Game/Snake/Source/SnakeGameInstance.cpp)
