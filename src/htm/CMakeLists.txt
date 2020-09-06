target_sources(htmlib
	PRIVATE
		spatialPooler.cpp
	PUBLIC
		htmConstants.hpp
		spatialPooler.hpp
)

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
