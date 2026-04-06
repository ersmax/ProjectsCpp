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
		void menu() override;
  protected:
	  void postNewMessage();
		void deleteOldMessage();
	};

} // myNamespaceBlog


#endif // OWNER_14_08_H