target_sources(utilslib
	PRIVATE
		logger.cpp
	PUBLIC
		logger.hpp
		itcTask.hpp
)

find_package(Threads REQUIRED)

set_target_properties(utilslib 
	PROPERTIES 
		LINKER_LANGUAGE CXX
)

target_link_libraries(utilslib 
	PUBLIC 
		${CMAKE_THREAD_LIBS_INIT}
)

target_include_directories(utilslib 
	PUBLIC 
		${CMAKE_CURRENT_LIST_DIR}
)
