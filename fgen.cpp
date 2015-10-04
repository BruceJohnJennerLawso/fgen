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

//#define RPITHINK

#ifdef RPITHINK

#define scrWidth 30

#else

#define scrWidth 80

#endif


void Print_text(std::string text);
void Print_line(std::string line);

void Print_start_message(std::string file_name, std::string file_type);

std::string Get_type_extension(std::string type_argument);
std::string Get_style_character(std::string type_argument);

bool Is_header(std::string type_argument);

std::string Input_string(std::string prompt);	


bool noExtensionFlag(std::string input)
{
	if((input == "-noexten")||(input == "-noext"))
	{	return true;
	}
	return false;
}

int Create_filetype(std::string type_argument, std::string name_argument, std::string style_character, bool no_extension);



int main(int argc, char* argv[])
{	std::string Style_character = "/";
	if(argc <= 1)
	{	std::cout << "Incorrect number of arguments" << std::endl;
		std::cout << "Try fgen '-filetype' 'filename' to generate a new source file" << std::endl;
		return -1;
	}
	else if(argc == 2)
	{	std::string argument_one = argv[1];
		std::cout << "Incorrect number of arguments" << std::endl;
		std::cout << "Try fgen '-filetype' 'filename' to generate a new source file" << std::endl;
		// we need a bare minimum of 2 arguments to actually do stuff
		return -1;		
	}
	else if(argc == 3)
	{	std::string argument_one = argv[1];
		std::string argument_two = argv[2];
		// two arguments, so we have a filetype and a filename (hopefully)
		Print_start_message(argument_two, argument_one);
		// echo the name of the file just to make usage a bit nicer
		return Create_filetype(argument_one, argument_two, Get_style_character(argument_one), false);
		// try to create the file if possible and return whatever the function
		// spits out to indicate an error code
	}
	else if(argc == 4)
	{	std::string argument_one = argv[1];
		std::string argument_two = argv[2];
		std::string argument_three = argv[3];
		// three arguments, which we interpret as being two files with the same
		// name, but different file types (ie an .hpp/.cpp or .h/.c pair,
		// usually for distinct classes in C++)
		Print_start_message(argument_three, argument_one);
		// say hello, let us know the names of the files we will be creating
		// today
		int err = Create_filetype(argument_one, argument_three, Get_style_character(argument_one), false);
		// create the file with the first type specified
		if(err == 0)
		{	// we check to see if everything went okay
			// if not we spit out an error value and terminate
			Print_start_message(argument_three, argument_two);
			// if errything is good, we let us know the name of the next file,
			// and we try to create it
			return Create_filetype(argument_two, argument_three, Get_style_character(argument_two), false);
		}
		else
		{	return err;
		}
	}
	else if(argc == 5)
	{	std::string argument_four = argv[4];
		
		bool no_ext = noExtensionFlag(argument_four);

		std::string argument_one = argv[1];
		std::string argument_two = argv[2];
		std::string argument_three = argv[3];
		// three arguments, which we interpret as being two files with the same
		// name, but different file types (ie an .hpp/.cpp or .h/.c pair,
		// usually for distinct classes in C++)
		Print_start_message(argument_three, argument_one);
		// say hello, let us know the names of the files we will be creating
		// today
		int err = Create_filetype(argument_one, argument_three, Get_style_character(argument_one), no_ext);
		// create the file with the first type specified
		if(err == 0)
		{	// we check to see if everything went okay
			// if not we spit out an error value and terminate
			Print_start_message(argument_three, argument_two);
			// if errything is good, we let us know the name of the next file,
			// and we try to create it
			return Create_filetype(argument_two, argument_three, Get_style_character(argument_two), no_ext);
		}
		else
		{	return err;
		}
	}	
	else
	{	std::cout << "Too many arguments for fgen" << std::endl;
		std::cout << "Try fgen '-filetype' 'filename' to generate a new source file" << std::endl;
		std::cout << argc << " Arguments" << std::endl;
		// too many arguments were specified, so we really didnt know what to do
		return -1;
		// let them know something went wrong
	}
}

void Print_text(std::string text)
{	std::cout << text;
	// why did I have to learn C++ first...
}

void Print_line(std::string line)
{	std::cout << line << std::endl;
}	// this is to clean up the look of the code in general

std::string Input_string(std::string prompt)
{	std::string data = "";
	while(true)
	{	//std::cout << std::endl;
		std::cout << prompt;
		// write the prompt (ie "Input Data: " to get the user to input whatever
		while(std::getline(std::cin, data))
		{	// std::getline cycles through the input data contained in the 
			// cin stream and stores it in a string called data
			if (data.size() == 0)
			{	// If there was nothing in it, we jump back to the top of the
				// loop and try again
				continue;	
			}	
			else
			{	return data;
				// send whatever the user typed
			}	
		}
	}
}

bool typeArgumentIsC(std::string type_argument)
{	// generalization here, C and C++
	if((type_argument == "-cpp")||(type_argument == "-hpp")||(type_argument == "-h")||(type_argument == "-c"))	
	{	return true;
	}
	return false;
}



int Create_filetype(std::string type_argument, std::string name_argument, std::string style_character, bool no_extension)
{	
	// screw functional programming, Im causing side effects
	if(Get_type_extension(type_argument) == ".")
	{	return 2;
		// uhhh, oh
		// "." was the error code for basically file type not recognized
	}
	else
	{	name_argument.append(Get_type_extension(type_argument));
		// slap on the extension to the name of the file so we have a complete
		// filename , ie file.extension
	}
	unsigned int column = scrWidth;
	// personal preference is not to exceed 80 chars wide in a file, although
	// I dont care enough to force actual code into that limit, just comments
	
	// this could be read from a cfg file later
	std::string dotslash = "./";
	// ./ being the current directory here
	std::string comments = "";	
	if(no_extension == false)
	{
		dotslash.append(name_argument);
	}
	// ./filename.extension
	std::ofstream file(dotslash.c_str());
	// create a file with the name we specified
	if(file.is_open())
	{	
		if((typeArgumentIsC(type_argument) == true)||(type_argument == "-py"))
		{	
			// had to completely rethink the flow for php,
			//  totally different idea from C and py

			file << style_character << style_character << " " << name_argument << " ";
			column -= 4;
			column -= name_argument.size();
			for(unsigned int cy = 1; cy != column; ++cy)
			{	file << style_character;
			}	file << style_character << std::endl;	
			
			comments = Input_string("Input file comments, input / to exit: ");
		
			while(comments != "/")
			{	if(comments.size() > (scrWidth -6))
				{	std::cout << "input too long, must be " << (scrWidth -6) << " characters or shorter\n" << std::endl;
				}
				else
				{	file << style_character << style_character << " ";
					file << comments << " ";
					if(comments.size() < (scrWidth -6))
					{	unsigned int remaining_space = ((scrWidth -6)- comments.size());
						for(unsigned int cy = 0; cy != remaining_space; ++cy)
						{	file << style_character;
						}	file << style_character;
					}
					file << style_character << std::endl;
				}
				comments = Input_string("Input file comments, input / to exit: ");
			}
			for(unsigned int cy = 1; cy != scrWidth; ++cy)
			{	file << style_character;
			}	file << style_character << std::endl;
		
			if(typeArgumentIsC(type_argument) == true)
			{	// its C, yay
				file << "//#include <std_files>" << std::endl;
				file << "//#include \"Headers.h\"\n" << std::endl;				
				file << "//#include \"Source.c\"\n" << std::endl;
				file << "//#include \"Headers.hpp\"" << std::endl;		
				file << "//#include \"Source.cpp\"\n\n" << std::endl;
		
		
				if(Is_header(type_argument)== true)
				{	std::string header_guard = Input_string("Input header guard name: ");
					std::string start_guard = "#ifndef ";
					start_guard.append(header_guard);
					file << start_guard << std::endl;
					std::string def_guard = "#define ";
					def_guard.append(header_guard);
					file << def_guard << std::endl;
					file << "\n\n#endif" << std::endl;
				}
			}
		}
		
		

		else if(type_argument == "-php")
		{	file << "<!-- " << name_argument  <<  " -->" << std::endl;
			file << "<?php\n" << std::endl;
			file << "?>" << std::endl; 
		}
		else if(type_argument == "-sh")
		{	file << "#!/bin/bash" << std::endl;
			file << "## " << name_argument << " ##" << std::endl;
			file << "" << std::endl;
			file << "exit 0" << std::endl;
		
		}
		
		
		

		
		file.close();
		return 0;
	}
	else
	{	std::cout << "unable to create " << type_argument << " file" << std::endl;
		return -3;
	}			
}

void Print_start_message(std::string file_name, std::string file_type)
{	std::string output = "File ";
	output.append(file_name);
	output.append(Get_type_extension(file_type));
	Print_line(output);
}

std::string Get_type_extension(std::string type_argument)
{	std::string output;
	if(type_argument == "-cpp")
	{	output = ".cpp";
	}
	else if(type_argument == "-hpp")
	{	output = ".hpp";
	}
	else if(type_argument == "-c")
	{	output = ".c";
	}
	else if(type_argument == "-h")
	{	output = ".h";
	}
	else if(type_argument == "-py")
	{	output = ".py";
	}	
	else if(type_argument == "-php")
	{	output = ".php";
	}
	else if(type_argument == "-sh")
	{	output = "sh";
	}
	else
	{	std::cout << "Unknown file type, current fgen supported filetypes are: " << std::endl;
		std::cout << "-cpp" << std::endl;
		std::cout << "-hpp" << std::endl;
		std::cout << "-c" << std::endl;
		std::cout << "-h" << std::endl;
		std::cout << "-py" << std::endl;		
		std::cout << "-php" << std::endl;
		std::cout << "-sh" << std::endl;
		output = ".";
		// uhh, lets just stick some chewing gum here...
	}
	return output;
}

std::string Get_style_character(std::string type_argument)
{	std::string output;
	if(type_argument == "-cpp")
	{	output = "/";
	}
	else if(type_argument == "-hpp")
	{	output = "/";
	}
	else if(type_argument == "-c")
	{	output = "/";
	}
	else if(type_argument == "-h")
	{	output = "/";
	}
	else if(type_argument == "-php")
	{	output = "/";
		// Im just making this up as I go here, might not actually work
		// properly if the comment isnt inside php tags
		// To be safe, Im gonna generate the file with <?php ?> tags
		// and worry about html later
	}
	else if(type_argument == "-py")
	{	output = "#";
	}
	else if(type_argument == "-sh")
	{	output = "#";
	}	
	else
	{	std::cout << "Unknown file type, current fgen supported filetypes are: " << std::endl;
		std::cout << "-cpp" << std::endl;
		std::cout << "-hpp" << std::endl;
		std::cout << "-c" << std::endl;
		std::cout << "-h" << std::endl;
		std::cout << "-py" << std::endl;		
		output = ".";
		// uhh, lets just stick some chewing gum here...
	}
	return output;
}

bool Is_header(std::string type_argument)
{	if(type_argument == "-hpp")
	{	return true;
	}
	else if(type_argument == "-h")
	{	return true;
	}
	else
	{	return false;
	}	
}
