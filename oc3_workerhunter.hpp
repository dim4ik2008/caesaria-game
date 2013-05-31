// This file is part of openCaesar3.
//
// openCaesar3 is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// openCaesar3 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with openCaesar3.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __OPENCAESAR3_WORKERSHUNTER_H_INCLUDE_
#define __OPENCAESAR3_WORKERSHUNTER_H_INCLUDE_

#include "oc3_servicewalker.hpp"

class WorkersHunter;
typedef SmartPtr<WorkersHunter> WorkersHunterPtr;

class WorkersHunter : public ServiceWalker
{
public:
  static WorkersHunterPtr create( City& city );

  int getWorkersNeeded() const;
  void onNewTile();
  void hireWorkers( const int workers );

  void send2City( WorkingBuildingPtr building, const int workersNeeded );

private:
  WorkersHunter( City& city );

  int _workersNeeded;
};

#endif//__OPENCAESAR3_WORKERSHUNTER_H_INCLUDE_