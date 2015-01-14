#include "ClassGenerator.hpp"
#include "Variable.hpp"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sstream>

ClassGenerator::ClassGenerator(const std::string& name, Object *parent) :
	Object(name, parent)
{
	this->registerCmd("var", ClassGenerator::onVar, "var <name>=<type> -> add a variable of \"type\"");
	this->registerCmd("extend", ClassGenerator::onExtend, "extend [classname] -> set or unset extend classname");
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
	return (this->strdata() + "::");
}

const std::string 	ClassGenerator::strdata() const {
	if (this->parent())
		return (this->parent()->strnamespace() + this->getName());
	else
		return (this->getName());
}

void	ClassGenerator::onVar(Object *obj, const std::string& data) {
	auto index = data.find_first_of('=');
	if (index != std::string::npos) {
		std::string name = data.substr(0, index);
		std::string type = data.substr(index + 1);
		bool create = true;
		for (auto it : obj->objects()) {
			Variable  *v = dynamic_cast<Variable*>(it);
			if (v && v->getName().compare(name) == 0)
			{
				std::cout << "An variable of this name already exist" << std::endl;
				create = false;
				while (v->waitCmd())
					;
			}
		}
		if (create) {
			Variable *v = new Variable(name, obj);
			v->setType(type);
			while (v->waitCmd())
				;
		}
	} else {
		bool error = true;
		for (auto it : obj->objects()) {
			Variable  *v = dynamic_cast<Variable*>(it);
			if (v && v->getName().compare(data) == 0)
			{
				error = false;
				while (v->waitCmd())
					;
			}
		}
		if (error)
			std::cerr << "Wrong syntax [" << data << "] (see help)" << std::endl;
	}
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

void			ClassGenerator::_append(std::stringstream& ss, int level, int encapuslation) const
{
	for (auto it : this->objects()) {
		if ((it->isPrivate() && encapuslation == 0) || (it->isProtected() && encapuslation == 1) || (it->isPublic() && encapuslation == 2)) {
			ClassGenerator *cg = dynamic_cast<ClassGenerator*>(it);
			if (cg) {
				ss << cg->generate(level + 1, true);
				continue ;
			}
			Variable *v = dynamic_cast<Variable*>(it);
			if (v) {
				this->print_level(ss, level + 1);
				if (v->isStatic())
					ss << "static ";
				if (v->isConst())
					ss << "const ";
				ss << v->type() << " _" << v->getName() << ";\n";

			}
		}
	}
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
		this->_append(ss, level, 0);
		ss << "\n";
		this->print_level(ss, level) << "protected:\n";
		this->_append(ss, level, 1);
		ss << "\n";
		this->print_level(ss, level) << "public:\n";
		this->_append(ss, level, 2);
		ss << "\n";
		this->print_level(ss, level + 1) << this->getName() << "();\n";
		this->print_level(ss, level + 1) << "~" << this->getName() << "();\n";
		this->print_level(ss, level + 1) << this->getName() << "(const " << this->strdata() << "& obj);\n";
		this->print_level(ss, level + 1) << this->getName() << "& operator=(const " << this->getName() << "& obj);\n";
		ss << "\n\n";
		bool in = false;
		for (auto it : this->objects()) {
			Variable *v = dynamic_cast<Variable*>(it);
			if (v && v->isGet()) {
				std::string varname = v->getName();
				varname[0] = ::toupper(varname[0]);
				this->print_level(ss, level + 1);
				if (v->isStatic())
					ss << "static ";
				ss << "inline const " << v->type() << "& get" << varname << "() const {\n";
				this->print_level(ss, level + 2) << "return (";
				if (v->isStatic())
					ss << v->strnamespace();
				else
					ss << "this->";
				ss << "_" << v->getName() << ");\n";
				this->print_level(ss, level + 1) << "}\n";
				in = true;
			}
			if (v && v->isSet() && !v->isConst()) {
				std::string varname = v->getName();
				varname[0] = ::toupper(varname[0]);
				if (!v->isStatic()) {
					this->print_level(ss, level + 1) << "inline " << this->getName() << "& set" << varname << "(const " << v->type() << "& v) {\n";
					this->print_level(ss, level + 2) << "this->_" << v->getName() << " = v;\n";
					this->print_level(ss, level + 2) << "return (*this);\n";
				} else {
					this->print_level(ss, level + 1) << "static inline void set" << varname << "(const " << v->type() << "& v) {\n";
					this->print_level(ss, level + 2) << this->strnamespace() << "_" << v->getName() << " = v;\n";
				}
				this->print_level(ss, level + 1) << "}\n";
			}
		}
		if (in)
			ss << "\n\n";
		this->print_level(ss, level) << "};\n";
	} else {
		bool in = false;
		for (auto it : this->objects()) {
			Variable *v = dynamic_cast<Variable*>(it);
			if (v && v->isStatic()) {
				if (v->isConst())
					ss << "const ";
				ss << v->type() << " " << v->strnamespace() << "_" << v->getName();
				if (!v->getDefault().empty())
					ss << " = " << v->getDefault() << ";\n";
				else
					ss << ";\n";
				in = true;
			}
		}
		if (in)
			ss << "\n";
		ss << this->strnamespace() << this->getName() << "()\n";
		if (this->_extend) {
			ss << "\t: " << this->_extend_class << "()\n";
		}
		bool first = true;
		for (auto it : this->objects()) {
			Variable *v = dynamic_cast<Variable*>(it);
			if (v && !v->isStatic() && !v->getDefault().empty()) {
				if (first && !this->_extend) {
					ss << "\t:\n";
					first = false;
				}
				else if (first && this->_extend) {
					ss << "\t";
					first = false;
				}
				else
					ss << ",\n";
				ss << "\t_" << v->getName() << "(" << v->getDefault() << ")";
			}
		}
		if (!first)
			ss << "\n";
		ss << "{\n";
		ss << "}\n\n";
		ss << this->strnamespace() << "~" << this->getName() << "()\n{\n}\n\n";
		ss << this->strnamespace() << this->getName() << "(const " << this->strdata() << "& obj)\n";
		if (this->_extend) {
			ss << "\t: " << this->_extend_class << "(obj)\n";
		}
		first = true;
		for (auto it : this->objects()) {
			Variable *v = dynamic_cast<Variable*>(it);
			if (v && !v->isStatic() && !v->isConst() && !v->getDefault().empty()) {
				if (first && !this->_extend) {
					ss << "\t:\n";
					first = false;
				}
				else if (first && this->_extend) {
					ss << "\t";
					first = false;
				}
				else
					ss << ",\n";
				ss << "\t_" << v->getName() << "(obj._" << v->getName() << ")";
			}
		}
		if (!first)
			ss << "\n";
		ss << "{\n";
		if (!this->_extend && first)
			ss << "\t(void)obj;\n";
		ss << "}\n\n";
		ss << this->strdata() << "& " << this->strnamespace() << "operator=(const " << this->strdata() << "& obj)\n";
		ss << "{\n";
		if (this->_extend == true)
			ss << "\t" << this->_extend_class << "::operator=(obj);\n";
		else
		{
			in = false;
			for (auto it : this->objects()) {
				Variable *v = dynamic_cast<Variable*>(it);
				if (v && !v->isStatic() && !v->isConst() && !v->getDefault().empty()) {
					ss << "\tthis->_" << v->getName() << " = obj._" << v->getName() << ";\n";
					in = true;
				}
			}
			if (!in)
				ss << "\t(void)obj;\n";
		}

		this->print_level(ss, 1) << "return (*this);\n";
		ss << "}\n\n";
		for (auto it : this->objects()) {
			ClassGenerator *cg = dynamic_cast<ClassGenerator*>(it);
			if (cg) {
				ss << cg->generate(level, false);
			}
		}
	}
	return (ss.str());
}