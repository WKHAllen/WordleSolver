cmake_minimum_required(VERSION 3.10)

# set the project name
project(WordleSolver VERSION 1.0.0)

# add the executable
add_executable(WordleSolver ${CMAKE_CURRENT_LIST_DIR}/src/main.c)

# copy the dictionaries to the build
add_custom_command(TARGET WordleSolver PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/dict/ $<TARGET_FILE_DIR:WordleSolver>/dict)
