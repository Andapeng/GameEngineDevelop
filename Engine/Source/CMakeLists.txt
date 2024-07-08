cmake_minimum_required (VERSION 3.8)
add_library(Main)

# 查找Boost库
find_package(Boost COMPONENTS system filesystem log REQUIRED)
 
# 如果Boost被找到，打印版本信息
if(Boost_FOUND)
    message(STATUS "Found Boost ${Boost_VERSION}")
else()
    message(FATAL_ERROR "Boost not found")
endif()

include_directories(${BOOST_ROOT})

target_sources(Main
	PRIVATE
	Application.cpp
	GameInstance.cpp
	Log.cpp
	Main.cpp
)

target_link_libraries(Main PUBLIC sfml-system sfml-network sfml-graphics sfml-window Boost::system Boost::filesystem Boost::log)
