#ifndef VIEWER_14_08_H
#define VIEWER_14_08_H

#include "14_08_Blog.h"

typedef myNamespaceBlog::Blog *BlogPtr;

namespace myNamespaceBlog
{
	class Viewer
	{
	public:
		Viewer();
		Viewer(Blog& theBlog);
		Viewer(const std::string& theName, Blog& theBlog);
		virtual void menu();
		const Message& getMessage(int numberMessage) const;
		friend std::ostream& operator <<(std::ostream& outputStream, const Viewer& aViewer);
		friend std::istream& operator >>(std::istream& inputStream, Viewer& aViewer);
	protected:
		void printAllTitles() const;
		void printTheMessage() const;
		BlogPtr blog;
		// pointer to an object of class Blog 
		// (the object has a pointer to a dynamic array of type Message, 
		// and nMessages as size of dynamic array)
	private:
		std::string name;
	};


} // myNamespaceBlog

#endif // VIEWER_14_08_H