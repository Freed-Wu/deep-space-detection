cmake_minimum_required(VERSION 3.10)
if(DEFINED ENV{GITHUB_REF_NAME})
  set(VERSION $ENV{GITHUB_REF_NAME})
else()
  set(VERSION 0.0.0.0)
endif()
project(
  deep-space-detection
  VERSION ${VERSION}
  DESCRIPTION deep-space-detection
  HOMEPAGE_URL https://github.com/Freed-Wu/deep-space-detection)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_executable(main src/main.cpp src/arithmetic_coding.cpp)
configure_file(config.h.in src/config.h)
install(TARGETS main RUNTIME)

set(CPACK_PACKAGE_CONTACT
    https://github.com/Freed-Wu/deep-space-detection/issues)
include(CPack)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_ARCHIVE_THREADS 0)
set(CPACK_THREADS 0)
