cmake_minimum_required(VERSION 3.15)
project(online_voting_system LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE) # Add this line to enforce C++20

add_executable(online_voting_system
        src/main.cpp
        src/Candidate.cpp
        src/Election.cpp # <-- ADD THIS LINE
        src/Voter.cpp
)

# This command copies the 'data' folder from your project root to the build directory
file(COPY data DESTINATION "${CMAKE_BINARY_DIR}") # <-- ADD THIS ENTIRE LINE