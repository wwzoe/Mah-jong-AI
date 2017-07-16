/*
  tilemap.h

  defines a class to record state of tiles.
*/

#ifndef TILEMAP_H
#define TILEMAP_H

#include "tile.h"

// Indicates the state of tiles we know from the game.
typedef enum {
  InMyhand,
  InMyDiscardedTiles,
  InPlayer2DiscardedTiles,
  InPlayer3DiscardedTiles,
  InPlayer4DiscardedTiles,
  InMySuite,
  InPlayer2Suite,
  InPlayer3Suite,
  InPlayer4Suite,
  Unknown
} TileState;

//  A statemap to show state of all tiles
//  Kinds of tiles are tracked here are
//  Dots, Bamboo, Characters, Winds, Dragons.
//  Seasons and Flowers are not included. therefore,
//  172 tiles are tracked.
typedef struct {
  TileState tile_states[172];
} TileMap;

Tile discard(TileMap *current_tile_map, TileMap *target_tile_map);
TileMap player_discard(TileMap *current_tile_map, int id, Tile discarded);
TileMap player_chow(TileMap *current_tile_map, int id, Tile tile, ChowPosition cpos);
TileMap player_pung(TileMap *current_tile_map, int id, Tile tile);
TileMap player_kong(TileMap *current_tile_map, int id, Tile tile);


#endif
