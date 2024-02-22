#include "Controladora.hpp"

int main()
{
	Controladora* oControl = new Controladora(false);
	srand(time(NULL));
	oControl->menuPrincipal();
	cin.get();
}
