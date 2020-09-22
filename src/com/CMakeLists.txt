target_sources(comlib
	PRIVATE
		configurationService.cpp
		messageEncoder.cpp
		zmqConnector.cpp

	PUBLIC
		comInterface.hpp
		configurationService.hpp
		messageEncoder.hpp
		zmqSubscriber.hpp
		zmqConnector.hpp
)

find_package(Threads REQUIRED)
find_library(zmq REQUIRED)

target_link_libraries(comlib
	PUBLIC
		${CMAKE_THREAD_LIBS_INIT}
)

target_include_directories(comlib
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)
