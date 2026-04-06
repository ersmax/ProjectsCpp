#ifndef MENU_14_08_H
#define MENU_14_08_H

#include "14_08_Message.h"

typedef myNamespaceBlog::Message *MessagePtr;

namespace myNamespaceBlog
{
	class Blog
	{
	public:
		Blog();
		Blog(const Blog& anotherBlog);
		Blog& operator =(const Blog& anotherBlog);
		~Blog();
		const Message& operator [](int idx) const;
		Message& operator [](int idx);
		int getNumMessages() const;
		//   Postcondition: returns the number of messages in the blog
		void addNewMessage(const Message& newMessage);
		//   Postcondition: adds a new message to the end of the blog
		void deleteMessage(int index);
		//   Precondition: index is 0-normalized (0 <= index < nMessages)
		//   Postcondition: deletes the message at the specified index from the blog
	private:
		MessagePtr blogMessages;
		//   Postcondition: points to a dynamic array of messages of type Message
		int nMessages;
	};

} // myNamespaceBlog

#endif // MENU_14_08_H