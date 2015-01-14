#ifndef VARIABLE_HPP
# define VARIABLE_HPP

# include "Object.hpp"

class Variable : public Object
{
private:
	static void	onType(Object *obj, const std::string& data);
	static void	onStatic(Object *obj, const std::string& data);
	static void	onDefault(Object *obj, const std::string& data);
	static void onConst(Object *obj, const std::string& data);
	static void onSet(Object *obj, const std::string& data);
	static void onGet(Object *obj, const std::string& data);

	std::string	_type = "void";
	std::string	_default = "";
	bool		_const = false;
	bool		_static = false;
	bool		_get = true;
	bool		_set = true;

public:
	Variable(const std::string& name, Object *parent);
	virtual ~Variable();

	virtual const std::string	display() const;
	virtual const std::string	strnamespace() const;

	inline Variable& setType(const std::string& type) {
		this->_type = type;
		return (*this);
	}

	inline const std::string& type() const {
		return (this->_type);
	}

	inline bool					isStatic() const {
		return (this->_static);
	}
	inline bool					isConst() const {
		return (this->_const);
	}
	inline bool					isGet() const {
		return (this->_get);
	}
	inline bool					isSet() const {
		return (this->_set);
	}

	inline const std::string&	getDefault() const {
		return (this->_default);
	}
};

#endif