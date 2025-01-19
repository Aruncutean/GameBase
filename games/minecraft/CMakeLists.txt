set(SUBMODUL2_SOURCES
        main.cpp
)

add_executable(submodul2_executabil ${SUBMODUL2_SOURCES})

target_include_directories(submodul2_executabil PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
