cmake_minimum_required(VERSION 3.10)

project("MyVulkanEngine")

#set the cpp standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror -Wno-implicit-fallthrough")


#check for external libraries
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
include(FetchContent)

#check for glm
if (NOT EXISTS "${EXTERNAL_INSTALL_LOCATION}/glm")
	message(STATUS "glm not found, downloading...")
	execute_process(
		COMMAND git clone https://github.com/g-truc/glm.git
		WORKING_DIRECTORY ${EXTERNAL_INSTALL_LOCATION}
	)
endif()
	
#sources files
set(SOURCE_FILE
	"src/main.cpp"
	"src/application/graphic_engine/debug/debug_messenger.cpp"
	"src/application/graphic_engine/logical_device/device.cpp"
	"src/application/graphic_engine/instance/instance.cpp"
	"src/application/graphic_engine/physical_device/physical_device.cpp"
	"src/application/graphic_engine/queue/queue.cpp"
	"src/application/graphic_engine/surface/surface.cpp"
	"src/application/graphic_engine/graphic_engine.cpp"
	"src/application/application.cpp"
	"src/iostream/logger.cpp"
	"src/error/error.cpp"
	"src/window/window_manager.cpp"
	"src/window/window.cpp"
)

add_executable(MyVulkanEngine ${SOURCE_FILE})

target_link_libraries(MyVulkanEngine glfw vulkan dl pthread X11 Xxf86vm Xrandr Xi)

target_include_directories(MyVulkanEngine PUBLIC
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/src/application"
	"${PROJECT_SOURCE_DIR}/src/application/graphic_engine"
	"${PROJECT_SOURCE_DIR}/src/application/graphic_engine/debug"
	"${PROJECT_SOURCE_DIR}/src/application/graphic_engine/logical_device"
	"${PROJECT_SOURCE_DIR}/src/application/graphic_engine/instance"
	"${PROJECT_SOURCE_DIR}/src/application/graphic_engine/physical_device"
	"${PROJECT_SOURCE_DIR}/src/application/graphic_engine/queue"
	"${PROJECT_SOURCE_DIR}/src/application/graphic_engine/surface"
	"${PROJECT_SOURCE_DIR}/src/error"
	"${PROJECT_SOURCE_DIR}/src/iostream"
	"${PROJECT_SOURCE_DIR}/src/window"
	"${EXTERNAL_INSTALL_LOCATION}/glm"
)
