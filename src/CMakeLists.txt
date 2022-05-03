cmake_minimum_required(VERSION 3.16)
project(optimizer-lib VERSION 0.1)
set (CMAKE_CXX_STANDARD 11)

include_directories(./include)

set(H_FILES
    include/ArmijoLineSearch.hpp
    include/CentralDifference.hpp
    include/ConstantStepSize.hpp
    include/GradientDescent.hpp
    include/StepSize.hpp
    include/StrongWolfeSearch.hpp
)

set(CPP_FILES
    include/ArmijoLineSearch.cpp
    include/CentralDifference.cpp
    include/ConstantStepSize.cpp
    include/GradientDescent.cpp
    include/StepSize.cpp
    include/StrongWolfeSearch.cpp
)

add_library(optimizer-lib ${H_FILES} ${CPP_FILES})

install(TARGETS optimizer-lib DESTINATION /usr/local/lib)
install(FILES ${H_FILES} DESTINATION /usr/local/include)