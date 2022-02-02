cmake_minimum_required(VERSION 3.10)

# set the project name
project(WordleSolver VERSION 1.0.0)

# add the executable
file(GLOB CSources ${CMAKE_CURRENT_LIST_DIR}/src/*.c)
add_executable(WordleSolver ${CSources})

# copy the assets to the build
add_custom_command(TARGET WordleSolver PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:WordleSolver>/assets)
