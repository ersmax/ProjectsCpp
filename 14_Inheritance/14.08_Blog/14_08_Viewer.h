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
		//   Postcondition: the default constructor initializes the name of the viewer to an empty string,
		// and the pointer to the blog to nullptr
		Viewer(Blog& theBlog);
		Viewer(const std::string& theName, Blog& theBlog);
		void menu() const;
		//   Postcondition: displays the menu of the viewer and allows the viewer to choose an option
		// among these: (1) Print all titles of the messages in the blog, (2) print the content of a message,
		// and (0) exit the menu
		const Message& getMessage(int numberMessage) const;
		const BlogPtr& getBlog() const;
		friend std::ostream& operator <<(std::ostream& outputStream, const Viewer& aViewer);
		friend std::istream& operator >>(std::istream& inputStream, Viewer& aViewer);
	protected:
		void printAllTitles() const;
		//   Precondition: it is declared as protected to share functionalities with derived classes.
		//   Postcondition: prints all titles of the messages in the blog.
		void printTheMessage() const;
		//   Postcondition: prints the text message of a selected message in a blog, including the title.
		BlogPtr blog;
		//   Precondition: the pointer is initialized to point to a Blog object 
		// in the constructor of the Viewer class. If no Blog object is passed to the constructor, 
		// the pointer is initialized to nullptr.
		//	 Postcondition:	pointer to an object of class Blog 
		// (the object has a pointer to a dynamic array of type Message, 
		// and nMessages as size of dynamic array)
	private:
		std::string name;
	};

} // myNamespaceBlog

#endif // VIEWER_14_08_H