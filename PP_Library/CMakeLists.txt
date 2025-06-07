cmake_minimum_required(VERSION 3.16)
project(PP_Library)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags for better error reporting
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Create shared library for common classes
add_library(LibraryCore
        Book.cpp
        Date.cpp
        Loan.cpp
        FileManager.cpp
)

# Librarian executable
add_executable(librarian
        librarian.cpp
)

# Reader executable
add_executable(reader
        reader.cpp
)

# Link the shared library to both executables
target_link_libraries(librarian LibraryCore)
target_link_libraries(reader LibraryCore)

# Include current directory for headers
target_include_directories(LibraryCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(librarian PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(reader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})