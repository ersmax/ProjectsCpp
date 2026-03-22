#include "11.01_f.h"
#include "11.01_g.h"

int main( )
{
	{
		using A::f;
		f();
	}
	{
		using A::g;
		g();
	}
	return 0;
}
