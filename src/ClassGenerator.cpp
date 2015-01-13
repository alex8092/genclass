#include "ClassGenerator.hpp"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>

ClassGenerator::ClassGenerator(const std::string& name, Object *parent) :
	Object(name, parent)
{
	this->registerCmd("var", ClassGenerator::onVar);
	this->registerCmd("extend", ClassGenerator::onExtend);
	this->registerCmd("printNamespace", ClassGenerator::onPrintNamespace);
}

ClassGenerator::~ClassGenerator()
{

}

const std::string	ClassGenerator::display() const {
	if (this->parent() && !this->parent()->display().empty())
		return (this->parent()->display() + " - Class[" + this->getName() + "]");
	return ("Class[" + this->getName()+"]");
}

const std::string	ClassGenerator::strnamespace() const {
	if (this->parent())
		return (this->parent()->strnamespace() + this->getName() + "::");
	else
		return (this->getName() + "::");
}

void	ClassGenerator::onVar(Object *obj, const std::string& data) {
	std::cout << "\tvar -> " << data << std::endl;
}

void	ClassGenerator::onExtend(Object *obj, const std::string& data) {
	ClassGenerator *self = dynamic_cast<ClassGenerator*>(obj);
	if (self) {
		if (data.empty())
			self->_extend = false;
		else
		{
			self->_extend = true;
			self->_extend_class = data;
		}
	}
}

void	ClassGenerator::onPrintNamespace(Object *obj, const std::string& data) {
	std::cout << "namespace: " << obj->strnamespace() << std::endl;
}