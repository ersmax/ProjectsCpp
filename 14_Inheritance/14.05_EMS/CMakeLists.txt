# Generic CMakeLists for a multi-file example folder
# All .cpp files in this folder belong to one executable.

# Collect all .cpp files in this directory
file(GLOB EXAMPLE_SOURCES CONFIGURE_DEPENDS "*.cpp")

# Use the directory name as the target name
get_filename_component(TARGET_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)

add_executable(${TARGET_NAME}
    ${EXAMPLE_SOURCES}
    ../14.03_Doctor/14_03_Doctor.cpp
    ../14.01_Administrator/14_01_Employee.cpp
    ../14.01_Administrator/14_01_Salaried_Employee.cpp
   ../14.04_Student/14_04_Input_Validation.cpp
)
