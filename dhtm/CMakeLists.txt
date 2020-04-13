target_sources(dhtmlib
	PRIVATE
		zmqConnector.cpp
	PUBLIC
		zmqConnector.hpp
		ipcInterface.hpp
)
find_package(xtl REQUIRED)
find_package(xtensor REQUIRED)

find_package(Threads REQUIRED)

target_link_libraries(dhtmlib PUBLIC xtensor ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(dhtmlib PUBLIC ${CMAKE_CURRENT_LIST_DIR})
