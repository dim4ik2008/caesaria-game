// This file is part of CaesarIA.
//
// CaesarIA is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CaesarIA is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CaesarIA.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright 2012-2014 Dalerank, dalerankn8@gmail.com

#ifndef _CAESARIA_BUILDING_EDUCATION_H_INCLUDE_
#define _CAESARIA_BUILDING_EDUCATION_H_INCLUDE_

#include "objects/service.hpp"

class School : public ServiceBuilding
{
public:
  School();

  int currentVisitors() const;

  virtual void deliverService();

  virtual unsigned int walkerDistance() const;
  virtual void buildingsServed(const std::set<BuildingPtr> &buildings, ServiceWalkerPtr walker);
protected:
  virtual int _getWalkerOrders() const;

private:
  class Impl;
  ScopedPtr<Impl> _d;
};

class Library : public ServiceBuilding
{
public:
   Library();

   int currentVisitors() const;
};

class Academy : public ServiceBuilding
{
public:
   Academy();

   int currentVisitors() const;
   virtual void deliverService();
   virtual std::string sound() const;
   virtual unsigned int walkerDistance() const;
};


#endif
