#include "Shell.hpp"
#include "ClassGenerator.hpp"
#include <iostream>
#include <fstream>

Shell::Shell() :
	Object("", 0)
{
	this->registerCmd("class", Shell::onClass);
}

Shell::~Shell()
{

}

const std::string	Shell::display() const {
	return ("");
}

const std::string	Shell::strnamespace() const {
	return ("");
}

void				Shell::onClass(Object *obj, const std::string& data)
{
	if (data.empty()) {
		std::cerr << "An class cannot have an empty name" << std::endl;
		return ;
	}
	ClassGenerator *gene = new ClassGenerator(data, obj);
	gene->registerCmd("class", Shell::onClass);
	while (gene->waitCmd())
		;
}


void				Shell::generate()
{
	std::ofstream source, header;

	for (auto it : this->objects()) {
		ClassGenerator *cg = dynamic_cast<ClassGenerator*>(it);
		if (cg) {

		}
	}
}