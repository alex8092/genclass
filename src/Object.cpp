#include "Object.hpp"
#include <iostream>
#include <sstream>

Object::Object(const std::string& name, Object* parent) :
	_parent(parent),
	_name(name)
{
	if (parent)
		parent->addObject(*this);
}

Object::Object(const Object& obj) :
	_parent(obj._parent),
	_name(obj._name)
{
}

Object::~Object()
{

}

Object&	Object::operator=(const Object& obj)
{
	this->_parent = obj._parent;
	this->_name = obj._name;
	return (*this);
}

Object&	Object::addObject(Object& obj)
{
	this->_subobjects.push_back(&obj);
	return (*this);
}

bool	Object::waitCmd()
{
	std::string	line;
	std::cout << this->display() << " $> ";
	if (std::getline(std::cin, line)) {
		std::stringstream	ss;
		ss << line;
		std::string cmd;
		if (std::getline(ss, cmd, ' ')) {
			if (cmd.compare("end") == 0)
				return (false);
			else if (cmd.compare("help") == 0)
			{
				for (auto it : this->_allow_cmds)
					std::cout << "cmd [" << it.first << "] << " << this->_helper_cmds[it.first] << std::endl;
				return (true);
			}
			else
			{
				auto it = this->_allow_cmds.find(cmd);
				if (it != this->_allow_cmds.end()) {
					if (this->_allow_cmds[cmd]) {
						std::string data = ss.str().substr(cmd.length());
						while (std::isspace(*data.begin()))
							data = data.substr(1);
						this->_allow_cmds[cmd](this, data);
						return (true);
					} else {
						std::cerr << "Invalid function for cmd [" << cmd << "]" << std::endl;
						return (true);
					}
				} else {
					std::cerr << "Unknow command [" << cmd << "]" << std::endl;
					return (true);
				}
			}
		} else {
			std::cerr << "Unknow error" << std::endl;
		}
	}
	return (false);
}