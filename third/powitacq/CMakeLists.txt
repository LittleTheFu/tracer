# Set the project name
project (powitacq)

include_directories(include)
add_library(${PROJECT_NAME}  STATIC code/powitacq_rgb.cpp)