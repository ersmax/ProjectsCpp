# Generic CMakeLists for a multi-file example folder
# All .cpp files in this folder belong to one executable.

# Collect all .cpp files in this directory
file(GLOB EXAMPLE_SOURCES CONFIGURE_DEPENDS "*.cpp")

# Use the directory name as the target name
get_filename_component(TARGET_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)

add_executable(${TARGET_NAME}
    ${EXAMPLE_SOURCES}
)