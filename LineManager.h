#ifndef SDDS_LineManager
#define SDDS_LineManager
#include "Workstation.h"
#include <iostream>
#include <vector>

namespace sdds {
class LineManager {
  // the collection of workstations
  std::vector<Workstation *> m_activeLine{};
  // total number of CustomerOrder
  size_t m_cntCustomerOrder{};
  // points to the first active station on the current line
  Workstation *m_firstStation{};

public:
  // custom constructor that load the data from the file
  LineManager(const std::string &file,
              const std::vector<Workstation *> &stations);

  // this modifier reorders the workstations present in the instance variable
  // `m_activeLine`
  void reorderStations();

  // this modifier performs **one** iteration of operations
  bool run(std::ostream &os);

  // display function
  void display(std::ostream &os) const;
};
} // namespace sdds

#endif // DEBUG
