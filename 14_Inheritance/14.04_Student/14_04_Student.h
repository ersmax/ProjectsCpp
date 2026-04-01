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
		const std::string& getUniversity() const;
		const std::string& getRegistration() const;
		const std::string& getProctor() const;
		friend std::istream& operator >>(std::istream& inputStream, Student& aStudent);
		friend std::ostream& operator <<(std::ostream& outputStream, const Student& aStudent);
	private:
		std::string universityName;
		int registrationNumber;
		UniversityStaff proctor;
	};


} // myNamespaceUniversity


#endif // STUDENT_14_04_H
