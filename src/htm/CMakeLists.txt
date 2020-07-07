target_sources(htmlib
	PRIVATE
		spatialPooler.cpp
	PUBLIC
		spatialPooler.hpp
)
find_package(xtl REQUIRED)
find_package(xtensor REQUIRED)

find_package(Threads REQUIRED)

target_link_libraries(htmlib 
	PUBLIC 
		xtensor 
		${CMAKE_THREAD_LIBS_INIT}
)

target_include_directories(htmlib 
	PUBLIC 
		${CMAKE_CURRENT_LIST_DIR}
)
