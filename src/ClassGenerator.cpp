#include "ClassGenerator.hpp"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sstream>

ClassGenerator::ClassGenerator(const std::string& name, Object *parent) :
	Object(name, parent)
{
	// this->registerCmd("var", ClassGenerator::onVar);
	this->registerCmd("extend", ClassGenerator::onExtend, "extend [classname] -> set or unset extend classname");
	this->registerCmd("public", ClassGenerator::onPublic, "public -> set object public");
	this->registerCmd("protected", ClassGenerator::onProtected, "protected -> set object protected");
	this->registerCmd("private", ClassGenerator::onPrivate, "private -> set object private");
	this->registerCmd("generate", ClassGenerator::onGenerate, "generate -> print generate header and source");
	this->registerCmd("printNamespace", ClassGenerator::onPrintNamespace, "printNamespace -> print namespace of object");
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

void	ClassGenerator::onPublic(Object *obj, const std::string& data) {
	ClassGenerator *self = dynamic_cast<ClassGenerator*>(obj);
	if (self) {
		self->_public = true;
		self->_protected = false;
	}
}

void	ClassGenerator::onProtected(Object *obj, const std::string& data) {
	ClassGenerator *self = dynamic_cast<ClassGenerator*>(obj);
	if (self) {
		self->_public = false;
		self->_protected = true;
	}
}

void	ClassGenerator::onPrivate(Object *obj, const std::string& data) {
	ClassGenerator *self = dynamic_cast<ClassGenerator*>(obj);
	if (self) {
		self->_public = false;
		self->_protected = false;
	}
}

void	ClassGenerator::onGenerate(Object *obj, const std::string& data) {
	ClassGenerator *self = dynamic_cast<ClassGenerator*>(obj);
	if (self) {
		std::cout << self->generate(0, true) << std::endl;
		std::cout << self->generate(0, false) << std::endl;
	}
}


void	ClassGenerator::onPrintNamespace(Object *obj, const std::string& data) {
	std::cout << "namespace: " << obj->strnamespace() << std::endl;
}

const std::string	ClassGenerator::generate(int level, bool header) const
{
	std::stringstream	ss;
	if (header) {
		this->print_level(ss, level) << "class " << this->getName();
		if (this->_extend == true) {
			ss << " : public " << this->_extend_class << "\n";
		} else
			ss << "\n";
		this->print_level(ss, level) << "{\n\n";
		 this->print_level(ss, level) << "private:\n";
		for (auto it : this->objects()) {
			ClassGenerator *cg = dynamic_cast<ClassGenerator*>(it);
			if (cg && cg->isPrivate()) {
				ss << cg->generate(level + 1, true);
			}
		}
		ss << "\n";
		this->print_level(ss, level) << "protected:\n";
		for (auto it : this->objects()) {
			ClassGenerator *cg = dynamic_cast<ClassGenerator*>(it);
			if (cg && cg->isProtected()) {
				ss << cg->generate(level + 1, true);
			}
		}
		ss << "\n";
		this->print_level(ss, level) << "public:\n";
		for (auto it : this->objects()) {
			ClassGenerator *cg = dynamic_cast<ClassGenerator*>(it);
			if (cg && cg->isPublic()) {
				ss << cg->generate(level + 1, true);
			}
		}
		ss << "\n";
		this->print_level(ss, level + 1) << this->getName() << "();\n";
		this->print_level(ss, level + 1) << "~" << this->getName() << "();\n";
		this->print_level(ss, level + 1) << this->getName() << "(const " << this->getName() << "& obj);\n";
		this->print_level(ss, level + 1) << this->getName() << "& operator=(const " << this->getName() << "& obj);\n";
		ss << "\n\n";
		this->print_level(ss, level) << "};\n";
	} else {
		ss << this->strnamespace() << this->getName() << "()\n{\n}\n\n";
		ss << this->strnamespace() << "~" << this->getName() << "()\n{\n}\n\n";
		ss << this->strnamespace() << this->getName() << "(const " << this->strnamespace() << "& obj)\n{\n}\n\n";
		ss << this->strnamespace() << this->getName() << "& " << this->strnamespace() << "operator=(const " << this->getName() << "& obj)\n{\n";
		this->print_level(ss, 1) << "return (*this);\n}\n\n";
		for (auto it : this->objects()) {
			ClassGenerator *cg = dynamic_cast<ClassGenerator*>(it);
			if (cg) {
				ss << cg->generate(level, false);
			}
		}
	}
	return (ss.str());
}