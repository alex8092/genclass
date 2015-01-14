#include "Shell.hpp"
#include "ClassGenerator.hpp"
#include <iostream>
#include <fstream>

Shell::Shell() :
	Object("", 0)
{
	this->registerCmd("class", Shell::onClass, "class <classname> -> create class in object");
	this->registerCmd("class_extension", Shell::onClassExtension, "class_extension [extension] -> add .[extension].{hpp,cpp} after class name");
}

Shell::~Shell()
{

}

const std::string	Shell::display() const {
	return ("");
}

const std::string	Shell::strnamespace() const {
	return ("");
}

const std::string	Shell::strdata() const {
	return ("");
}

void				Shell::onClass(Object *obj, const std::string& data)
{
	if (data.empty()) {
		std::cerr << "An class cannot have an empty name" << std::endl;
		return ;
	}
	bool	in = false;
	for (auto it : obj->objects()) {
		if (it->getName().compare(data) == 0) {
			it->waitCmd();
			in = true;
		}
	}
	ClassGenerator *gene = new ClassGenerator(data, obj);
	gene->registerCmd("class", Shell::onClass, "class <classname> -> create class in object");
	while (gene->waitCmd())
		;
}

void				Shell::onClassExtension(Object *obj, const std::string& data)
{
	Shell	*sh = dynamic_cast<Shell*>(obj);

	if (sh) {
		if (data.empty()) {
			sh->_class_ext = "";
		} else {
			sh->_class_ext = data;
		}
	}
}


void				Shell::generate()
{
	std::ofstream source, header;

	for (auto it : this->objects()) {
		ClassGenerator *cg = dynamic_cast<ClassGenerator*>(it);
		if (cg) {
			std::string header_file = (cg->getName() + (this->_class_ext.empty() ? "" : "." + this->_class_ext) + ".hpp");
			std::string source_file = (cg->getName() + (this->_class_ext.empty() ? "" : "." + this->_class_ext) + ".cpp");
			header.open(header_file.c_str());
			if (header.is_open()) {
				source.open(source_file.c_str());
				if (source.is_open()) {
					std::string classname = cg->getName();
					if (!this->_class_ext.empty())
						classname += "_" + this->_class_ext;
					std::transform(classname.begin(), classname.end(), classname.begin(), ::toupper);
					header << "#ifndef _" << classname << "_HPP\n# define _" << classname << "_HPP\n\n";
					header << cg->generate(0, true);
					header << "#endif\n";
					source << "#include \"" << header_file << "\"\n\n";
					source << cg->generate(0, false);
					source.close();
				} else {
					std::cerr << "Cannot open source file [" << source_file << "]" << std::endl;
				}
				header.close();
			} else {
				std::cerr << "Cannot open header file [" << header_file << "]" << std::endl;
			}
		}
	}
}