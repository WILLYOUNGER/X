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

add_executable(asio_chat_client client.cc)
target_link_libraries(asio_chat_client ${muduo_net})
target_link_libraries(asio_chat_client ${muduo_base})
target_link_libraries(asio_chat_client pthread)
target_include_directories(asio_chat_client
    PUBLIC 
        ${Muduo_INCLUDE_DIR}/
)

add_executable(asio_chat_loadtest loadtest.cc)
target_link_libraries(asio_chat_loadtest ${muduo_net})
target_link_libraries(asio_chat_loadtest ${muduo_base})
target_link_libraries(asio_chat_loadtest pthread)
target_include_directories(asio_chat_loadtest
    PUBLIC 
        ${Muduo_INCLUDE_DIR}/
)

add_executable(asio_chat_server server.cc)
target_link_libraries(asio_chat_server ${muduo_net})
target_link_libraries(asio_chat_server ${muduo_base})
target_link_libraries(asio_chat_server pthread)
target_include_directories(asio_chat_server
    PUBLIC 
        ${Muduo_INCLUDE_DIR}/
)

add_executable(asio_chat_server_threaded server_threaded.cc)
target_link_libraries(asio_chat_server_threaded ${muduo_net})
target_link_libraries(asio_chat_server_threaded ${muduo_base})
target_link_libraries(asio_chat_server_threaded pthread)
target_include_directories(asio_chat_server_threaded
    PUBLIC 
        ${Muduo_INCLUDE_DIR}/
)

add_executable(asio_chat_server_threaded_efficient server_threaded_efficient.cc)
target_link_libraries(asio_chat_server_threaded_efficient ${muduo_net})
target_link_libraries(asio_chat_server_threaded_efficient ${muduo_base})
target_link_libraries(asio_chat_server_threaded_efficient pthread)
target_include_directories(asio_chat_server_threaded_efficient
    PUBLIC 
        ${Muduo_INCLUDE_DIR}/
)

add_executable(asio_chat_server_threaded_highperformance server_threaded_highperformance.cc)
target_link_libraries(asio_chat_server_threaded_highperformance ${muduo_net})
target_link_libraries(asio_chat_server_threaded_highperformance ${muduo_base})
target_link_libraries(asio_chat_server_threaded_highperformance pthread)
target_include_directories(asio_chat_server_threaded_highperformance
    PUBLIC 
        ${Muduo_INCLUDE_DIR}/
)



