cmake_minimum_required(VERSION 3.10)

project("MyVulkanEngine")

#set the cpp standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror")


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
	"src/application/application.cpp"
	"src/iostream/logger.cpp"
)

add_executable(MyVulkanEngine ${SOURCE_FILE})

target_link_libraries(MyVulkanEngine glfw vulkan dl pthread X11 Xxf86vm Xrandr Xi)

target_include_directories(MyVulkanEngine PUBLIC
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/src/application"
	"${PROJECT_SOURCE_DIR}/src/iostream"
	"${EXTERNAL_INSTALL_LOCATION}/glm"
)
