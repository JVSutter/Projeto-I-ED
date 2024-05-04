#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "array_stack.h"
#include "array_queue.h"
#include "solutions.h"

using str_size_t = std::string::size_type;
using matrix_size_t = std::vector<std::vector<int>>::size_type;
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

static std::string popTag(std::string& text, const std::string& tag)
{
    str_size_t beginContent{};
    str_size_t endContent{};

    str_size_t currentChar{0};

    while (true) {
        if (currentChar >= text.size()) {
            return "";
        }

        str_size_t openingBracketPos{text.find('<', currentChar)};
        str_size_t closeBracketPos{text.find('>', currentChar)};

        str_size_t tagSize{(closeBracketPos - openingBracketPos) - 1};
        std::string currentTag{text.substr(openingBracketPos + 1, tagSize)};

        if (currentTag == tag) {
            beginContent = closeBracketPos + 1;
        }
        else if (currentTag == ('/' + tag)) {
            endContent = openingBracketPos - 1;
            break;
        }

        currentChar = closeBracketPos + 1;
    }

    str_size_t contentLen{endContent - beginContent + 1};
    std::string content{text.substr(beginContent, contentLen)};

    str_size_t beginErase{beginContent - tag.size() - 2};
    str_size_t eraseLen{content.size() + tag.size() * 2 + 5};
    text.erase(beginErase, eraseLen);

    return content;
}

static bool validateXml(const std::string& text)
{
    structures::ArrayStack<std::string> stack{};
    str_size_t currentChar{0};

    while (true) {
        str_size_t openingBracketPos{text.find('<', currentChar)};
        str_size_t closeBracketPos{text.find('>', currentChar)};

        if ((closeBracketPos < openingBracketPos) or
           (openingBracketPos == NOT_FOUND and closeBracketPos != NOT_FOUND) or
           (openingBracketPos != NOT_FOUND and closeBracketPos == NOT_FOUND)) {
            return false;
        }
        else if (openingBracketPos == NOT_FOUND and closeBracketPos == NOT_FOUND) {
            break;
        }

        int tagSize{static_cast<int>(closeBracketPos - openingBracketPos) - 1};
        std::string tag{text.substr(openingBracketPos + 1, tagSize)};

        if (tag.find('<') != NOT_FOUND) {
            return false;
        }

        if (tag[0] == '/') {
            std::string endTag{text.substr(openingBracketPos + 2, tagSize - 1)};

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

std::vector<std::vector<int>> strToMatrix(const std::string& str, const int& height, const int& width)
{
    std::vector<std::vector<int>> positions(static_cast<matrix_size_t>(height),
                                            std::vector<int>(static_cast<matrix_size_t>(width)));
    int currentBit{0};

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            positions[i][j] = str[currentBit] - '0';
            currentBit++;
        }
    }

    return positions;
}

int computeMatrixArea(std::vector<std::vector<int>>& matrix, const int& height,
                      const int& width, const int& initialX, const int& initialY)
{
    int area{0};
    structures::ArrayQueue<std::tuple<int, int>> positions{};
    positions.enqueue(std::make_tuple(initialX, initialY));
    std::vector<std::vector<int>> visitedElements(static_cast<matrix_size_t>(height),
                                                  std::vector<int>(static_cast<matrix_size_t>(width), 0));

    while (not positions.empty()) {
        std::tuple<int, int> currentPos{positions.dequeue()};
        int x{std::get<0>(currentPos)};
        int y{std::get<1>(currentPos)};

        if (x != (height - 1) and matrix[x + 1][y] == 1 and visitedElements[x + 1][y] == 0) {
            visitedElements[x + 1][y] = 1;
            positions.enqueue(std::make_tuple(x + 1, y));
            area++;
        }
        if (x > 0 and matrix[x - 1][y] == 1 and visitedElements[x - 1][y] == 0) {
            visitedElements[x - 1][y] = 1;
            positions.enqueue(std::make_tuple(x - 1, y));
            area++;
        }
        if (y != (width - 1) and matrix[x][y + 1] == 1 and visitedElements[x][y + 1] == 0) {
            visitedElements[x][y + 1] = 1;
            positions.enqueue(std::make_tuple(x, y + 1));
            area++;
        }
        if (y != 0 and matrix[x][y - 1] == 1 and visitedElements[x][y - 1] == 0) {
            visitedElements[x][y - 1] = 1;
            positions.enqueue(std::make_tuple(x, y - 1));
            area++;
        }
    }

    return area;
}

void computeCleanupArea(const std::string& path)
{
    std::string text{readFile(path)};
    if (not validateXml(text)) {
        std::cout << "erro" << '\n';
        return;
    }
    structures::ArrayQueue<std::tuple<int, int>> positions{};
    
    while (true) {
        std::string scenario{popTag(text, "cenario")};
        if (scenario == "") {
            break;
        }

        std::cout << popTag(scenario, "nome") << " ";
        int height{std::stoi(popTag(scenario, "altura"))};
        int width{std::stoi(popTag(scenario, "largura"))};
        int initialX{std::stoi(popTag(scenario, "x"))};
        int initialY{std::stoi(popTag(scenario, "y"))};

        std::string matrixStr{popTag(scenario, "matriz")};
        std::vector<std::vector<int>> matrix{strToMatrix(matrixStr, height, width)};
        std::cout << computeMatrixArea(matrix, height, width, initialX, initialY) << '\n';
    }
}
