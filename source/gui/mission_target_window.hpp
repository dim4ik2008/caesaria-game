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

#ifndef __CAESARIA_MISSION_TARGETS_WINDOW_H_INCLUDED__
#define __CAESARIA_MISSION_TARGETS_WINDOW_H_INCLUDED__

#include "core/scopedptr.hpp"
#include "game/predefinitions.hpp"
#include "widget.hpp"

namespace gui
{

class MissionTargetsWindow : public Widget  
{
public:
  static MissionTargetsWindow* create( Widget* parent, PlayerCityPtr city , int id=-1 );
  ~MissionTargetsWindow();

  void draw( GfxEngine& painter );
  void setCity( PlayerCityPtr city );

private:
  MissionTargetsWindow( Widget* parent, int id, const Rect& rectangle );

  class Impl;
  ScopedPtr< Impl > _d;
};

}//end namespace gui
#endif //__CAESARIA_MISSION_TARGETS_WINDOW_H_INCLUDED__
