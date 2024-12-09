cmake_minimum_required (VERSION 3.8)
project(Engine VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(VCPKG_ROOT "C:/Source/git/vcpkg" CACHE STRING "Vcpkg root directory")
set(CMAKE_TOOLCHAIN_FILE "C:/Source/git/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(SFML_DIR "C:/Source/git/vcpkg/installed/x64-windows/share/sfml")
set(IMGUI_DIR "D:/Project/GameEngineDevelop/Engine/ThirdParty/imgui")
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
Source/RHI/d3dx12.h 
"Source/Misc/GameTimer.cpp" 
"Source/Gui/Button.cpp" 
"Source/Entities/Text.cpp" 
"Source/Renderer/ImguiRenderer.cpp" 
"Source/Gui/ButtonDescript.cpp" 
"Source/Game/Breakout/GameLevel.cpp"
"Source/Game/Breakout/Brick.cpp"
"Source/Game/Breakout/Breakout.cpp" "Source/Game/Breakout/Paddle.cpp" "Source/Game/Breakout/Ball.cpp" "Source/Renderer/Particle.cpp")

add_executable(Engine Source/Main.cpp)
add_library(LibEngine ${EngineSources})
add_subdirectory(ThirdParty/imgui)
add_subdirectory(ThirdParty/imgui-sfml)

target_compile_definitions(Engine PRIVATE -DOPENGL_RENDERING)
target_compile_definitions(LibEngine PRIVATE -DOPENGL_RENDERING)

include_directories(LibEngine
PRIVATE 
"ThirdParty"
"ThirdParty/Eigen"
"ThirdParty/Vulkan/include"
"ThirdParty/include"
"C:/Source/git/vcpkg/installed/x64-windows/include/"
"C:/Source/boost/boost_1_72_0/boost_1_72_0")

target_link_directories(LibEngine
						PRIVATE
						"ThirdParty/lib"
						"ThirdParty/Vulkan/lib"
						"C:/Source/boost/boost_1_72_0/boost_1_72_0/stage/lib"
						"C:/Source/git/vcpkg/installed/x64-windows/debug/lib")

target_link_libraries(LibEngine
					PUBLIC
					gtestd.lib
					glad.lib
					sfml-window-d.lib
					sfml-graphics-d.lib
					sfml-audio-d.lib
					sfml-network-d.lib
					sfml-system-d.lib
					freetyped.lib
					box2d.lib
					fmtd.lib
					dxgi.lib
					vulkan-1.lib
					d3d12.lib
					dxgi.lib
					d3dcompiler.lib
					libimgui
					ImGui-SFML

)
install(TARGETS LibEngine DESTINATION lib)

include_directories(Engine
PRIVATE 
"ThirdParty"
"ThirdParty/Eigen"
"ThirdParty/Vulkan/include"
"ThirdParty/include"
"C:/Source/git/vcpkg/installed/x64-windows/include/"
"C:/Source/boost/boost_1_72_0/boost_1_72_0")


target_link_directories(Engine
						PRIVATE
						"ThirdParty/lib"
						"ThirdParty/Vulkan/lib"
						"C:/Source/boost/boost_1_72_0/boost_1_72_0/stage/lib"
						"C:/Source/git/vcpkg/installed/x64-windows/debug/lib")

target_link_libraries(Engine
					PUBLIC
					gtestd.lib
					glad.lib
					sfml-window-d.lib
					sfml-graphics-d.lib
					sfml-audio-d.lib
					sfml-network-d.lib
					sfml-system-d.lib
					freetyped.lib
					box2d.lib
					fmtd.lib
					dxgi.lib
					vulkan-1.lib
					d3d12.lib
					dxgi.lib
					d3dcompiler.lib
					libimgui
					ImGui-SFML
)
target_sources(Engine 
				PRIVATE
				${EngineSources})


