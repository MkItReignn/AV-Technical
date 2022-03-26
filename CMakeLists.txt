cmake_minimum_required(VERSION 3.14)
project(NMP)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
enable_testing()
add_executable(
    main
    main.cpp
)
add_dependencies(
    main
    gtest
)
target_link_libraries(
    main
    gtest_main
)

find_package(Threads REQUIRED)

target_link_libraries(main
    ${CMAKE_THREAD_LIBS_INIT}
)

add_compile_options(-pthread)