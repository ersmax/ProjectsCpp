# CMakeList.txt : CMake project, include source and define
# project specific logic here.
#

# Add source to this project's executable.
# add_executable (Cpp_vs_Java "02_Expressions/1_0_0_Cpp_vs_Java.cpp")

# List all folders
set(FOLDERS
    "01_Volume"
    "02_Diet"
    "03_Sales_Profit_Increase"
    "04_Loan"
    "05_Truck_capacity"
    "06_Cab_fare"
    "07_Calories_deficit"
    "08_Babylonian_algorithm"
    "09_Arcade_prize"
    "10_Plane_distance"
    "11_Time"
    "12_BMI"
    "13_Coffee_intake"
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