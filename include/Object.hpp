#ifndef OBJECT_HPP
# define OBJECT_HPP

# include <string>
# include <vector>
# include <map>

class Object
{
public:
	typedef void (*func_callback)(Object *, const std::string&);

private:
	Object 															*_parent;
	std::vector<Object*>											_subobjects;
	std::string														_name;
	std::map<std::string, func_callback>							_allow_cmds;

public:

	explicit Object(const std::string& name, Object *parent);
	explicit Object(const Object& obj);
	Object&	operator=(const Object& obj);
	virtual	~Object();

	virtual const std::string	display() const = 0;
	virtual const std::string	strnamespace() const = 0;
	Object&	addObject(Object& obj);

	inline size_t				nbObjects() const {
		return (this->_subobjects.size());
	}

	inline const Object&		object(size_t index) const {
		return (*this->_subobjects[index]);
	}

	inline std::vector<Object*>&	objects() {
		return (this->_subobjects);
	}

	inline Object&				registerCmd(const std::string& name, func_callback f) {
		this->_allow_cmds[name] = f;
		return (*this);
	}

	inline const std::string&	getName() const {
		return (this->_name);
	}

	inline Object*				parent() {
		return (this->_parent);
	}

	inline const Object*				parent() const {
		return (this->_parent);
	}

	bool						waitCmd();
};

#endif