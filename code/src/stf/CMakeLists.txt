add_library(stf INTERFACE)

target_include_directories(stf INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/interface)

# TODO (stouff) add the public headers inside the include directory to our install