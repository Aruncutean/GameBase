set(SUBMODUL1_SOURCES
      myGame.cpp myGame.h main.cpp
)

add_executable(submodul1_executabil ${SUBMODUL1_SOURCES})

target_include_directories(submodul1_executabil)
