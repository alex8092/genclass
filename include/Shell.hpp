#ifndef SHELL_CMD
# define SHELL_CMD

# include "Object.hpp"
# include <string>

class Shell : public Object
{
private:
	static void	onClass(Object *obj, const std::string& data);
	static void	onClassExtension(Object *obj, const std::string& data);

	std::string	_class_ext = "";

public:
	explicit Shell();
	virtual	~Shell();

	virtual const std::string	display() const;
	virtual const std::string	strnamespace() const;
	virtual const std::string	strdata() const;
	void						generate();
};

#endif