#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include "Utilities.h"

using namespace std;

namespace sdds {
char Utilities::m_delimiter {};

char Utilities::getDelimiter() {
    return Utilities::m_delimiter;
}

void Utilities::setDelimiter(char newDelimeter) {
    Utilities::m_delimiter = newDelimeter;
}

size_t Utilities::getFieldWidth() const {
    return this->m_widthField;
}

void Utilities::setFieldWidth(size_t newWidth) {
    this->m_widthField = newWidth;
}

string Utilities::extractToken(
    const string& str,
    size_t& nxt,
    bool& more) {

    string token {};

    if (more) {
        size_t delPos = str.find(this->m_delimiter, nxt);
        if (delPos == nxt) {
            more = false;
            throw std::invalid_argument(
                "Incorrect Input");
        }
        else if (delPos == string::npos) {
            more = false;
        }

        size_t len = delPos - nxt;
        token = this->removeSpace(str.substr(nxt, len));

        nxt += len + 1;

        if (token.length() > this->m_widthField) {
            this->m_widthField = token.length();
        }
    }
    return token;
}

string Utilities::removeSpace(const string& str) {
    size_t pos1 = str.find_first_not_of(' ');
    size_t pos2 = str.find_last_not_of(' ');
    return str.substr(pos1, (pos2 - pos1) + 1);
}
} 
