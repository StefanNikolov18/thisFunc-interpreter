#include "Definitions.hpp"
#include "../Parser/Parser.hpp"
#include <stdexcept>


void Definitions::loadFromStream(std::istream& is)
{
    if (is.bad())
        throw std::runtime_error("Bad file stream!");

   
    std::string definition{};
    while (std::getline(is, definition)) {
        insertNewDefinition(definition);
    }
}

bool Definitions::isDefined(const std::string& def) const
{
    return defFuncMap.find(def) != defFuncMap.end();
}

const std::vector<std::string>& Definitions::findDefinition
(const std::string& key) const
{
    auto it = this->defFuncMap.find(key);
    if (it == defFuncMap.end())
        throw std::logic_error("Is not defined");

    return it->second.tokens;
}

const size_t Definitions::findParams(const std::string& key) const
{
    auto it = this->defFuncMap.find(key);
    if (it == defFuncMap.end())
        throw std::logic_error("Is not defined");

    return it->second.paramsCnt;
}

void Definitions::insertNewDefinition(const std::string& line)
{
    std::string name = extractName(line);
    std::vector<std::string> definition = extractDef(line);
    size_t paramCnt = extractParamCount(line);

    defFuncMap[name] = { paramCnt,definition };
}

std::string Definitions::extractName(const std::string& line)
{
    auto pos = line.find("<-");
    if (pos == std::string::npos)
        throw std::logic_error("No '<-' found in declaration");

    std::string name = line.substr(0, pos);
    size_t start = name.find_first_not_of(" \t");
    size_t end = name.find_last_not_of(" \t");

    if (start == std::string::npos)
        throw std::logic_error("Name is empty");

    return name.substr(start, end - start + 1);
}

std::vector<std::string> Definitions::extractDef(const std::string& line)
{
    auto pos = line.find("<-");
    if (pos == std::string::npos)
        throw std::logic_error("No '<-' found in declaration");

    std::string def = line.substr(pos + 2);
    Parser parseDefinition(def);
    
    return parseDefinition.getTokens();
}

//work only with digits
size_t Definitions::extractParamCount(const std::string& line)
{
    if (line.empty())
        return 0;

    size_t paramCnt = 0;
    auto pos = line.find("<-");
    if (pos == std::string::npos)
        throw std::logic_error("No '<-' found in declaration");
    bool hasDS = false;
    for (size_t i = pos + 2; i < line.size(); ++i) {
        if (line[i] == '#' && i + 1 < line.size() 
            && std::isdigit(line[i+1])) {
            int index = line[++i] - '0';
            if(index > paramCnt)
            paramCnt = index;
            hasDS = true;
        }
    }

    return hasDS ? paramCnt + 1 : 0;
}

