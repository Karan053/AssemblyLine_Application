#ifndef SDDS_Station
#define SDDS_Station
#include <iostream>
#include <string>

namespace sdds {

class Station {
    static size_t m_widthField;
    static unsigned id_generator;

    int m_id {};
    std::string m_name {};
    std::string m_desc {};
    size_t m_serialNumber {};
    size_t m_count {};

public:
    // one argument constructor
    Station(const std::string line);
    // returns the name of the current `Station` object
    const std::string& getItemName() const;
    // returns the next serial number to be used on the assembly line and
    // increments `m_serialNumber`
    size_t getNextSerialNumber();
    // returns the remaining quantity of items in the `Station` object
    size_t getQuantity() const;
    // subtracts 1 from the available quantity; should not drop below 0
    void updateQuantity();
    // display function
    void display(std::ostream& os, bool full) const;
};

} // namespace sdds

#endif // !DEBUG
