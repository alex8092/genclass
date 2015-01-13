#ifndef SHELL_CMD
# define SHELL_CMD

# include "Object.hpp"

class Shell : public Object
{
private:
	static void	onClass(Object *obj, const std::string& data);

public:
	explicit Shell();
	virtual	~Shell();

	virtual const std::string	display() const;
	virtual const std::string	strnamespace() const;
	void						generate();
};

#endif