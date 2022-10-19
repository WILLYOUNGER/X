cmake_minimum_required(VERSION 3.5)

############################################################
# Create a library
############################################################

message("--------Cur Src Dir: " ${CMAKE_CURRENT_LIST_DIR})

if(LINUX)
file(GLOB_RECURSE XPUBLIC_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/XFrames/*.cpp)
file(GLOB_RECURSE XPUBLIC_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/XTools/XHTTP/*.cpp)
file(GLOB_RECURSE XPUBLIC_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/XTools/XServer/*.cpp)
file(GLOB_RECURSE XPUBLIC_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/XTools/XNet/*.cpp)
file(GLOB_RECURSE XPUBLIC_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/XTools/XUtils/XUtils.cpp)
endif()

file(GLOB_RECURSE XPUBLIC_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/XGame/*.cpp)
file(GLOB_RECURSE XPUBLIC_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/XStruct/*.cpp)
file(GLOB_RECURSE XPUBLIC_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/XTools/XLOG/*.cpp)
file(GLOB_RECURSE XPUBLIC_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/XTools/XPthread/*.cpp)
file(GLOB_RECURSE XPUBLIC_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/XTools/XSql/*.cpp)
file(GLOB_RECURSE XPUBLIC_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/XTools/XUtils/*.cpp)
file(GLOB_RECURSE XPUBLIC_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/XTools/XUtils/XFile.cpp)
file(GLOB_RECURSE XPUBLIC_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/XTools/XUtils/XMath.cpp)
file(GLOB_RECURSE XPUBLIC_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/XTools/XUtils/XWheelTimer.cpp)
message("--------PUB RESULT: " ${XPUBLIC_SRC_LIST})


add_library(publib SHARED 
    ${XPUBLIC_SRC_LIST}
)
add_library(X::PUBLIB ALIAS publib)

if(LINUX)
target_link_libraries(publib PUBLIC mysqlcppconn)
endif()

target_link_libraries(publib PUBLIC pthread)
target_link_libraries(publib
    PUBLIC 
        X::THIRD
)

if(LINUX)

target_include_directories(publib
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/XTools/XHTTP
)

target_include_directories(publib
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/XTools/XNet
)

target_include_directories(publib
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/XTools/XServer
)

endif()

target_include_directories(publib
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/XFrames
)

target_include_directories(publib
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/XFrames/XServlet
)

target_include_directories(publib
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/XGame
)

target_include_directories(publib
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/XGame/XDesignBase
)

target_include_directories(publib
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/XGame/XStatistics
)

target_include_directories(publib
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/XStruct
)

target_include_directories(publib
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/XTools
)

target_include_directories(publib
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/XTools/XSql
)

target_include_directories(publib
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/XTools/XLog
)

target_include_directories(publib
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/XTools/XPthread
)

target_include_directories(publib
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}/XTools/XUtils
)