#ifndef MESSAGE_14_08_H
#define MESSAGE_14_08_H

#include <string>

namespace myNamespaceBlog
{
	class Message
	{
	public:
		Message();
		Message(const std::string& theTitle);
		Message(const std::string& theTitle, const std::string& theMessage);
		const std::string& getTitle() const;
		const std::string& getText() const;
		friend std::istream& operator >>(std::istream& inputStream, Message& aMessage);
		friend std::ostream& operator <<(std::ostream& outputStream, const Message& aMessage);
	private:
		std::string title;
		std::string text;
	};

} // myNamespaceBlog


#endif // MESSAGE_14_08_H
