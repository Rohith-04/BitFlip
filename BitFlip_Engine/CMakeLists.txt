cmake_minimum_required(VERSION 3.20)
project(BitFlip_Engine VERSION 0.1.0 LANGUAGES CXX)

# ── Standard ──────────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ── Compiler Warnings ─────────────────────────────────────────────────────────
add_compile_options(-Wall -Wextra -Wpedantic)

# ── Engine Library ────────────────────────────────────────────────────────────
add_library(BitFlip_Engine STATIC
    src/Core/Wire.cpp
    src/Core/Gate.cpp
    src/Circuit/Circuit.cpp
    src/Simulation/Propagator.cpp
)

target_include_directories(BitFlip_Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# ── Test Executable ───────────────────────────────────────────────────────────
add_executable(BitFlip_Tests
    tests/main.cpp
    tests/test_gates.cpp
    tests/test_propagation.cpp
)

target_link_libraries(BitFlip_Tests PRIVATE BitFlip_Engine)
target_include_directories(BitFlip_Tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)