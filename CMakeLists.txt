cmake_minimum_required(VERSION 3.18)
project( robotProject )

find_package( OpenCV REQUIRED )
find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)

add_subdirectory(cppClientLib build)

set(SOURCES
	#src/spdlog_test.cpp
    src/main.cpp
    src/custom_robot.cpp
    src/custom_detector.cpp 
    src/movement.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/cppClientLib/src/includes
    ${OpenCV_INCLUDE_DIRS}
    src/
    )

target_link_libraries(${PROJECT_NAME} PUBLIC
    serverClient
    ${OpenCV_LIBS}
    )

target_link_libraries(robotProject PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(robotProject PUBLIC spdlog::spdlog_header_only)
