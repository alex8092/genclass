#ifndef CLASSGENERATOR_HPP
# define CLASSGENERATOR_HPP

# include "Object.hpp"

class ClassGenerator : public Object
{
private:
	static void onExtend(Object *obj, const std::string& data);
	static void	onPrintNamespace(Object *obj, const std::string& data);
	static void	onGenerate(Object *obj, const std::string& data);
	static void	onVar(Object *obj, const std::string& data);

	bool			_extend = false;
	std::string		_extend_class = "";

	void		_append(std::stringstream& ss, int level, int encapuslation) const;

public:
	ClassGenerator(const std::string& name, Object *parent = 0);
	virtual ~ClassGenerator();

	virtual const std::string	display() const;
	virtual const std::string	strnamespace() const;
	const std::string			strdata() const;
	const std::string			generate(int level, bool header) const;
};

#endif