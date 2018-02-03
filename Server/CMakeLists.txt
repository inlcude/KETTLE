project(Server)
include_directories(../Common)
include_directories(../Extern/boost)
aux_source_directory(../Common COMMON_SRC)
aux_source_directory(../Extern/boost/boost BOOST_SRC)
aux_source_directory(../Extern/gperftools/src GPERFTOOLS_SRC)
link_directories(../Extern/boost/lib)
link_directories(../Extern/gperftools/lib)
link_libraries(${BOOST_LIBRARIES})
#link_libraries(${GPERFTOOLS_LIBRARIES})
if(WIN32)
link_libraries(${WIN_LIBRARIES})
endif()
set(SRC_LIST
    Server.cpp
	${COMMON_SRC}
	${BOOST_SRC}
	${GPERFTOOLS_SRC})

add_executable(Server ${SRC_LIST})

