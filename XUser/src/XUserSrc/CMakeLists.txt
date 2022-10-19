cmake_minimum_required(VERSION 3.5)

############################################################
# Create a library
############################################################


message("--------Cur Src Dir: " ${CMAKE_CURRENT_LIST_DIR})
file(GLOB_RECURSE XUserSrc_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
message("--------XUSERSRC RESULT: " ${XUserSrc_SRC_LIST})


add_library(userSrc SHARED 
    ${XUserSrc_SRC_LIST}
)
add_library(X::USER ALIAS userSrc)

# link library
target_link_libraries(userSrc
    PUBLIC 
        X::PUBLIB
)

# target_include_directories(userSrc
#     PUBLIC 
#         ${CMAKE_CURRENT_LIST_DIR}/XServer
# )

# target_include_directories(userSrc
#     PUBLIC 
#         ${CMAKE_CURRENT_LIST_DIR}/XUserServlet
# )