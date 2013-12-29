#ifndef __OPENCAESAR3_ASTARPOINT_H_INCLUDED__
#define __OPENCAESAR3_ASTARPOINT_H_INCLUDED__

#include "core/position.hpp"
#include "gfx/tile.hpp"

class AStarPoint
{

public:
  AStarPoint* parent;
  bool closed;
  bool opened;
  int f, g, h;
  const Tile* tile;

  AStarPoint()
  {
    parent = NULL;
    closed = false;
    opened = false;
    tile = 0;

    f = g = h = 0;
  }

  TilePos getPos()
  {
    return tile ? tile->getIJ() : TilePos( 0, 0 );
  }  

  AStarPoint( const Tile* t ) : tile( t )
  {    
    parent = NULL;
    closed = false;
    opened = false;

    f = g = h = 0;
  }

  AStarPoint* getParent()
  {
    return parent;
  }

  void setParent(AStarPoint* p)
  {
    parent = p;
  }

  int getGScore(AStarPoint* p, bool useRoad )
  { 
    int offset = (p->tile
                  ? (p->tile->getFlag( Tile::tlRoad ) ? 0 : +50)
                  : (+100) ) * ( useRoad ? 1 : 0 );
    TilePos pos = tile ? tile->getIJ() : TilePos( 0, 0 ); 
    TilePos otherPos = p->tile ? p->tile->getIJ() : getPos();
    return p->g + ((pos.getI() == otherPos.getI() || pos.getJ() == otherPos.getJ()) ? 10 : 14) + offset;
  }

  int getHScore(AStarPoint* p)
  {
    TilePos pos = tile ? tile->getIJ() : TilePos( 0, 0 ); 
    TilePos otherPos = p ? p->tile->getIJ() : TilePos( 0, 0 );
    return (abs(otherPos.getI() - pos.getI()) + abs(otherPos.getJ() - pos.getJ())) * 10;
  }

  int getGScore()
  {
    return g;
  }

  int getHScore()
  {
    return h;
  }

  int getFScore()
  {
    return f;
  }

  void computeScores(AStarPoint* end, bool useRoad )
  {
    g = getGScore(parent, useRoad );
    h = getHScore(end);
    f = g + h;
  }

  bool hasParent()
  {
    return parent != NULL;
  }
};

#endif //__OPENCAESAR3_ASTARPOINT_H_INCLUDED__