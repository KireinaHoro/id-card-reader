cmake_minimum_required(VERSION 3.0)

project(controller
	LANGUAGES C CXX)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     ON)
find_package(Boost REQUIRED
	COMPONENTS serialization) 
message("## Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")  # デバッグ用：解決したパスを表示
message("## Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")  # デバッグ用：解決したパスを表示

add_executable(enroll
	enroll.cc)
add_executable(query
	query.cc)

include_directories(
	"${PROJECT_SOURCE_DIR}"
	"${Boost_INCLUDE_DIRS}"
	"../include")

target_link_libraries(enroll
	nnxx
	nanomsg
	Boost::serialization)
target_link_libraries(query
	nnxx
	nanomsg
	Boost::serialization)
