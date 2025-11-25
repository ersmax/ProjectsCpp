# CMakeList.txt : CMake project, include source and define
# project specific logic here.
#

# Add source to this project's executable.
# add_executable (Cpp_vs_Java "02_Expressions/1_0_0_Cpp_vs_Java.cpp")

# List all folders
set(FOLDERS
    "3.01_File_size"
    "3.02_Salary_hike"
    "3.03_Future_salary_hike"
    "3.04_Gravitational_force"
    "3.05_Clothing_size"
    "3.06_Scores_statistics"
    "3.07_Euclidean_distance"
    "3.08_Bottles_beer"
    "3.09_Game_of_craps"
    "3.10_Estimated_height"
    "3.11_Game_of_Pig"
    "3.12_Day_from_date"
    "3.13_Price_Winners_Lottery"
    "3.14_Babylonian_square_root"
    "3.15_Likelihood_death"
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