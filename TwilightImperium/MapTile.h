#ifndef MAP_TILE_H
#define MAP_TILE_H

#include "GameBoardObject.h"
#include "UtilityClasses.h"
#include "Planet.h"

class MapTile : public GameBoardObject
{
public:
	enum TileType {RegularSystem, HomeSystem, AstroidSystem, NebulaSystem, SupernovaSystem};
	   
private:
	static const TupleInt _tileSize;
	TupleInt _tilePos;
	TileType _tileType;
	std::vector<Planet> _planets;
	static const GameBoardObject::LayerEnum _layerValue;

public:
	MapTile();
	MapTile(TileType, std::string);
	
	MapTile& operator=(const MapTile&);
	MapTile(MapTile const&);
	~MapTile();

	static TupleInt GetTileSize();
	void SetTilePos(int, int);
	void AddPlanet(Planet*);
	void SetPlanetsPositions();

	const std::vector<Planet>* GetPlanets() const;
	const Planet* GetPlanet(int) const;
	TileType GetTileType() const;

	int CalculateDistanceToTile(MapTile*) const;

private:
	void CopyMapTile(const MapTile&);
};

#endif // !MAP_TILE_H