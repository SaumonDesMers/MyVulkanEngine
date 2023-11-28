cmake_minimum_required(VERSION 3.10)

project("MyVulkanEngine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror")

set(SOURCE_FILE
	"src/main.cpp"
)

add_executable(MyVulkanEngine ${SOURCE_FILE})

target_link_libraries(MyVulkanEngine glfw vulkan dl pthread X11 Xxf86vm Xrandr Xi)
