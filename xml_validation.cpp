#include <fstream>
#include <string>

#include "array_stack.h"
#include "xml_validation.h"

using str_size_t = std::string::size_type;
constexpr str_size_t NOT_FOUND{std::string::npos};


static std::string readFile(const std::string& path)
{
    std::ifstream file{};
    file.open(path);
    std::string line{};
    std::string text{};

    while(getline(file, line)) {
        text += line;
    }

    file.close();
    return text;
}

bool validateXml(const std::string& path)
{
    structures::ArrayStack<std::string> stack{};
    std::string text{readFile(path)};
    str_size_t currentChar{0};

    while (true) {
        str_size_t openBracketPos{text.find('<', currentChar)};
        str_size_t closeBracketPos{text.find('>', currentChar)};

        if ((closeBracketPos < openBracketPos) or
           (openBracketPos == NOT_FOUND and closeBracketPos != NOT_FOUND) or
           (openBracketPos != NOT_FOUND and closeBracketPos == NOT_FOUND)) {
            return false;
        }
        else if (openBracketPos == NOT_FOUND and closeBracketPos == NOT_FOUND) {
            break;
        }

        int tagSize{static_cast<int>(closeBracketPos - openBracketPos) - 1};
        std::string tag{text.substr(openBracketPos + 1, tagSize)};

        if (tag.find('<') != NOT_FOUND) {
            return false;
        }

        if (tag[0] == '/') {
            std::string endTag{text.substr(openBracketPos + 2, tagSize - 1)};

            if (stack.top() != endTag) {
                return false;
            }
            stack.pop();
        }
        else {
            stack.push(tag);
        }

        currentChar = closeBracketPos + 1;
    }

    return stack.empty();
}
