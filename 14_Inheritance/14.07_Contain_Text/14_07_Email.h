#ifndef EMAIL_14_07_H
#define EMAIL_14_07_H

#include "14_07_Document.h"

namespace myNamespaceDocs
{	
	class Email : public Document
	{
	public:
		Email();
		//   Postcondition: An Email object has been created with sender, 
		// receiver, and title initialized to "No sender", "No receiver", 
		// and "No title", respectively, and text initialized to an empty string.
		Email(	const std::string& theSender, const std::string& theReceiver,
				const std::string& theTitle, const std::string& theText);
		//   Postcondition: An Email object has been created with sender initialized to theSender, 
		// receiver initialized to theReceiver, title initialized to theTitle, and text initialized to theText.
		Email& operator =(const Email& anEmail) = default;
		const std::string& getSender() const;
		const std::string& getReceiver() const;
		const std::string& getTitle() const;
		friend std::istream& operator >>(std::istream& inputStream, Email& anEmail);
		//   Precondition: inputStream is open, anEmail is a valid Email object.
		//   Postcondition: inputStream has been modified to read a string into the text of anEmail,
		// and to read the sender, receiver, and title of anEmail.
		friend std::ostream& operator <<(std::ostream& outputStream, const Email& anEmail);
		//   Precondition: outputStream is open, anEmail is a valid Email object.
		//   Postcondition: outputStream has been modified to write the sender, receiver, title, and text of anEmail to the stream.
	private:
		std::string sender;
		std::string receiver;
		std::string title;
	};

} // myNamespaceDocs

#endif // EMAIL_14_07_H
