#ifndef SDDS_Workstation
#define SDDS_Workstation
#include "CustomerOrder.h"
#include "Station.h"
#include <deque>
#include <iostream>
#include <ostream>

namespace sdds {
extern std::deque<CustomerOrder> g_pending;
extern std::deque<CustomerOrder> g_completed;
extern std::deque<CustomerOrder> g_incomplete;

class Workstation : public Station {
  std::deque<CustomerOrder> m_orders{};
  Workstation *m_pNextStation{};

public:
  // 1-argument constructor
  Workstation(const std::string &line) : Station(line) {}

  // this modifier fills the order
  void fill(std::ostream &ostr);

  // attempts to move the order at the front of the queue
  bool attemptToMoveOrder();

  // this modifier stores the address of the referenced `Workstation`
  void setNextStation(Workstation *station = nullptr);

  // this query returns the address of next `Workstation`
  Workstation *getNextStation() const;

  // display function
  void display(std::ostream &os) const;

  // moves the `CustomerOrder` referenced in parameter `newOrder` to the back of
  // the queue
  Workstation &operator+=(CustomerOrder &&newOrder);
};
} // namespace sdds

#endif // !DEBUG
