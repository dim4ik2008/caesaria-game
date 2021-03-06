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

#ifndef _CAESARIA_CHASTENER_ELEPHANT_INCLUDE_H_
#define _CAESARIA_CHASTENER_ELEPHANT_INCLUDE_H_

#include "enemysoldier.hpp"
#include "predefinitions.hpp"

class ChastenerElephant : public EnemySoldier
{
  WALKER_MUST_INITIALIZE_FROM_FACTORY
public:
  virtual int agressive() const;
  virtual bool die();

protected:
  Pathway _findPathway2NearestConstruction( unsigned int range );
  bool _tryAttack();

  ChastenerElephant( PlayerCityPtr city );
};

#endif //_CAESARIA_CHASTENER_ELEPHANT_INCLUDE_H_
