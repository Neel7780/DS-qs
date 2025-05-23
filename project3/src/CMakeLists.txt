cmake_minimum_required(VERSION 3.10)
project(QRCode)

# Compiler settings
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# OpenCV paths
set(OpenCV_INCLUDE_DIRS "C:/Users/neelk/Downloads/opencv/build/include")
set(OpenCV_LIB_DIR "C:/Users/neelk/Downloads/opencv/build/x64/vc16/lib")
set(OpenCV_BIN_DIR "C:/Users/neelk/Downloads/opencv/build/x64/vc16/bin")

# Source files
set(SOURCES
    Source/main.cpp
    Source/ImageBinarization.cpp
    Source/Filesystem.cpp
    Source/Generator.cpp
    Source/CodeFinder.cpp
)

# Create executable
add_executable(main ${SOURCES})

# Include directories
target_include_directories(main PRIVATE ${OpenCV_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/Header)

# Link OpenCV explicitly
link_directories(${OpenCV_LIB_DIR})
target_link_libraries(main PRIVATE "${OpenCV_LIB_DIR}/opencv_world490.lib")

# Post-build: copy DLL to output
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${OpenCV_BIN_DIR}/opencv_world490.dll"
        $<TARGET_FILE_DIR:main>
)

# Print configuration for debugging
message(STATUS "OpenCV include: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV lib: ${OpenCV_LIB_DIR}")
message(STATUS "OpenCV bin: ${OpenCV_BIN_DIR}")
message(STATUS "Output: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
