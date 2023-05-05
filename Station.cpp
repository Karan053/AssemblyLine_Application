#include <iomanip>
#include <iostream>
#include <string>
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
unsigned Station::id_generator = 1;
size_t Station::m_widthField {};

Station::Station(const string stationStr) {
    Utilities obj {};
    bool more = true;
    size_t nxt = 0u;

    this->m_id = Station::id_generator++;
    this->m_name = obj.extractToken(stationStr, nxt, more);
    this->m_serialNumber = stoul(obj.extractToken(stationStr, nxt, more));
    this->m_count = stoul(obj.extractToken(stationStr, nxt, more));

    if (this->m_widthField < obj.getFieldWidth()) {
        this->m_widthField = obj.getFieldWidth();
    }

    this->m_desc = obj.extractToken(stationStr, nxt, more);
}

const string& Station::getItemName() const {
    return this->m_name;
}

size_t Station::getNextSerialNumber() {
    return this->m_serialNumber++;
}

size_t Station::getQuantity() const {
    return this->m_count;
}

void Station::updateQuantity() {
    if (this->m_count > 0) 
        this->m_count--;
}

void Station::display(std::ostream& os, bool full) const {
    os << setw(3) << setfill('0') << right;
    os << this->m_id << " | ";
    os << setfill(' ') << setw(this->m_widthField) << left;
    os << this->m_name << "  | ";
    os << setw(6) << setfill('0') << right;
    os << this->m_serialNumber << " | ";
    os << setfill(' ') << right;
    if (full) {
        os << setw(4) << this->m_count << " | ";
        os << this->m_desc;
    }
    os << endl;
}
}
