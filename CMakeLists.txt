cmake_minimum_required(VERSION 3.21)
project(FC_projects)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "-Wall -O2")

find_package(ROOT 6.24 CONFIG REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIR})






add_executable(Ex225 main/Ex225.cpp)
add_executable(Ex422 main/Ex422.cpp)
add_executable(Ex454 main/Ex454.cpp)
add_executable(Ex464 main/Ex464.cpp)

add_executable(ShootingMethod main/ShootingMethod.cpp)
add_executable(VanderPol main/VanderPol.cpp)
add_executable(Duffing main/Duffing.cpp)
add_executable(DuffingLyap main/DuffingLyaponov.cpp)

file(GLOB SRC_LIB_FILES src/*.cpp)
add_library(FC STATIC ${SRC_LIB_FILES})

target_link_libraries(Ex225 PUBLIC FC)
target_include_directories(Ex225 PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(Ex225 PUBLIC ROOT::Core  ROOT::MathCore ROOT::Gui)


target_link_libraries(Ex422 PUBLIC FC)
target_link_libraries(Ex422 PUBLIC Eigen3::Eigen)
target_include_directories(Ex422 PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(Ex422 PUBLIC ROOT::Core  ROOT::MathCore ROOT::Gui)


target_link_libraries(Ex454 PUBLIC FC)
target_include_directories(Ex454 PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(Ex454 PUBLIC ROOT::Core  ROOT::MathCore ROOT::Gui)

target_link_libraries(Ex464 PUBLIC FC)
target_include_directories(Ex464 PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(Ex464 PUBLIC ROOT::Core  ROOT::MathCore ROOT::Gui)


target_link_libraries(ShootingMethod PUBLIC FC)
target_include_directories(ShootingMethod PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(ShootingMethod PUBLIC ROOT::Core  ROOT::MathCore ROOT::Gui)


target_link_libraries(Duffing PUBLIC FC)
target_include_directories(Duffing PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(Duffing PUBLIC ROOT::Core  ROOT::MathCore ROOT::Gui)


target_link_libraries(DuffingLyap PUBLIC FC)
target_include_directories(DuffingLyap PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(DuffingLyap PUBLIC ROOT::Core  ROOT::MathCore ROOT::Gui)


target_link_libraries(VanderPol PUBLIC FC)
target_include_directories(VanderPol PRIVATE ${ROOT_INCLUDE_DIRS})
target_link_libraries(VanderPol PUBLIC ROOT::Core  ROOT::MathCore ROOT::Gui)

