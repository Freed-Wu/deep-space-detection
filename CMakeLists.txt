cmake_minimum_required(VERSION 3.10)
project(
  deep-space-detection
  VERSION 0.0.0.0
  DESCRIPTION deep-space-detection
  HOMEPAGE_URL https://github.com/Freed-Wu/deep-space-detection)
add_executable(main main.cpp arithmetic_coding.cpp)
configure_file(config.h.in config.h)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_ARCHIVE_THREADS 0)
set(CPACK_THREADS 0)
install(TARGETS main RUNTIME)
