# CMakeList.txt : CMake project, include source and define
# project specific logic here.
#

# Add source to this project's executable.
# add_executable (Cpp_vs_Java "02_Expressions/1_0_0_Cpp_vs_Java.cpp")

# List all folders
set(FOLDERS
    "4.01_Hour_Conversion"
    "4.02_Area_Circumference"
    "4.03_Redeem_Voucher"
    "4.04_Feet_Inches_to_Meters"
    "4.05_Meters_to_Feet_Inches"
    "4.06_Length_Conversion"
    "4.07_Pounds_Ounces_to_Grams"
    "4.08_Grams_to_Pounds_Ounces"
    "4.09_Weight_Conversion"
    "4.10_Length_Weight_Conversion"
    "4.11_Monty_Hall_Problem"
    "4.12_Three_Way_Duel"
    "4.13_Treadmill_Pace"
    "4.14_Time_Difference"
    "4.15_Convert_Lowest_Terms"
    "4.16_Highest_Score"
    "4.17_Get_Score_Average_Score"
    "4.18_Sorting_Trivial_Quick_Merge"
)

# Automatically get all .cpp and headers files 
foreach(folder ${FOLDERS})
    # Gather .cpp and .h files
    file(GLOB SOURCES CONFIGURE_DEPENDS "${folder}/*.cpp")
    file(GLOB HEADERS CONFIGURE_DEPENDS "${folder}/*.h")

    foreach(source ${SOURCES})
        # Executable name = filename without extension
        get_filename_component(exec_name ${source} NAME_WE)

        # Create target
        add_executable(${exec_name} ${source} ${HEADERS})
    endforeach()
endforeach()



# TODO: Add tests and install targets if needed.