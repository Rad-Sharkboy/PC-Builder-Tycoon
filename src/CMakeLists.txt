add_executable(RigBuilderTycoon main.cpp resources.rc Component.cpp CPU.cpp GPU.cpp RAM.cpp PC.cpp)
target_link_libraries(RigBuilderTycoon raylib)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")