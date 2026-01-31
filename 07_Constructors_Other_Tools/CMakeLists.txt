# CMakeList.txt : CMake project, include source and define
# project specific logic here.
#

# Add source to this project's executable.
# add_executable (Cpp_vs_Java "02_Expressions/1_0_0_Cpp_vs_Java.cpp")

# List all folders
set(FOLDERS
    "7.01_Rainbow"
    "7.02_Rectangle"
    "7.03_Counter_grocery"
    "7.04_Hotdog_parlour"
    "7.05_Iterator"
    "7.06_Pizza_order"
)

# Automatically get all .cpp and headers files 
foreach(folder ${FOLDERS})

    file(GLOB SOURCES CONFIGURE_DEPENDS "${folder}/*.cpp")
    file(GLOB HEADERS CONFIGURE_DEPENDS "${folder}/*.h")

    foreach(source ${SOURCES})
        get_filename_component(folder_name ${folder} NAME)
        get_filename_component(file_name ${source} NAME_WE)
        set(exec_name "${folder_name}_${file_name}")
        add_executable(${exec_name} ${source} ${HEADERS})

    endforeach()
endforeach()


# TODO: Add tests and install targets if needed.