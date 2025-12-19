# CMakeList.txt : CMake project, include source and define
# project specific logic here.
#

# Add source to this project's executable.
# add_executable (Cpp_vs_Java "02_Expressions/1_0_0_Cpp_vs_Java.cpp")

# List all folders
set(FOLDERS
    "6.01_Employee_Rating"
    "6.02_Circle_Class"
    "6.03_Pair_Template_Implementation"
    "6.04_Gas_Pump"
    "6.05_Fraction_Class"
    "6.06_Bicycle_Speedometer"
    "6.07_Pizzeria"
    "6.08_Money_Portfolio"
    "6.09_Money_Portfolio_Improved"
    "6.10_Weight_Conversion"
    "6.11_Highest_Score"
    "6.12_Mystery_Box"
    "6.13_Player_Stats_Class"
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