project(Test)
include_directories(../Common)
aux_source_directory(../Common COMMON_SRC)
link_libraries(${GPERFTOOS_LIBRARIES})
add_definitions("-Wall -g")
set(SRC_LIST
    testlog.cpp
	${COMMON_SRC}
	${GPERFTOOLS_SRC})
link_libraries(pthread)
add_executable(testlog ${SRC_LIST})