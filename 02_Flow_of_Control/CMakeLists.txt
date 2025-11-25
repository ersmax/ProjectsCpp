# CMakeList.txt : CMake project, include source and define
# project specific logic here.
#

# Add source to this project's executable.
# add_executable (Cpp_vs_Java "02_Expressions/1_0_0_Cpp_vs_Java.cpp")

# List all folders
set(FOLDERS
    "2.01_Apartment_price"
    "2.02_Interests_deposit"
    "2.03_Financing_education"
    "2.04_Prime_numbers"
    "2.05_Cryptarithmetic_puzzle"
    "2.06_Buoyancy"
    "2.07_GPA"
    "2.08_Equivalent_Temperatures"
    "2.09_Babylonian_cyclic"
    "2.10_Text_replacement"
    "2.11_Ideal_BMI"
    "2.12_Benfords_Law"
    "2.13_Pair_sum"
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