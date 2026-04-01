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
		const std::string& getDiscipline() const;
		const std::string& getCourse() const;
		friend std::istream& operator >>(std::istream& inputStream, ScienceStudent& aScienceStudent);
		friend std::ostream& operator <<(std::ostream& outputStream, const ScienceStudent& aScienceStudent);
	private:
		std::string discipline;
		std::string course;
	};

} // myNamespaceUniversity

#endif // SCIENCE_STUDENT_14_04_H
