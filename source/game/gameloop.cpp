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
// Copyright 2012-2014 dalerank, dalerankn8@gmail.com

#include "gameloop.hpp"
#include "config.hpp"
#include "core/direction.hpp"
#include "core/logger.hpp"
#include "gfx/tilemap.hpp"
#include "world/empire.hpp"
#include "gamedate.hpp"
#include "scene/level.hpp"
#include "events/dispatcher.hpp"
#include "freeplay_finalizer.hpp"

using namespace scene;

namespace gamestate
{

class InGame::Impl
{
public:
  scene::Level* level;
  Simulation*   simulation;
  struct {
    std::string*  next;
    std::string*  restart;
  } filename;
};

InGame::InGame( Game* game, gfx::Engine* engine,
                Simulation& simulation,
                std::string& nextFilename,
                std::string& restartFilename) :
  State(game), __INIT_IMPL(InGame)
{
  __D_REF(d,InGame)
  d.level = new scene::Level( *game, *engine );
  d.simulation = &simulation;
  d.filename.next = &nextFilename;
  d.filename.restart = &restartFilename;

  _initialize( d.level, SCREEN_GAME);

  Logger::debug( "game: prepare for game loop" );
}

bool InGame::update(gfx::Engine* engine)
{
  __D_REF(d,InGame)
  if (_screen->isStopped())
  {
    return false;
  }

  _screen->update( *engine );
  Simulation& sim = *d.simulation;

  bool simulationAvailable = _game->city()->tilemap().direction() == direction::north;
  if( sim.time.manualTicksCounterX10 > 0 )
  {
    simulationAvailable = true;
  }

  if( simulationAvailable )
  {
    if( !_game->isPaused() )
    {
      sim.time.ticksX10 += sim.time.multiplier / config::gamespeed::scale;
    }
    else if ( sim.time.manualTicksCounterX10 > 0 )
    {
      unsigned int delta = math::min( sim.time.multiplier / config::gamespeed::scale, sim.time.manualTicksCounterX10 );
      sim.time.ticksX10 += delta;
      sim.time.manualTicksCounterX10 -= delta;
    }

    game::Date& cdate = game::Date::instance();
    while( sim.time.ticksX10 > sim.time.current * config::gamespeed::scale + 1 )
    {
      sim.time.current++;

      cdate.timeStep( sim.time.current );
      _game->empire()->timeStep( sim.time.current );

      d.level->animate( sim.time.current );
    }
  }

  events::Dispatcher::instance().update( *_game, sim.time.current );
  return true;
}

InGame::~InGame()
{
  __D_REF(d,InGame)
  _game->clear();

  if( d.filename.next )
    *d.filename.next = d.level->nextFilename();

  switch( _screen->result() )
  {
  case Level::res_menu: _game->setNextScreen( SCREEN_MENU );  break;
  case Level::res_load: _game->setNextScreen( SCREEN_GAME );  _game->load( d.level->nextFilename() ); break;

  case Level::res_restart:
  {
    Logger::debug( "ScreenGame: restart game " + *d.filename.restart );
    bool loadOk = _game->load( *d.filename.restart );
    _game->setNextScreen( loadOk ? SCREEN_GAME : SCREEN_MENU );

    Logger::debug( (loadOk ? "ScreenGame: end loading file " : "ScreenGame: cant load file " ) + *d.filename.restart );

    if( loadOk )
    {
      std::string ext = vfs::Path( *d.filename.restart ).extension();
      if( ext == ".map" || ext == ".sav" )
      {
        game::freeplay::Finalizer finalizer( _game->city() );
        finalizer.addPopulationMilestones();
        finalizer.initBuildOptions();
        finalizer.addEvents();
      }
    }
  }
  break;

  case Level::res_briefing: _game->setNextScreen( SCREEN_BRIEFING ); break;
  case Level::res_quit: _game->setNextScreen( SCREEN_QUIT );  break;
  default: _game->setNextScreen( SCREEN_QUIT ); break;
  }
}

}//end namespace gamestate
