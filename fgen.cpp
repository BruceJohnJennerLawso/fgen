// fgen ////////////////////////////////////////////////////////////////////////
// file generator //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// a program to automatically generate c++ header and source files for my //////
// projects ////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

void Print_text(std::string text);
void Print_line(std::string line);

std::string Input_string(std::string prompt);	

int Create_filetype(std::string type_argument, std::string name_argument, std::string style_character);

int main(int argc, char* argv[])
{	std::string Style_character = "/";
	if(argc <= 1)
	{	//std::cout << argv[0] << std::endl;
		std::cout << "Incorrect number of arguments" << std::endl;
		std::cout << "Try fgen '-filetype' 'filename' to generate a new source file" << std::endl;
		return -1;
	}
	else if(argc == 2)
	{	std::string argument_one = argv[1];
		std::cout << "Incorrect number of arguments" << std::endl;
		std::cout << "Try fgen '-filetype' 'filename' to generate a new source file" << std::endl;
		return -1;		
	}
	else if(argc == 3)
	{	std::string argument_one = argv[1];
		std::string argument_two = argv[2];
		return Create_filetype(argument_one, argument_two, "/");
	}
	else if(argc == 4)
	{	std::string argument_one = argv[1];
		std::string argument_two = argv[2];
		std::string argument_three = argv[3];
		if(Create_filetype(argument_one, argument_three, "/") != 0)
		{	return Create_filetype(argument_one, argument_three, "/");
		}	// check if the first type is good before moving on to the next one
		else
		{	return Create_filetype(argument_two, argument_three, "/");
		}
	}	
	else
	{	std::cout << "Too many arguments for fgen" << std::endl;
		std::cout << "Try fgen '-filetype' 'filename' to generate a new source file" << std::endl;
		std::cout << argc << " Arguments" << std::endl;
		return -1;
		// let them know something went wrong
	}
}

void Print_text(std::string text)
{	std::cout << text;
}

void Print_line(std::string line)
{	std::cout << line << std::endl;
}	// this is to clean up the look of the code in general

std::string Input_string(std::string prompt)
{	std::string data = "";
	while(true)
	{	//std::cout << std::endl;
		std::cout << prompt;
		while(std::getline(std::cin, data))
		{	if (data.size() == 0)
			{	continue;	
			}	
			else
			{	return data;
			}	
		}
	}
}

int Create_filetype(std::string type_argument, std::string name_argument, std::string style_character)
{	if(type_argument == "-cpp")
	{	name_argument.append(".cpp");
	}
	else if(type_argument == "-hpp")
	{	name_argument.append(".hpp");
	}
	else if(type_argument == "-c")
	{	name_argument.append(".c");
	}
	else if(type_argument == "-h")
	{	name_argument.append(".h");
	}	// this is inefficient, but I cant remember how to do it properly
	else
	{	std::cout << "Unknown file type, current fgen supported filetypes are: " << std::endl;
		std::cout << "-cpp" << std::endl;
		std::cout << "-hpp" << std::endl;
		std::cout << "-c" << std::endl;
		std::cout << "-h" << std::endl;
		return -2;
	}
	unsigned int column = 80;
	std::string dotslash = "./";
	std::string comments = "";	
	dotslash.append(name_argument);
	std::ofstream file(dotslash.c_str());
	if(file.is_open())
	{	file << style_character << style_character << " " << name_argument << " ";
		column -= 4;
		column -= name_argument.size();
		for(unsigned int cy = 1; cy != column; ++cy)
		{	file << style_character;
		}	file << style_character << std::endl;	
		comments = Input_string("Input file comments, input / to exit: ");
		while(comments != "/")
		{	if(comments.size() > 74)
			{	std::cout << "input too long, must be 74 characters or shorter\n" << std::endl;
			}
			else
			{	file << style_character << style_character << " ";
				file << comments << " ";
				if(comments.size() < 74)
				{	unsigned int remaining_space = (74- comments.size());
					for(unsigned int cy = 0; cy != remaining_space; ++cy)
					{	file << style_character;
					}	file << style_character;
				}
				file << style_character << std::endl;
			}
			comments = Input_string("Input file comments, input / to exit: ");
		}
		for(unsigned int cy = 1; cy != 80; ++cy)
		{	file << style_character;
		}	file << style_character << std::endl;
		file << "//#include <std_files>" << std::endl;
		file << "//#include \"Headers.h\"" << std::endl;				
		file << "//#include \"Source.c\"\n" << std::endl;
		file << "//#include \"Headers.hpp\"" << std::endl;		
		file << "//#include \"Source.cpp\"\n" << std::endl;
		file.close();
		return 0;
	}
	else
	{	std::cout << "unable to create " << type_argument << " file" << std::endl;
		return -3;
	}			
}

