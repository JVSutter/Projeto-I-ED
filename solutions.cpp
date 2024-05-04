#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "array_stack.h"
#include "array_queue.h"
#include "solutions_utils.h"
#include "solutions.h"

/*
    -------------- Módulo principal --------------
    Cada função corresponde a uma tarefa do trabalho

    validateXml -> questão 1
    computeCleanupArea -> questão 2
*/

static bool validateXml(const std::string& text)
{
    // Função responsável por determinar a validade da sintaxe no arquivo XML

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

void computeCleanupArea(const std::string& path)
{
    // Função responsável por computar a área de limpeza do robô

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
