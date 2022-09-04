cmake_minimum_required(VERSION 3.5)

############################################################
# Create an executable
############################################################

ADD_SUBDIRECTORY(XMuduo)
ADD_SUBDIRECTORY(XPublic)

message("--------Cur Src Dir: " ${CMAKE_CURRENT_LIST_DIR})
file(GLOB_RECURSE XBASE_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
message("--------TEST RESULT: " ${XBASE_SRC_LIST})

find_path(Muduo_INCLUDE_DIR muduo "${CMAKE_CURRENT_LIST_DIR}/../include")
find_path(Muduo_LIBRARY_DIR libmuduo_net.a "${CMAKE_CURRENT_LIST_DIR}/../lib")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${Muduo_LIBRARY_DIR})
message(STATUS ${Muduo_INCLUDE_DIR})
message(STATUS ${Muduo_LIBRARY_DIR})

include_directories(${Muduo_INCLUDE_DIR})
find_library(muduo_base muduo_base)
find_library(muduo_net muduo_net)
message(STATUS ${muduo_base})
message(STATUS ${muduo_net})

# Add an executable with the above sources
add_executable(XMuduo
    ${XBASE_SRC_LIST}   
)

# link library
target_link_libraries(XMuduo
    PUBLIC 
        X::TEST
)

target_link_libraries(XMuduo 
    PUBLIC 
        ${muduo_base})

target_link_libraries(XMuduo 
    PUBLIC 
        ${muduo_net})

target_link_libraries(XMuduo 
    PUBLIC 
        rt)

target_include_directories(XMuduo
    PUBLIC 
        ${Muduo_INCLUDE_DIR}/
)


