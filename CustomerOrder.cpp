#include <iomanip>
#include <iostream>
#include <string>
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
size_t CustomerOrder::m_widthField {};

CustomerOrder::CustomerOrder(const string orderStr) {
    Utilities utils {};
    bool more = true;
    size_t nxt = 0u;

    this->m_name = utils.extractToken(orderStr, nxt, more);
    this->m_product = utils.extractToken(orderStr, nxt, more);

    // Count num of items to extract
    bool ExtraMore = more;
    size_t ExtraNxt = nxt;
    while (ExtraMore) {
        utils.extractToken(orderStr, ExtraNxt, ExtraMore);
        this->m_cntItem++;
    }

    // Extract items
    this->m_lstItem = new Item* [this->m_cntItem] {};
    for (size_t i = 0; i < this->m_cntItem; i++) {
        this->m_lstItem[i] = new Item(utils.extractToken(orderStr, nxt, more));
    }

    if (CustomerOrder::m_widthField < utils.getFieldWidth()) {
        CustomerOrder::m_widthField = utils.getFieldWidth();
    }
}

CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {
    *this = std::move(other);
}

CustomerOrder::~CustomerOrder() {
    for (size_t i = 0; i < this->m_cntItem; i++) {
        delete this->m_lstItem[i];
    }
    delete[] this->m_lstItem;
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
    if (this != &src) {
        for (size_t i = 0; i < this->m_cntItem; i++) {
            delete this->m_lstItem[i];
        }
        delete[] this->m_lstItem;

        this->m_name = std::move(src.m_name);
        this->m_product = std::move(src.m_product);
        this->m_cntItem = src.m_cntItem;
        this->m_lstItem = src.m_lstItem;

        src.m_cntItem = 0;
        src.m_lstItem = nullptr;
    }

    return *this;
}

bool CustomerOrder::isOrderFilled() const {
    for (size_t i = 0; i < this->m_cntItem; i++) {
        if (!this->m_lstItem[i]->m_isFilled) return false;
    }
    return true;
}

bool CustomerOrder::isItemFilled(const string& itemName) const {
    for (size_t i = 0; i < this->m_cntItem; i++) {
        const Item& thisItem = *this->m_lstItem[i];
        if (thisItem.m_itemName == itemName && !thisItem.m_isFilled)
            return false;
    }
    return true;
}

void CustomerOrder::fillItem(Station& station, ostream& os) {
    bool added = false;
    for (size_t i = 0; i < this->m_cntItem && !added; i++) {

        Item& temp = *this->m_lstItem[i];

        bool checkStation = temp.m_itemName == station.getItemName();
        bool checkFill= !temp.m_isFilled;

        if (checkStation && checkFill) {

            if (station.getQuantity() > 0) {
                station.updateQuantity();
                temp.m_serialNumber = station.getNextSerialNumber();
                temp.m_isFilled = true;
                os << "    Filled ";
                os << this->m_name << ", ";
                os << this->m_product << " [";
                os << temp.m_itemName << "]" << endl;
                added = true;
            }
            else {
                os << "    Unable to fill ";
                os << this->m_name << ", ";
                os << this->m_product << " [";
                os << temp.m_itemName << "]" << endl;
            }
        }
    }
}

void CustomerOrder::display(ostream& os) const {

    os << this->m_name << " - " << this->m_product << endl;

    for (size_t i = 0; i < this->m_cntItem; i++) {
        const Item& thisItem = *this->m_lstItem[i];
        os << "[";
        os << setfill('0') << right << setw(6);
        os << thisItem.m_serialNumber;
        os << "] ";
        os << setfill(' ') << left << setw(CustomerOrder::m_widthField);
        os << thisItem.m_itemName;
        os << "   - ";
        os << (thisItem.m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
    }
}
}
