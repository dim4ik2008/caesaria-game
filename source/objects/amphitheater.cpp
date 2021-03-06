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

#include "amphitheater.hpp"
#include "core/position.hpp"
#include "game/resourcegroup.hpp"
#include "city/statistic.hpp"
#include "core/variant_map.hpp"
#include "training.hpp"
#include "core/utils.hpp"
#include "core/logger.hpp"
#include "game/gamedate.hpp"
#include "walker/serviceman.hpp"
#include "constants.hpp"
#include "actor_colony.hpp"
#include "walker/helper.hpp"
#include "core/common.hpp"
#include "objects_factory.hpp"

using namespace gfx;

REGISTER_CLASS_IN_OVERLAYFACTORY(object::amphitheater, Amphitheater)

class Amphitheater::Impl
{
public:
  struct
  {
    DateTime glads;
    DateTime arts;
  } lastshow;
};

Amphitheater::Amphitheater()
  : EntertainmentBuilding(Service::amphitheater, object::amphitheater, Size(3,3)), _d( new Impl )
{
  _fgPictures().resize(2);

  _addNecessaryWalker( walker::actor );
  _addNecessaryWalker( walker::gladiator );
}

void Amphitheater::timeStep(const unsigned long time)
{
  EntertainmentBuilding::timeStep( time );
}

Service::Type Amphitheater::serviceType() const
{
  int gldValue = traineeValue( walker::gladiator );
  return gldValue > 0 ? Service::amphitheater : Service::theater;
}

std::string Amphitheater::workersStateDesc() const
{
  if( numberWorkers() > 0 )
  {
    if( showsCount() == 0 ) { return "##amphitheater_have_never_show##"; }
    if( traineeValue( walker::gladiator ) == 0 ) { return "##amphitheater_have_only_shows##"; }
    if( traineeValue( walker::actor ) == 0 ) { return "##amphitheater_have_only_battles##"; }
  }

  return EntertainmentBuilding::workersStateDesc();
}

bool Amphitheater::build( const city::AreaInfo& info)
{
  EntertainmentBuilding::build( info );

  ActorColonyList actors = info.city->statistic().objects.find<ActorColony>( object::actorColony );
  if( actors.empty() )
  {
    _setError( "##need_actor_colony##" );
  }

  GladiatorSchoolList gladiators = info.city->statistic().objects.find<GladiatorSchool>( object::gladiatorSchool );
  if( gladiators.empty() )
  {
    _setError( "##colosseum_haveno_gladiatorpit##" );
  }

  return true;
}

void Amphitheater::deliverService()
{
  int saveWalkesNumber = walkers().size();
  Service::Type lastSrvc = serviceType();

  EntertainmentBuilding::deliverService();

  if( _animation().isRunning())
  {
    _fgPictures().front().load( ResourceGroup::entertainment, 12 );
    int currentWalkerNumber = walkers().size();
    if( saveWalkesNumber != currentWalkerNumber )
    {
      (lastSrvc == Service::colosseum
        ? _d->lastshow.glads : _d->lastshow.arts ) = game::Date::current();
    }
  }
  else
  {
    _fgPictures().front() = Picture::getInvalid();
    _fgPictures().back() = Picture::getInvalid();
  }
}

void Amphitheater::save(VariantMap& stream) const
{
  EntertainmentBuilding::save( stream );
  VARIANT_SAVE_ANY_D( stream, _d, lastshow.glads )
  VARIANT_SAVE_ANY_D( stream, _d, lastshow.arts )
}

void Amphitheater::load(const VariantMap& stream)
{
  EntertainmentBuilding::load( stream );
  VARIANT_LOAD_TIME_D( _d, lastshow.glads, stream )
  VARIANT_LOAD_TIME_D( _d, lastshow.arts, stream )
}

int Amphitheater::maxVisitors() const { return 800; }

Variant Amphitheater::getProperty(const std::string & name) const
{
  if (name == "needGladiators") return isNeed(walker::gladiator);
  if (name == "showTheatrical") return isShow(Amphitheater::theatrical);
  if (name == "showGladiatorBouts") return isShow(Amphitheater::gladiatorBouts);
  if (name == "lastShowTheatrical") return lastShow(Amphitheater::theatrical);
  if (name == "lastShowGladiatorBouts") return lastShow(Amphitheater::gladiatorBouts);

  return EntertainmentBuilding::getProperty(name);
}

bool Amphitheater::isShow(Amphitheater::PlayType type) const
{
  switch( type )
  {
  case theatrical: return _getServiceManType() == Service::theater;
  case gladiatorBouts: return _getServiceManType() == Service::amphitheater;
  }

  return false;
}

DateTime Amphitheater::lastShow(Amphitheater::PlayType type) const
{
  switch( type )
  {
  case theatrical: return _d->lastshow.arts;
  case gladiatorBouts: return  _d->lastshow.glads;
  }

  return DateTime( -350, 1, 1 );
}

Service::Type Amphitheater::_getServiceManType() const
{
  ServiceWalkerList servicemen = walkers().select<ServiceWalker>();
  return (!servicemen.empty()
                ? servicemen.front()->serviceType()
                : Service::srvCount);
}

bool Amphitheater::isNeed(walker::Type type) const
{
  switch( type )
  {
  case walker::gladiator:
  case walker::actor:
    return traineeValue( type ) == 0;

  default: break;
  }

  return false;
}

WalkerList Amphitheater::_specificWorkers() const
{
  WalkerList ret = walkers();
  utils::excludeByType( ret, WalkerTypeSet( walker::actor, walker::gladiator ) );

  return ret;
}
