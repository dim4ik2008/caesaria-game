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

#ifndef __CAESARIA_CITYSERVICE_H_INCLUDED__
#define __CAESARIA_CITYSERVICE_H_INCLUDED__

#include "core/referencecounted.hpp"
#include "core/smartptr.hpp"
#include "core/variant.hpp"

class CityService : public ReferenceCounted
{
public:
  virtual void update( const unsigned int time ) = 0;

  virtual std::string getName() const { return _name; }
  virtual bool isDeleted() const { return false; }
  
  virtual void destroy() {}

  virtual VariantMap save() const { return VariantMap(); }
  virtual void load(const VariantMap& stream) {}

protected:
  CityService( const std::string& name ) : _name( name )
  {
  }

protected:
  std::string _name;
};

typedef SmartPtr<CityService> CityServicePtr;

#endif//__CAESARIA_CITYSERVICE_H_INCLUDED__