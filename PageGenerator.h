#pragma once

#include <vector>
#include <fstream>

class PageGenerator
{
public:
					PageGenerator(std::string page_name, std::vector<std::string>& images);

private:
	void			head();
	void			content(std::vector<std::string>& images);
	void			tail();

	std::ofstream	page;
};

