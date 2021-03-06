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
// Copyright 2012-2013 Gregoire Athanase, gathanase@gmail.com
// Copyright 2012-2014 Dalerank, dalerankn8@gmail.com

#ifndef _CAESARIA_TIMBER_LOGGER_H_INCLUDE_
#define _CAESARIA_TIMBER_LOGGER_H_INCLUDE_

#include "factory.hpp"

class TimberLogger : public Factory
{
public:
  TimberLogger();

  virtual math::Percent productivity();
  virtual void timeStep(const unsigned long time);
  virtual std::string errorDesc() const;
  virtual bool canBuild(const city::AreaInfo& areaInfo) const;  // returns true if it can be built there

  virtual void load(const VariantMap &stream);
  virtual void save(VariantMap &stream) const;

protected:
  virtual void _productReady();

private:
  void _checkDistance2forest();
  const gfx::Tile& _findNearestForest(const city::AreaInfo& areaInfo) const;

  class Impl;
  ScopedPtr<Impl> _d;
};

#endif //_CAESARIA_TIMBER_LOGGER_H_INCLUDE_
