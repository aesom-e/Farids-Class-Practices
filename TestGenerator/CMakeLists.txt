cmake_minimum_required(VERSION 3.30)
project(TestGenerator C)

set(CMAKE_C_STANDARD 11)

add_executable(TestGenerator main.c
               error.c
               constants.c
               programHandler.c
               caseHandler.c)