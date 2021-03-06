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

#ifndef _CAESARIA_CONTEXMENUITEM_INCLUDE_H_
#define _CAESARIA_CONTEXMENUITEM_INCLUDE_H_

#include "label.hpp"
#include "core/scopedptr.hpp"

namespace gui
{

class ContextMenu;

class ContextMenuItem : public Label
{
public:
  typedef enum { hoverIndex=3 } OpacityIndex;
  typedef enum { alignRigth=0x1, alignLeft=0x2, alignHorizCenter=0x4,
    alignTop=0x10, alignBottom=0x20, alignVertCenter=0x40,
    alignAuto=0xff } SubMenuAlign;

  typedef enum
  {
    drawSubmenuSprite = 0,
    drawCount
  } DrawFlag;

  ContextMenuItem(Widget* parent, const std::string& text);

  virtual ~ContextMenuItem();

  virtual bool isSeparator() const;

  virtual void setCommandId( int cmdId);

  virtual int commandId() const;

  virtual ContextMenu* submenu() const;

  virtual void setIsSeparator(bool separator);

  virtual void toggleCheck();

  virtual void draw(gfx::Engine &painter);

  virtual void setFlag(DrawFlag flagName, bool set=true);

  virtual void setIcon(const gfx::Picture& icon,const Point& offset);

  virtual bool isHovered() const;

  virtual void setHovered(bool hover);

  //!
  virtual bool isAutoChecking();

  //!
  virtual void setAutoChecking(bool autoChecking);

  virtual bool isPointInside(const Point& point) const;

  virtual void setChecked(bool check);

  virtual bool isChecked() const;

  virtual int offset() const;

  virtual void setOffset(int offset);

  virtual void setDimmension(const Size& size);

  virtual const Size& dimmension() const;

  //! Adds a sub menu from an element that already exists.
  virtual void setSubmenu(ContextMenu* menu);

  virtual ContextMenu* addSubmenu(int id = -1);

  virtual ContextMenuItem* addSubmenuItem(const std::string& text);

  virtual void setSubmenuAlignment(SubMenuAlign align);

  virtual SubMenuAlign subMenuAlignment() const;

  void setSubmenuIconVisible(bool visible);

  void moveToIndex(int index);

  void setStateFont(ElementState state, Font f);

  virtual void setVisible(bool visible);

signals public:
  Signal1<bool>& onChecked();
  Signal2<Widget*,bool>& onCheckedEx();
  Signal1<int>& onAction();

protected:
  virtual void _updateTexture(gfx::Engine& painter);

private:
  __DECLARE_IMPL(ContextMenuItem)
};

}//end namespace gui
#endif //_CAESARIA_CONTEXMENUITEM_INCLUDE_H_
