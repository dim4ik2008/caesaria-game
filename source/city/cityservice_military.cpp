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

#include "cityservice_military.hpp"
#include "city.hpp"
#include "game/gamedate.hpp"
#include "walker/enemysoldier.hpp"
#include "core/utils.hpp"
#include "city/cityservice_info.hpp"
#include "world/playerarmy.hpp"
#include "world/empire.hpp"
#include "objects/fort.hpp"
#include "core/variant_map.hpp"
#include "core/flagholder.hpp"
#include "statistic.hpp"
#include "cityservice_factory.hpp"

namespace city
{

static const int notificationHistoryMonths = 3 * DateTime::monthsInYear;
static const int enemySoldiertThreat = 10;
REGISTER_SERVICE_IN_FACTORY(Military,military)

class Military::Impl
{
public:
  Notifications notifications;
  DateTime lastEnemyAttack;
  float threatValue;
  bool needUpdateMilitaryThreat;
};

Military::Military( PlayerCityPtr city )
  : Srvc( city, defaultName() ), _d( new Impl )
{
  _d->needUpdateMilitaryThreat = true;
  _d->threatValue = 0;
}

void Military::timeStep(const unsigned int time )
{
  if( game::Date::isMonthChanged() )
  {
    DateTime curDate = game::Date::current();
    //clear old notificationse
    _d->notifications.eraseOld( curDate, notificationHistoryMonths );
  }

  if( game::Date::isWeekChanged() )
  {
    world::EmpirePtr empire = _city()->empire();

    for( Notifications::iterator it=_d->notifications.begin(); it != _d->notifications.end(); )
    {
      world::ObjectPtr object = empire->findObject( it->desc.objectName );

      if( object.isValid() ) { ++it; }
      else { it = _d->notifications.erase( it ); }
    }
  }

  if( _d->needUpdateMilitaryThreat || game::Date::isMonthChanged() )
  {
    _d->needUpdateMilitaryThreat = false;

    int enemiesInCity_n = _city()->walkers().count<EnemySoldier>();

    _d->threatValue = (float)(enemiesInCity_n * enemySoldiertThreat);
  }  
}

void Military::addNotification(const notification::Describe& describe )
{
  Notification n;
  n.date = game::Date::current();
  n.desc = describe;

  _d->notifications.push_back( n );
}

Notification Military::priorityNotification() const
{
  return Notification();
}

const Notifications& Military::notifications() const
{
  return _d->notifications;
}

bool Military::haveNotification( notification::Type type) const
{
  return _d->notifications.contain( type );
}

bool Military::isUnderAttack() const
{
  return haveNotification( notification::barbarian )
      || haveNotification( notification::chastener );
}

VariantMap Military::save() const
{
  VariantMap ret;

  VariantMap notifications;
  int index = 0;
  for( auto& notification : _d->notifications )
  {
    notifications[ utils::format( 0xff, "note_%03d", index ) ] = notification.save();
  }

  VARIANT_SAVE_ANY( ret, notifications );
  VARIANT_SAVE_ANY_D( ret, _d, lastEnemyAttack )

  return ret;
}

void Military::load(const VariantMap& stream)
{
  VariantMap notifications;
  VARIANT_LOAD_TIME_D( _d, lastEnemyAttack, stream );
  VARIANT_LOAD_VMAP( notifications, stream );

  for( auto& notification : notifications )
    _d->notifications.push_back( notification::create( notification.second.toList()) );
}

const DateTime& Military::lastAttack() const { return _d->lastEnemyAttack; }

void Military::updateThreat(int value)
{
  _d->needUpdateMilitaryThreat = true;

  if( value > 0 )
    _d->lastEnemyAttack = game::Date::current();
}

int Military::monthFromLastAttack() const{ return _d->lastEnemyAttack.monthsTo( game::Date::current()); }

world::PlayerArmyList Military::expeditions() const
{
  FortList forts = _city()->statistic().objects.find<Fort>( object::group::military );

  world::PlayerArmyList ret;
  for( auto fort : forts )
  {
    world::PlayerArmyPtr army = fort->expedition();
    if( army.isValid() )
    {
      ret.push_back( army );
    }
  }

  return ret;
}

world::ObjectList Military::enemies() const
{
  world::ObjectList ret;

  return ret;
}

int Military::value() const{ return (int)_d->threatValue; }
std::string Military::defaultName(){  return TEXT(Military); }

}//end namespace city
