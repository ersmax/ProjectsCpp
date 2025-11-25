#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
using namespace std;

int main ( ) {
    string line;
    fstream inputStream;


    std::cout << std::filesystem::current_path() << "\n";


    inputStream.open("02_Flow_of_Control/2.10_Text_replacement/Utilities/2_10_Text_replacement.txt");
    if (!inputStream)
        std::cerr << "Error opening the file\n";

    while (getline(inputStream, line)) {
        string word;
        istringstream iss(line);
        while (iss >> word) {
            if (word == "hate")
                word = "love";
            cout << word << " ";
        }
        cout << endl;
    }

    inputStream.close();

    return 0;
}