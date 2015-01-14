#ifndef CLASSGENERATOR_HPP
# define CLASSGENERATOR_HPP

# include "Object.hpp"

class ClassGenerator : public Object
{
private:
	static void	onPublic(Object *obj, const std::string& data);
	static void	onProtected(Object *obj, const std::string& data);
	static void	onPrivate(Object *obj, const std::string& data);
	static void	onVar(Object *obj, const std::string& data);
	static void onExtend(Object *obj, const std::string& data);
	static void	onPrintNamespace(Object *obj, const std::string& data);
	static void	onGenerate(Object *obj, const std::string& data);

	bool			_extend = false;
	bool			_public = true;
	bool			_protected = false;
	std::string		_extend_class = "";

public:
	ClassGenerator(const std::string& name, Object *parent = 0);
	virtual ~ClassGenerator();

	inline bool	isPublic() const {
		return (this->_public && !this->_protected);
	}

	inline bool isProtected() const {
		return (!this->_public && this->_protected);
	}

	inline bool isPrivate() const {
		return (!this->_public && !this->_protected);
	}

	virtual const std::string	display() const;
	virtual const std::string	strnamespace() const;
	const std::string			generate(int level, bool header) const;
};

#endif