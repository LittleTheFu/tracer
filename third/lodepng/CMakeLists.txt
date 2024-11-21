# Set the project name
project (lodepng)

include_directories(include)
add_library(${PROJECT_NAME}  STATIC code/lodepng.cpp)