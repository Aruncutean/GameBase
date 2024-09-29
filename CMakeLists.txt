# CMakeList.txt : CMake project for test, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("test")

include_directories(${CMAKE_SOURCE_DIR}/lib/glad/src/include)
include_directories(${CMAKE_SOURCE_DIR}/lib/SDL/include)
include_directories(${CMAKE_SOURCE_DIR}/lib/glm)
include_directories(${CMAKE_SOURCE_DIR}/lib/stb)

link_directories(${CMAKE_SOURCE_DIR}/lib/SDL/lib/x64)

add_executable(test "src/main.cpp" ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c  "src/graphics/utils/render.h" "src/graphics/utils/render.cpp" "src/graphics/utils/texture.cpp" "src/graphics/utils/texture.h" "src/graphics/utils/shader.cpp" "src/graphics/utils/shader.h" "src/graphics/utils/mesh.h" "src/graphics/utils/mesh.cpp"
        src/window/Window.cpp
        src/window/Window.h
        src/game/game.cpp
        src/game/game.h
        src/myGame/myGame.cpp
        src/myGame/myGame.h
        src/graphics/scene/scene2d.cpp
        src/graphics/scene/scene2d.h
        src/graphics/object/Object2d.cpp
        src/graphics/object/Object2d.h
        src/utils/Utils.cpp
        src/utils/Utils.h)

target_link_libraries(test SDL2main SDL2 opengl32)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET test PROPERTY CXX_STANDARD 20)
endif()

