set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)

set(
	console_app_srcs
	main.cpp
)

add_executable(console_app ${console_app_srcs})
target_link_libraries(console_app ${OpenCV_LIBS})

target_include_directories(console_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})