#include "Utils.hpp"
#include <cassert>

#include "../Options/Options.hpp"
#include "../Parser/Parser.hpp"
#include "../System/System.hpp"

TypeInput getTypeInput(const std::string& line) {
	if (line.empty())
		return TypeInput::Unknown;

	if (line.size() >= option::BUFFER_MAX_SIZE)
		throw std::invalid_argument("Line is too big");

	if (line.find("<-") != std::string::npos)
		return TypeInput::Declaration;


	return TypeInput::Execution;
}

bool readFromFile(const std::string& fileName, Definitions& def) {
	std::ifstream ifs(fileName, std::ios::in);

	if (!ifs.is_open())
		throw std::runtime_error("File " + fileName + " cannot be open!");

	std::string line{};
	while (std::getline(ifs, line)) {
		std::cout << line << std::endl;

		try {
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
			default: 
				std::cerr << "Unknown TypeInput value!\n";
				assert(false);
			}
		}
		catch (const std::exception& ex) {
			std::cerr << ex.what() << '\n';
		}
		catch (const std::bad_alloc& ba) {
			std::cerr << ba.what();
			return false;
		}
		catch (...) {
			std::cerr << "Unknown error happened!";
			return false;
		}

	}

	return true;
}
