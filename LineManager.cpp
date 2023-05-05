#include "LineManager.h"
#include "Utilities.h"
#include "Workstation.h"
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

namespace sdds {
// int LineManager::count{};

LineManager::LineManager(const std::string &file,
                         const std::vector<Workstation *> &stations) {
  if (file[0] != '\0') {
    ifstream istr(file);
    if (istr.is_open()) {
      string temp{};
      string temp2{};
      Utilities obj{};

      // fetching the data from the file
      while (!istr.eof()) {
        string line{};
        size_t nxt{};
        Workstation *current{};
        Workstation *next{};
        bool more = true;

        getline(istr, line);
        temp = obj.extractToken(line, nxt, more);
        temp2 = obj.extractToken(line, nxt, more);

        // assigning the current station
        auto station = std::find_if(stations.begin(), stations.end(),
                                    [&](Workstation *workObj) {
                                      return workObj->getItemName() == temp;
                                    });

        if (station != stations.end())
          current = *station;

        // assigning the next station
        auto station1 = std::find_if(stations.begin(), stations.end(),
                                     [&](Workstation *workObj) {
                                       return workObj->getItemName() == temp2;
                                     });

        if (station1 != stations.end())
          next = *station1;

        // pushing the stations inside the vector
        current->setNextStation(next);
        this->m_activeLine.push_back(current);
      }

      // finding the first Workstation
      this->m_firstStation = *std::find_if(
          this->m_activeLine.begin(), this->m_activeLine.end(),
          [this](const Workstation *obj) {
            return none_of(this->m_activeLine.begin(), this->m_activeLine.end(),
                           [&](Workstation *nextObj) {
                             if (nextObj->getNextStation() != nullptr) {
                               return obj == nextObj->getNextStation();
                             } else
                               return false;
                           });
          });
      this->m_cntCustomerOrder = g_pending.size();

      istr.close();
    }
  }
}

void LineManager::reorderStations() {
  std::vector<Workstation *> container{};
  Workstation *first = this->m_firstStation;

  // reordering Stations in the current variable
  while (first) {
    container.push_back(first);
    first = first->getNextStation();
  }

  // assigning reordered container
  this->m_activeLine = container;
}

bool LineManager::run(std::ostream &os) {
  //++count;
  static int counter = 1;
  os << "Line Manager Iteration: " << counter++ << endl;

  if (!g_pending.empty()) {
    *this->m_firstStation += std::move(g_pending.front());
    g_pending.pop_front();
  }

  // calling the fill function for all the activeline
  for (auto &obj : this->m_activeLine) {
    obj->fill(os);
  }

  // calling to move the order ahead
  for (auto &obj : this->m_activeLine) {
    obj->attemptToMoveOrder();
  }

  // return true or false but checking whether all customer orders are placed
  return this->m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
}

void LineManager::display(std::ostream &os) const {
  for (auto &obj : this->m_activeLine)
    obj->display(os);
}
} // namespace sdds
