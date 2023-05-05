#ifndef SDDS_CustomerOrder
#define SDDS_CustomerOrder
#include <iostream>
#include <string>
#include "Station.h"

namespace sdds {

struct Item {
    std::string m_itemName {};
    size_t m_serialNumber { 0 };
    bool m_isFilled { false };

    Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder {
    static size_t m_widthField;

    std::string m_name {};
    std::string m_product {};
    size_t m_cntItem {};
    Item** m_lstItem {};

public:

    // Disable copy operations
    CustomerOrder(const CustomerOrder&) = delete;
    CustomerOrder& operator=(const CustomerOrder&) = delete;

    // Constructors
    CustomerOrder() {}
    //one argument constructor
    CustomerOrder(const std::string orderStr);
    //move constructor
    CustomerOrder(CustomerOrder&& source) noexcept;

    // Destructor
    ~CustomerOrder();

    // Overloaded operators
    CustomerOrder& operator=(CustomerOrder&& source) noexcept;
    //check whether the order is filled or not
    bool isOrderFilled() const;
    //check if the item is filled or not
    bool isItemFilled(const std::string& itemName) const;
    //fills the incomplete order in the station
    void fillItem(Station& station, std::ostream& os);
    //display function
    void display(std::ostream& os) const;
};

} // namespace sdds

#endif // !DEBUG
