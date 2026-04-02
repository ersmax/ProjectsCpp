#ifndef SCIENCE_STUDENT_14_04_H
#define SCIENCE_STUDENT_14_04_H

#include "14_04_Student.h"

namespace myNamespaceUniversity
{
	class ScienceStudent : public Student
	{
	public:
		ScienceStudent();
		ScienceStudent(const std::string& theName, int theNumber, const UniversityStaff& theProctor,
		               std::string theDiscipline, const std::string& theCourse);
		ScienceStudent(const ScienceStudent& theObject) = default;
		ScienceStudent& operator =(const ScienceStudent& aScienceStudent) = default;
		const std::string& getDiscipline() const;
		const std::string& getCourse() const;
		friend std::istream& operator >>(std::istream& inputStream, ScienceStudent& aScienceStudent);
		//   Postcondition: The student's university name, registration number, proctor, discipline, 
		// and course have been read from the input stream and stored in aScienceStudent. 
		// The course must be either "Undergraduate" or "Postgraduate". 
		// If the input is invalid, the user is prompted to re-enter the information until valid input is entered.
		friend std::ostream& operator <<(std::ostream& outputStream, const ScienceStudent& aScienceStudent);
		//   Postcondition: The student's university name, registration number, proctor, discipline, 
		// and course have been printed to the output stream.
	private:
		std::string discipline;
		std::string course;
	};

} // myNamespaceUniversity

#endif // SCIENCE_STUDENT_14_04_H
