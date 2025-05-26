cmake_minimum_required(VERSION 3.14)
project(${PROJECT_NAME} LANGUAGES CXX)

# Keep compile_commands.json around
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# More verbose output during build
set(CMAKE_VERBOSE_MAKEFILE ON)

# Grab all .cpp files under src/ (re-runs if you add new files)
file(GLOB
  SOURCES
  CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

if (NOT SOURCES)
  message(FATAL_ERROR "No .cpp files found in ${CMAKE_CURRENT_SOURCE_DIR}/src!")
endif()

# Create the executable, expanding the list into multiple args
add_executable(main ${SOURCES})

# Include our headers
target_include_directories(main PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Put the binary into bin/
set_target_properties(main PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

# Optional: generate .clang_complete
add_custom_target(generate_clang_complete
  COMMAND python "${CMAKE_SOURCE_DIR}/scripts/cc_args.py"
          "${CMAKE_BINARY_DIR}/compile_commands.json"
          > "${CMAKE_SOURCE_DIR}/.clang_complete"
  DEPENDS "${CMAKE_BINARY_DIR}/compile_commands.json"
)
