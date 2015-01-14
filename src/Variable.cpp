#include "Variable.hpp"

Variable::Variable(const std::string& name, Object *parent) :
	Object(name, parent)
{
	this->_public = false;
	this->_protected = false;
	this->registerCmd("type", Variable::onType, "type <type> -> Change the type of the variable");
	this->registerCmd("static", Variable::onStatic, "static <true|false> -> Set the variable static or not");
	this->registerCmd("default", Variable::onDefault, "default [default_value] -> Set the default value");
	this->registerCmd("const", Variable::onConst, "const <true|false> -> Set the variable const or not");
	this->registerCmd("set", Variable::onSet, "set <true|false> -> Set if a setter will be created");
	this->registerCmd("get", Variable::onGet, "get <true|false> -> Set if a getter will be created");
}

Variable::~Variable()
{

}

const std::string	Variable::display() const {
	return (this->parent()->display() + " - Var [" + this->getName() + "]"); 
}

const std::string	Variable::strnamespace() const {
	return (this->parent()->strnamespace());
}

void	Variable::onType(Object *obj, const std::string& data)
{
	if (data.empty())
	{
		std::cerr << "Syntax error (see help)" << std::endl;
		return ;
	}
	Variable *v = dynamic_cast<Variable*>(obj);
	if (v)
		v->setType(data);
}

void	Variable::onStatic(Object *obj, const std::string& data)
{
	if (data.compare("true") && data.compare("false")) {
		std::cerr << "Syntax error (see help)" << std::endl;
		return ;
	}
	Variable *v = dynamic_cast<Variable*>(obj);
	if (v) {
		if (data.compare("true") == 0)
			v->_static = true;
		else
			v->_static = false;
	}
}

void	Variable::onDefault(Object *obj, const std::string& data)
{
	Variable *v = dynamic_cast<Variable*>(obj);
	if (v) {
		v->_default = data;
	}
}

void	Variable::onConst(Object *obj, const std::string& data)
{
	if (data.compare("true") && data.compare("false")) {
		std::cerr << "Syntax error (see help)" << std::endl;
		return ;
	}
	Variable *v = dynamic_cast<Variable*>(obj);
	if (v) {
		if (data.compare("true") == 0)
			v->_const = true;
		else
			v->_const = false;
	}
}

void	Variable::onSet(Object *obj, const std::string& data)
{
	if (data.compare("true") && data.compare("false")) {
		std::cerr << "Syntax error (see help)" << std::endl;
		return ;
	}
	Variable *v = dynamic_cast<Variable*>(obj);
	if (v) {
		if (data.compare("true") == 0)
			v->_set = true;
		else
			v->_set = false;
	}
}

void	Variable::onGet(Object *obj, const std::string& data)
{
	if (data.compare("true") && data.compare("false")) {
		std::cerr << "Syntax error (see help)" << std::endl;
		return ;
	}
	Variable *v = dynamic_cast<Variable*>(obj);
	if (v) {
		if (data.compare("true") == 0)
			v->_get = true;
		else
			v->_get = false;
	}
}