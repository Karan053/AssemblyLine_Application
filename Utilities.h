#ifndef SDDS_Utilities
#define SDDS_Utilities
#include <iostream>
#include <string>

namespace sdds {

class Utilities {

    static char m_delimiter;

    size_t m_widthField { 1 };

    // Private Methods
    std::string removeSpace(const std::string& str);

public:
    // sets the field width of the current object
    void setFieldWidth(size_t newWidth);
    // returns the field width of the current object
    size_t getFieldWidth() const;
    // extracts a token from string `str` referred to by the first parameter
    std::string extractToken(const std::string& str, size_t& next_pos,
        bool& more);
    // sets the delimiter for this class to the character received
    static void setDelimiter(char newDelimiter);
    // returns the delimiter for this class
    static char getDelimiter();
};

}

#endif // !DEBUG
