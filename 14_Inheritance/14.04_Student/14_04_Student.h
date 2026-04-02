#ifndef STUDENT_14_04_H
#define STUDENT_14_04_H

#include "14_04_University_Staff.h"

namespace myNamespaceUniversity
{
	class Student
	{
	public:
		Student();
		Student(std::string theName, int theNumber, const UniversityStaff& theProctor);
		Student(const Student& theObject) = default;
		Student& operator =(const Student& aStudent) = default;
		const std::string& getUniversity() const;
		int getRegistration() const;
		const std::string& getProctor() const;
		friend std::istream& operator >>(std::istream& inputStream, Student& aStudent);
		//   Postcondition: The student's university name, registration number, 
		// and proctor have been read from the input stream and stored in aStudent.
		friend std::ostream& operator <<(std::ostream& outputStream, const Student& aStudent);
		//   Postcondition: The student's university name, registration number, 
		// and proctor have been printed to the output stream.
	private:
		std::string universityName;
		int registrationNumber;
		UniversityStaff proctor;
	};


} // myNamespaceUniversity


#endif // STUDENT_14_04_H
