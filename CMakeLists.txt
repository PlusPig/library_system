cmake_minimum_required(VERSION 3.23)
project(library_system)

set(CMAKE_CXX_STANDARD 17)

add_executable(library_system main.cpp
        library.cpp
        library.h)

add_executable(login tutorial/login/login.cpp tutorial/login/login_plus.cpp tutorial/global.h)
