// fgen ////////////////////////////////////////////////////////////////////////
// file generator //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// a program to automatically generate c++ header and source files for my //////
// projects ////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

std::string style_character = "/";

std::string Input_string(std::string prompt);	

int main(int argc, char* argv[])
{	std::string comments = "";
	unsigned int column = 80;
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
	{	std::string dotslash = "./";
		std::string argument_one = argv[1];
		std::string argument_two = argv[2];
		if(argument_one == "-cpp")
		{	argument_two.append(".cpp");
			dotslash.append(argument_two);
			std::ofstream file(dotslash.c_str());
			if(file.is_open())
			{	file << style_character << style_character << " " << argument_two << " ";
				column -= 4;
				column -= argument_two.size();
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
				file << "//#include \"Headers.hpp\"" << std::endl;				
				file << "//#include \"Source.cpp\"\n" << std::endl;
				file.close();
			}
			else
			{	std::cout << "unable to create cpp file" << std::endl;
			}
		}
		else if(argument_one == "-hpp")
		{	argument_two.append(".hpp");
			dotslash.append(argument_two);
			std::ofstream file(dotslash.c_str());
			if(file.is_open())
			{	file << style_character << style_character << " " << argument_two << " ";
				column -= 4;
				column -= argument_two.size();
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
				file << "//#include \"Headers.hpp\"" << std::endl;				
				file << "//#include \"Source.cpp\"\n" << std::endl;
				file.close();
			}
			else
			{	std::cout << "unable to create hpp file" << std::endl;
			}		
		}		
		else if(argument_one == "-h")
		{	argument_two.append(".h");
			dotslash.append(argument_two);
			std::ofstream file(dotslash.c_str());
			if(file.is_open())
			{	file << style_character << style_character << " " << argument_two << " ";
				column -= 4;
				column -= argument_two.size();
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
				file.close();
			}
			else
			{	std::cout << "unable to create h file" << std::endl;
			}			
		}
		else if(argument_one == "-c")
		{	argument_two.append(".c");
			dotslash.append(argument_two);
			std::ofstream file(dotslash.c_str());
			if(file.is_open())
			{	file << style_character << style_character << " " << argument_two << " ";
				column -= 4;
				column -= argument_two.size();
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
				file.close();
			}
			else
			{	std::cout << "unable to create c file" << std::endl;
			}			
		}
		else
		{	std::cout << "Unknown file type, fgen supported filetypes are: " << std::endl;
			std::cout << "-cpp" << std::endl;
			std::cout << "-hpp" << std::endl;
			std::cout << "-c" << std::endl;
			std::cout << "-h" << std::endl;
			return -2;
			// let them know something went wrong
		}	// this could work a bit differently in the future
	}
	else
	{	std::cout << "Too many arguments for fgen" << std::endl;
		std::cout << "Try fgen '-filetype' 'filename' to generate a new source file" << std::endl;
		return -1;
		// let them know something went wrong
	}
	return 0;
}

std::string Input_string(std::string prompt)
{	std::string data = "";
	while(true)
	{	std::cout << std::endl;
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


