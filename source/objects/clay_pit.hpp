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
// Copyright 2012-2015 Dalerank, dalerankn8@gmail.com

#ifndef __CAESARIA_CLAY_PIT_H_INCLUDED__
#define __CAESARIA_CLAY_PIT_H_INCLUDED__

#include "factory.hpp"
#include "ruins.hpp"

class ClayPit : public Factory
{
public:
  ClayPit();
  
  virtual bool build(const city::AreaInfo &info);
  virtual bool canBuild(const city::AreaInfo& areaInfo) const;  // returns true if it can be built there
  virtual void timeStep( const unsigned long time );

  virtual void flood();

protected:
  virtual void _reachUnworkingTreshold();
};

class FloodedClayPit : public Ruins
{
public:
  FloodedClayPit();
};

#endif //__CAESARIA_CLAY_PIT_H_INCLUDED__
