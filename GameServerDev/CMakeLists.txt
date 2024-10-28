cmake_minimum_required (VERSION 3.8)
project(GameServerDev VERSION 0.0.1)
add_executable(GameServerDev Main.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(VCPKG_ROOT "C:/Source/git/vcpkg" CACHE STRING "Vcpkg root directory")
set(CMAKE_TOOLCHAIN_FILE "C:/Source/git/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

include_directories("../Engine/ThirdParty")
include_directories("../Engine/ThirdParty/Eigen")
include_directories("../Engine/ThirdParty/include")
include_directories("C:/Source/git/vcpkg/installed/x64-windows/include/")
include_directories("C:/Source/boost/boost_1_72_0/boost_1_72_0")


target_link_directories(GameServerDev
						PRIVATE
						"../Engine/ThirdParty/lib")

target_link_directories(GameServerDev
						PRIVATE
						"C:/Source/boost/boost_1_72_0/boost_1_72_0/stage/lib")

target_link_directories(GameServerDev
						PRIVATE
						"C:/Source/git/vcpkg/installed/x64-windows/lib")

target_link_libraries(GameServerDev
					PRIVATE
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
)

target_sources(GameServerDev 
				PRIVATE
				GameServer.cpp
				FileHelper.cpp
)