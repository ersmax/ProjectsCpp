#ifndef PERSON_14_05_H
#define PERSON_14_05_H

#include <string>

namespace myNamespacePeople
{
	class Person
	{
	public:
		Person();
		Person(std::string theName);
		Person(const Person& theObject) = default;
		const std::string& getName() const;
		Person& operator =(const Person& aStaff) = default;
		friend std::istream& operator >>(std::istream& inputStream, Person& aStaff);
		friend std::ostream& operator <<(std::ostream& outputStream, const Person& aStaff);
	private:
		std::string name;
	};

} // myNamespaceUniversity

#endif // PERSON_14_05_H
