target_sources(comlib
	PRIVATE
		zmqConnector.cpp
		messageEncoder.cpp
	PUBLIC
		zmqSubscriber.hpp
		zmqConnector.hpp
		messageEncoder.hpp
		comInterface.hpp
)

find_package(Threads REQUIRED)

target_link_libraries(comlib 
	PUBLIC 
		${CMAKE_THREAD_LIBS_INIT}
)

target_include_directories(comlib 
	PUBLIC 
		${CMAKE_CURRENT_LIST_DIR}
)
