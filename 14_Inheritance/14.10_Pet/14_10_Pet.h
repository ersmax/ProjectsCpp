#ifndef PET_14_10_H
#define PET_14_10_H

#include <string>

namespace myNamespacePet
{
	class Pet
	{
	public:
		Pet();
		Pet(const std::string& theName, int theAge, int theWeight);
		virtual ~Pet() = default;
		virtual const std::string& getLifespan() const;
		const std::string& getName() const;
		int getAge() const;
		int getWeight() const;
		virtual void print(std::ostream& outputStream) const;
		friend std::istream& operator >>(std::istream& inputStream, Pet& aPet);
		friend std::ostream& operator <<(std::ostream& outputStream, const Pet& aPet);
	private:
		std::string name;
		int age;
		int weight;
	};

} // myNamespacePet

#endif // PET_14_10_H