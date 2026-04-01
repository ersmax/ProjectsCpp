#include <vector>
#include <stdexcept>
#include "14_04_Science_Student.h"
#include "14_04_Input_Validation.h"


const std::vector<std::string> COURSES = {"Undergraduate", "Postgraduate"};

namespace 
{
	bool validateCourse(const std::string& aCourse)
	{
		for (const std::string& course : COURSES)
			if (aCourse == course)
				return true;
		std::cout << "Not a valid course. Retry\n";
		return false;
	}
}

namespace myNamespaceUniversity
{
	ScienceStudent::ScienceStudent() : Student(), discipline("No discipline"), course("No course")
	{ /* Body intentionally left empty */ }

	ScienceStudent::ScienceStudent(const std::string& theName, const int theNumber, const UniversityStaff& theProctor,
	                               std::string theDiscipline, const std::string& theCourse)
									: Student(theName, theNumber, theProctor), discipline(std::move(theDiscipline))
	{
		bool foundCourse = false;
		for (const std::string& aCourse : COURSES)
			if (theCourse == aCourse)
			{
				course = theCourse;
				foundCourse = true;
				break;
			}
		if (!foundCourse)	throw std::invalid_argument("Not a valid course\n");
	}

	std::istream& operator >>(std::istream& inputStream, ScienceStudent& aScienceStudent)
	{
		using myNamespaceValidation::readName;
		inputStream >> static_cast<Student&>(aScienceStudent);
		std::cout << "Enter a name of a discipline:\n";
		readName(inputStream, aScienceStudent.discipline);
		do
		{
			std::cout << "Enter a valid course among these:\n";
			for (const std::string& aCourse : COURSES)
				std::cout << aCourse << ' ';
			std::cout << "\nInput:\n";
			readName(inputStream, aScienceStudent.course);
		} while (!validateCourse(aScienceStudent.course));

		return inputStream;
	}

	std::ostream& operator <<(std::ostream& outputStream, const ScienceStudent& aScienceStudent)
	{
		outputStream << static_cast<const Student&>(aScienceStudent);
		outputStream << "Student discipline: " << aScienceStudent.discipline << '\n';
		outputStream << "Student course: " << aScienceStudent.course << '\n';
		return outputStream;
	}

	const std::string& ScienceStudent::getDiscipline() const { return discipline; }

	const std::string& ScienceStudent::getCourse() const { return course; }

} // myNamespaceUniversity
