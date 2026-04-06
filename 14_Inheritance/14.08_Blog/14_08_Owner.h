#ifndef OWNER_14_08_H
#define OWNER_14_08_H
#include "14_08_Viewer.h"


namespace myNamespaceBlog
{
	class Owner : public Viewer
	{
	public:
		Owner();
		Owner(Blog& theBlog);
		Owner(const std::string& theName, Blog& theBlog);
		void menu();
		//   Postcondition: displays the menu of the owner and allows the owner to choose an option
		// among these: (1) Print all titles of the messages in the blog, 
		// (2) print the content of a message, (3) post a new message, (4) delete an old message, 
		// and (0) exit the menu
  protected:
		void postNewMessage();
		//   Precondition: the method is protected to share the functionalities
		// with (possible) derived classes of Owner, but not with the Viewer class
		//   Postcondition: prompts the owner to enter the title and content of a new message,
		// and adds the new message to the end of the blog
		void deleteOldMessage();
		//   Postcondition: prompts the owner to enter the number of a message, 
		// and deletes the message from the blog
	};

} // myNamespaceBlog


#endif // OWNER_14_08_H