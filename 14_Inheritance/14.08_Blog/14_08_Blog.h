#ifndef MENU_14_08_H
#define MENU_14_08_H

#include "14_08_Message.h"

using myNamespaceBlog::Message;

typedef Message *MessagePtr;

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
		void addNewMessage(const Message& newMessage);
		void deleteMessage(int index);
		//   Precondition: index is 0-normalized (0 <= index < nMessages)
	private:
		MessagePtr blogMessages;
		int nMessages;
	};

} // myNamespaceBlog

#endif // MENU_14_08_H