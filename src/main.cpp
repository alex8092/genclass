#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include "Shell.hpp"

// void	do_class(const std::string& name, std::vector<std::pair<std::string, std::string>>& vars)
// {
// 	std::ofstream	ofs((name + ".hpp").c_str());
// 	std::string	namemaj = name;
// 	for (auto& it : namemaj)
// 		it = ::toupper(it);
// 	if (ofs.is_open())
// 	{
// 		ofs << "\n#ifndef " << namemaj << "_HPP\n";
// 		ofs << "# define " << namemaj << "_HPP\n";
// 		ofs << "\nclass " << name << "\n{\n";
// 		ofs << "\tprivate:\n";
// 		for (auto it : vars) {
// 			ofs << "\t\t" << it.first << "\t\t_" << it.second << ";\n";
// 		}
// 		ofs << "\n";
// 		ofs << "\tpublic:\n";
// 		ofs << "\t\t" << name << "();\n";
// 		ofs << "\t\t" << name << "(const " << name << "& obj);\n";
// 		ofs << "\t\t~" << name << "();\n";
// 		ofs << "\t\t" << name << "& operator=(const " << name << "& obj);\n";
// 		for (auto it : vars) {
// 			ofs << "\t\tinline const " << it.first << " get" << (char)::toupper(it.second[0]) << it.second.substr(1) << "() const {\n\t\t\treturn (this->_" << it.second << ");\n\t\t}\n";
// 		}		
// 		ofs << "};\n\n#endif\n";
// 		ofs.close();
// 	}
// 	else
// 	{
// 		std::cerr << "Cannot write .hpp" << std::endl;
// 		return ;
// 	}
// 	std::ofstream	ofs2((name + ".cpp").c_str());
// 	if (ofs2.is_open())
// 	{
// 		ofs2 << "\n#include \"" << name << ".hpp\"\n";
// 		ofs2 << "\n" << name << "::" << name << "() {}\n";
// 		ofs2 << "\n" << name << "::" << name << "(const " << name << "& obj)";
// 		if (vars.size()) {
// 			ofs2 << " :\n";
// 			bool first = true;
// 			for (auto it : vars) {
// 				if (!first) {
// 					ofs2 << ",\n";
// 				} else
// 					first = false;
// 				ofs2 << "\t_" << it.second << "(obj._" << it.second << ")";
// 			}
// 		}
// 		ofs2 << "\n{}\n";
// 		ofs2 << "\n" << name << "::~" << name << "() {}\n";
// 		ofs2 << "\n" << name << "& " << name << "::operator=(const " << name << "& obj) {\n";
// 		for (auto it : vars) {
// 			ofs2 << "\tthis->_" << it.second << " = obj._" << it.second << ";\n";
// 		}
// 		ofs2 << "\treturn (*this);\n}\n\n";
// 		ofs2.close();
// 	}
// 	else
// 	{
// 		std::cerr << "Cannot write .cpp" << std::endl;
// 		return ;
// 	}
// }

int	main(int ac, char **av)
{
	Shell	sh;
	while (sh.waitCmd())
		;
			// std::vector<std::pair<std::string, std::string>>	vars;
			// std::string line;
			// do
			// {
			// 	std::cout << av[1] << " - $> ";
			// 	if (std::getline(std::cin, line)) {
			// 		std::stringstream	ss(':');
			// 		ss << line;
			// 		std::string op;
			// 		std::getline(ss, op, ' ');
			// 		if (op.compare("var") == 0) {
			// 			std::string type;
			// 			std::string name;
			// 			std::getline(ss, type, ':');
			// 			std::getline(ss, name, ':');
			// 			vars.push_back(std::pair<std::string, std::string>(type, name));
			// 		}
			// 	} else
			// 		line = "next";
			// } while (line.compare("next"));
			// do_class(av[i], vars);
	return (0);
}
