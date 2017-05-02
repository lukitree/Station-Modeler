#include "PageGenerator.h"
#include <sstream>


PageGenerator::PageGenerator(std::string filename, std::vector<std::string>& images)
{
	page.open(filename);
	head();
	content(images);
	tail();
	page.close();
}

void PageGenerator::head()
{
	std::stringstream s;

	s << "<!DOCTYPE html>\n"
		<< "<html>"
		<< "<head>\n"
		<< "<title>Station Models</title>\n"
		<< "<head>\n"
		<< "<body>\n"
		<< "<h1>Station Models</h1>\n"
		<< "Automatically Generated Page\n"
		<< "<hr />";

	page << s.str();
}

void PageGenerator::content(std::vector<std::string>& images)
{
	std::stringstream s;

	for (const auto& el : images)
	{
		s << "<img src='" << "images/" << el << ".png" << "'>\n";
	}

	page << s.str();
}

void PageGenerator::tail()
{
	std::stringstream s;

	s << "<hr />\n"
		<< "<center>Copyright &copy; 2017 Edward Jenco<br> All Rights Reserved</center>\n"
		<< "</body>\n"
		<< "</html>";

	page << s.str();
}
