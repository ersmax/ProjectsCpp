# CMakeList.txt : CMake project, include source and define
# project specific logic here.
#

# Add source to this project's executable.
# add_executable (Cpp_vs_Java "02_Expressions/1_0_0_Cpp_vs_Java.cpp")

# List all folders
set(FOLDERS
    "5.01_Graph_Car_Mileage"
    "5.02_Delete_Repeated_Characters"
    "5.03_Standard_Deviation"
    "5.04_Vowels_Count"
    "5.05_Integer_Overflow_Sum_With_Arrays"
    "5.06_Contest_Score"
    "5.07_Histogram_Grades"
    "5.08_Birthday_Paradox"
    "5.09_Tic_Tac_Toe"
    "5.10_Ice_Cream_Parlor"
    "5.11_Histogram_Production"
    "5.12_Game_of_Life"
    "5.13_Memory_Matching_Cards"
    "5.14_Movie_Recommendation"
    "5.15_Randomized_Challenge_Response_System"
    "5.16_Movie_Recommender_From_File"
    "5.17_Benford_Law_Arrays"
    "5.18_Highest_Score_Players"
    "5.19_Players_Stats"
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