cmake_minimum_required (VERSION 3.8)
project(Engine VERSION 0.0.1)

set(LIBRARY_OUTPUT_PATH "lib")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(VCPKG_ROOT "C:/Source/git/vcpkg" CACHE STRING "Vcpkg root directory")
set(CMAKE_TOOLCHAIN_FILE "C:/Source/git/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

add_compile_definitions(-DNOMINMAX)

set(EngineSources Source/Component/Transform.cpp
				Source/Application.cpp
				Source/Log.cpp
				Source/GameInstance.cpp
				Source/Config/GlobalConfiguration.cpp
				Source/Entities/Camera2D.cpp
				Source/Entities/GameObject.cpp
				Source/Entities/Player.cpp
				Source/Entities/RenderableObject.cpp
				Source/Entities/Sprite.cpp
Source/Managers/AudioManager.cpp
Source/Managers/FontManager.cpp
Source/Managers/GraphicsManager.cpp
Source/Managers/IManager.cpp
Source/Managers/Managers.cpp
Source/Managers/InputManager.cpp
Source/Managers/NetworkManager.cpp
Source/Managers/PhysicsManager.cpp
Source/Managers/ResourceManager.cpp
Source/Managers/SceneManager.cpp
Source/Managers/StateManager.cpp
Source/Managers/StatisticsManager.cpp
Source/Math/Math.cpp
Source/Network/NetworkClient.cpp
Source/Network/NetMessage.cpp
Source/Platform/Window.cpp
Source/Platform/WindowImp.cpp
Source/RHI/Character.cpp
Source/RHI/Shader.cpp
Source/RHI/Texture.cpp
Source/Renderer/Renderer.cpp
Source/Renderer/SpriteRenderer.cpp
Source/Renderer/TextRenderer.cpp
Source/Scene/Scene.cpp
Source/Physics/HitInfo.cpp
Source/Physics/Physics2D.cpp
Source/Game/Snake/Food.cpp
Source/Game/Snake/ScoreBoard.cpp
Source/Game/Snake/Snake.cpp
Source/Game/Snake/SnakeGame.cpp
Source/Game/Snake/Wall.cpp
Source/Gui/Label.cpp
Source/RHI/D3D12GraphicsDevice.cpp 
Source/RHI/VulkanGrahphicsDevice.cpp
Source/RHI/OpenGLGraphicsDevice.cpp 
Source/Managers/WindowManager.cpp 
Source/RHI/D3dUtil.cpp
Source/RHI/d3dx12.h)

add_executable(Engine Source/Main.cpp)
add_library(LibEngine ${EngineSources})

target_include_directories(LibEngine
PUBLIC 
ThirdParty)
target_include_directories(LibEngine
PUBLIC 
ThirdParty/Eigen)
target_include_directories(LibEngine
PUBLIC 
ThirdParty/Vulkan/include)
target_include_directories(LibEngine
PUBLIC 
ThirdParty/include)
target_include_directories(LibEngine
PUBLIC 
"C:/Source/git/vcpkg/installed/x64-windows/include/")
target_include_directories(LibEngine
PUBLIC 
"C:/Source/boost/boost_1_72_0/boost_1_72_0")

target_link_directories(LibEngine
						PUBLIC
						"ThirdParty/lib")

target_link_directories(Engine
						PRIVATE
						"ThirdParty/Vulkan/lib")

target_link_directories(LibEngine
						PUBLIC
						"C:/Source/boost/boost_1_72_0/boost_1_72_0/stage/lib")

target_link_directories(LibEngine
						PUBLIC
						"C:/Source/git/vcpkg/installed/x64-windows/lib")

target_link_libraries(LibEngine
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
					dxgi.lib
					vulkan-1.lib
					d3d12.lib
					dxgi.lib
					d3dcompiler.lib

)
install(TARGETS LibEngine DESTINATION lib)

include_directories(Engine
PRIVATE 
ThirdParty)
target_include_directories(Engine
PRIVATE 
 ThirdParty/Eigen)
target_include_directories(Engine
PUBLIC 
ThirdParty/Vulkan/include)
target_include_directories(Engine
PRIVATE 
ThirdParty/include)
target_include_directories(Engine
PRIVATE 
"C:/Source/git/vcpkg/installed/x64-windows/include/")
target_include_directories(Engine
PRIVATE 
"C:/Source/boost/boost_1_72_0/boost_1_72_0")


target_link_directories(Engine
						PRIVATE
						"ThirdParty/lib")

target_link_directories(Engine
						PRIVATE
						"ThirdParty/Vulkan/lib")

target_link_directories(Engine
						PRIVATE
						"C:/Source/boost/boost_1_72_0/boost_1_72_0/stage/lib")

target_link_directories(Engine
						PRIVATE
						"C:/Source/git/vcpkg/installed/x64-windows/lib")

target_link_libraries(Engine
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
					dxgi.lib
					vulkan-1.lib
					d3d12.lib
					dxgi.lib
					d3dcompiler.lib
)
target_sources(Engine 
				PRIVATE
				${EngineSources})


