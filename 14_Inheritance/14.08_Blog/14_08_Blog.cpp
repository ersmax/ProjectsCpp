#include <iostream>
#include "14_08_Blog.h"

namespace myNamespaceBlog
{
	Blog::Blog() : blogMessages(nullptr), nMessages(0)
	{ /* body intentionally left empty */ }

	Blog::Blog(const Blog& anotherBlog) : nMessages(anotherBlog.nMessages)
	{
		blogMessages = new Message[nMessages];
		for (int idx = 0; idx < anotherBlog.nMessages; idx++)
			blogMessages[idx] = anotherBlog.blogMessages[idx];
	}

	Blog& Blog::operator=(const Blog& anotherBlog)
	{
		if (this == &anotherBlog)	return *this;
		if (nMessages != anotherBlog.nMessages)
		{
			delete [] blogMessages;
			blogMessages = new Message[anotherBlog.nMessages];
		}
		nMessages = anotherBlog.nMessages;
		for (int idx = 0; idx < nMessages; idx++)
			blogMessages[idx] = anotherBlog.blogMessages[idx];
		return *this;
	}

	Blog::~Blog()
	{
		delete [] blogMessages;
	}

	const Message& Blog::operator [](const int idx) const
	{
		if (idx < 0 || idx >= nMessages)
		{
			std::cout << "Illegal index access\n";
			std::exit(-1);
		}
		return blogMessages[idx];
	}

	Message& Blog::operator [](const int idx)
	{
		if (idx < 0 || idx >= nMessages)
		{
			std::cout << "Illegal index access\n";
			std::exit(-1);
		}
		return blogMessages[idx];
	}

	void Blog::addNewMessage(const Message& newMessage)
	{
		const MessagePtr temp = new Message[nMessages + 1];
		for (int idx = 0; idx < nMessages; idx++)
			temp[idx] = blogMessages[idx];

		temp[nMessages] = newMessage;
		nMessages++;

		delete [] blogMessages;
		blogMessages = temp;
	}

	void Blog::deleteMessage(const int index)
	{
		if (index < 0 || index >= nMessages)
		{
			std::cout << "Not a valid index for the message\n";
			return;
		}
		
		const MessagePtr temp = new Message[nMessages - 1];
		int destination = 0;
		for (int idx = 0; idx < nMessages; idx++)
		{
			if (idx == index)	continue;
			temp[destination++] = blogMessages[idx];
		}
		nMessages--;
		delete [] blogMessages;
		blogMessages = temp;
	}

	int Blog::getNumMessages() const { return nMessages;}

} // myNamespaceBlog