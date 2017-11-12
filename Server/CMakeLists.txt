project(Server)
include_directories(../Common)
include_directories(../Extern/boost)
link_directories(../Extern/boost/lib)
link_libraries(${boost_libraries})
if(WIN32)
link_libraries(${win_libraries})
endif()
set(src_list
    Server.cpp
    stdafx.cpp
	${common_src}
	${boost_src})

add_executable(Server ${src_list})

