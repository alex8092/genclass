#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include "Shell.hpp"

int	main(int ac, char **av)
{
	Shell	sh;
	while (sh.waitCmd())
		;
	sh.generate();
	return (0);
}
