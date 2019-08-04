project(Test)
include_directories(../Common)
aux_source_directory(../Common COMMON_SRC)
link_libraries(${GPERFTOOS_LIBRARIES})
add_definitions("-Wall -g")
link_libraries(pthread)
set(SRC_LIST
    testlog.cpp
	${COMMON_SRC}
	${GPERFTOOLS_SRC})
add_executable(testlog ${SRC_LIST})

set(SRC_LIST
    testAsynLog.cpp
	${COMMON_SRC}
	${GPERFTOOLS_SRC})
add_executable(testAsynLog ${SRC_LIST})

set(SRC_LIST
    testTcpServer.cpp
	${COMMON_SRC}
	${GPERFTOOLS_SRC})
add_executable(testTcpServer ${SRC_LIST})