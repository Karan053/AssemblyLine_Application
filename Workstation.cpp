#include "Workstation.h"
#include "CustomerOrder.h"
#include <deque>
#include <string>

using namespace std;

namespace sdds {
deque<CustomerOrder> g_pending{};
deque<CustomerOrder> g_completed{};
deque<CustomerOrder> g_incomplete{};

void Workstation::fill(std::ostream &ostr) {
  if (!this->m_orders.empty())
    this->m_orders.front().fillItem(*this, ostr);
}

bool Workstation::attemptToMoveOrder() {
  if (!this->m_orders.empty()) {
      CustomerOrder& temp = this->m_orders.front();

      if (temp.isItemFilled(this->getItemName())
          || this->getQuantity() <= 0)
      {
          if (this->m_pNextStation != nullptr) {
              *this->m_pNextStation += std::move(temp);
          }
          else {
              if (temp.isOrderFilled()) {
                  g_completed.push_back(std::move(temp));
              }
              else {
                  g_incomplete.push_back(std::move(temp));
              }
          }
          this->m_orders.pop_front();
          return true;
      }
  }

  return false;
}

void Workstation::setNextStation(Workstation *station) {
  this->m_pNextStation = station;
}

Workstation *Workstation::getNextStation() const {

  return this->m_pNextStation;
}

void Workstation::display(std::ostream &os) const {
  os << this->getItemName() << " --> ";
  if (this->m_pNextStation == nullptr)
    os << "End of Line" << endl;
  else
    os << this->m_pNextStation->getItemName() << endl;
}

Workstation &Workstation::operator+=(CustomerOrder &&newOrder) {
  this->m_orders.push_back(std::move(newOrder));
  return *this;
}
} // namespace sdds
