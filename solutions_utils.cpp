#include <fstream>
#include <string>
#include <tuple>
#include <vector>

#include "array_queue.h"
#include "solutions_utils.h"

/*
    -------------- Módulo utils --------------
    Contém procedimentos auxiliares, necessários para as funções em
    solutions.cpp funcionarem.
*/

std::string readFile(const std::string& path)
{
    // Coloca todo o conteúdo do arquivo em uma string

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

std::string popTag(std::string& text, const std::string& tag)
{
    /*
        Realiza o "pop" de uma tag no arquivo XML.
        Exemplo:

        Antes do pop, a string poderá assumir a seguinte configuração:
        <tag>...<exemplo>......</exemplo>...</tag>

        Após o pop da tag "exemplo", ficará assim:
        <tag>......</tag>

        A função retorna tudo que estiver entre <tag> e </tag>.
    */

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

std::vector<std::vector<int>> strToMatrix(const std::string& str, const int& height, const int& width)
{
    /*
        Transforma uma string de zeros e uns em uma matriz de largura
        'width' e altura 'height'.
    */

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
    /*
        Calcula a área percorrida pelo robô na matriz recebida como argumento,
        começando na posição (initialX, initialY).
    */

    if (matrix[initialX][initialY] == 0) {
        return 0;
    }

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
