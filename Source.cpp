/*
@brief Main source file for the program execution.
*/
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>

#include "Options/Options.hpp"

#include "Utils/Utils.hpp"

#include "Definitions/Definitions.hpp"
#include "Parser/Parser.hpp"
#include "System/System.hpp"



int main() {

	Definitions def;
	

	//input line
	std::string line{};
	
	if (option::WANT_EXECUTE_FROM_FILE) {
		if (!readFromFile(option::FILE_EXECUTABLE, def)) {
			return -1;
		}
	}


	while (true) {
		try {
			std::getline(std::cin, line);
			
			//end of program
			if (line == "exit")
				break;

			//what type is input string
			TypeInput what = getTypeInput(line);

			switch (what) {
			case TypeInput::Declaration:
			{
				//save definition in the program
				def.insertNewDefinition(line);
				std::cout << ">\n";
				break;
			}
			case TypeInput::Execution:
			{
				//tokenize line for easy reading
				Parser parse(line);
				std::vector<std::string> lineInTokens = parse.getTokens();
				System sys(lineInTokens, def);
				Value result = sys.execute(); //gets Value
				std::cout << "> " << result << std::endl;
				break;
			}
			case TypeInput::Unknown: //line.empty()
				break;
			}
		}catch(const std::exception& info){ //information for error
			std::cerr << info.what() << '\n';
			
		}
		catch (const std::bad_alloc& ba) { //no memory
			std::cerr << ba.what();
			return 1;
		}
		catch (...) {
			std::cerr << "Unknown error occured!";
			return 404;
		}
	}
	
	return 0;
}
