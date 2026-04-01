#ifndef UNIVERSITY_STAFF_14_04_H
#define UNIVERSITY_STAFF_14_04_H

#include <string>

namespace myNamespaceUniversity
{
	class UniversityStaff
	{
	public:
		UniversityStaff();
		UniversityStaff(std::string theName);
		UniversityStaff(const UniversityStaff& theObject) = default;
		const std::string& getName() const;
		UniversityStaff& operator =(const UniversityStaff& aStaff) = default;
		friend std::istream& operator >>(std::istream& inputStream, UniversityStaff& aStaff);
		friend std::ostream& operator <<(std::ostream& outputStream, const UniversityStaff& aStaff);
	private:
		std::string name;
	};

} // myNamespaceUniversity

#endif // UNIVERSITY_STAFF_14_04_H
