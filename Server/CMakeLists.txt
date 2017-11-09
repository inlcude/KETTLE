project(Server)
include_directories(../Common)
include_directories(../Extern/boost)
link_directories(../Extern/boost/lib)
if(WIN32)
link_libraries(${win_libraries})
endif()
link_libraries(${boost_libraries})
set(src_list
    Server.cpp
    stdafx.cpp
	${common_src}
	${boost_src})

add_executable(Server ${src_list})