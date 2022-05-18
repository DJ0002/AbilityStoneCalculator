
cmake_minimum_required (VERSION 3.8)

add_executable(AbilityStoneCalculator "AbilityStoneCalculator.cpp" "Calculator.cpp" "Calculator.h")

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(AbilityStoneCalculator PRIVATE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(AbilityStoneCalculator PRIVATE imgui::imgui)

find_package(glad CONFIG REQUIRED)
target_link_libraries(AbilityStoneCalculator PRIVATE glad::glad)
