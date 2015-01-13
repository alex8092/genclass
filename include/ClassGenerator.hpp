#ifndef CLASSGENERATOR_HPP
# define CLASSGENERATOR_HPP

# include "Object.hpp"

class ClassGenerator : public Object
{
private:
	static void	onVar(Object *obj, const std::string& data);
	static void onExtend(Object *obj, const std::string& data);
	static void	onPrintNamespace(Object *obj, const std::string& data);

	bool			_extend = false;
	std::string		_extend_class = "";

public:
	ClassGenerator(const std::string& name, Object *parent = 0);
	virtual ~ClassGenerator();

	virtual const std::string	display() const;
	virtual const std::string	strnamespace() const;
};

#endif