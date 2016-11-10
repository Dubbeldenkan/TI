#include "Draw.h"

Draw::Draw(HWND hWnd, Board* board)
{
	_g = new Graphics(hWnd);
	board->SetMapImage(_g->LoadImage(board->GetMapName()));
	_cityLabel = _g->LoadImage("CityLabel.png");
	_playerLabel = _g->LoadImage("PlayerLabel.png");
}

void Draw::DrawWholeBoard(Board* board, std::vector<Player*> players, 
	PowerPlantMarket* powerPlantMarket, ResourceMarket* resourceMarket)
{
	_g->StartDrawing();
	DrawBoard(board);
	for (int i = 0; i < players.size(); i++)
	{
		DrawPlayer(players[i], i);
	}
	DrawPowerPlantMarket(powerPlantMarket);
	DrawResourceMarket(resourceMarket);
	_g->StopDrawing();
	_g->Flip();
}

void Draw::DrawBoard(Board* board)
{
	_g->Draw(board->GetMapImage(), _mapPos.x, _mapPos.y, _mapPos.s);
	typedef std::map<char*, City*>::iterator it_type;
	for (it_type it = board->GetCityDictFirstIterator(); it != board->GetCityDictLastIterator(); it++)
	{
		DrawCity(it->second);
	}
}

void Draw::DrawCity(City* city)
{
	_g->Draw(&_cityLabel, city->GetXPos(), city->GetYPos(), 1);
	//TODO:: gör något snyggare sätt att lägga in + 13
	_g->PrintText(city->GetXPos() + 1, city->GetYPos() + 18, city->GetName(), Graphics::WHITE);

}

void Draw::DrawPlayer(Player* player, int playerIndex)
{
	//TODO rita ut så att man ser vilket ärg som tillhör vilken spelare.
	Pos playerDiff = Pos(0, 110);
	Pos powerPlantDiff = Pos(20, 0);
	Pos nameDiff = Pos(15, 30);
	_g->Draw(&_playerLabel, _firstPlayerPos.x, _firstPlayerPos.y + playerIndex * playerDiff.y, 1);
	_g->PrintText(_firstPlayerPos.x + nameDiff.x, _firstPlayerPos.y + playerIndex * playerDiff.y + nameDiff.y, 
		player->GetName(), Graphics::WHITE);
	for (int index = 0; index < player->numberOfPowerPlants; index++)
	{
		DrawPowerPlant(player->GetPowerPlant(index),
			_firstPlayerPos.x + _firstPlayerPowerPlantPos.x + powerPlantDiff.x*index,
			_firstPlayerPos.y + _firstPlayerPowerPlantPos.y + playerDiff.y*playerIndex);
	}
}

void Draw::DrawPowerPlant(PowerPlant* powerPlant, int xPos, int yPos)
{
	if (powerPlant->GetPowerPlantNumber() > 0)
	{
		int diff = 10;
		_g->PrintText(xPos, yPos, (char*)powerPlant->GetPowerPlantNumber(), Graphics::BLACK);
		std::string str;
		str = std::to_string(powerPlant->GetPowerPlantConsumption());
		str += "->" + std::to_string(powerPlant->GetPowerPlantProduction());
		const char* buffer = str.c_str();

		_g->PrintText(xPos, yPos + diff, (char*)buffer, Graphics::BLACK);
	}
}

void Draw::DrawPowerPlantMarket(PowerPlantMarket* ppm)
{
	//TODO
}

void Draw::DrawResourceMarket(ResourceMarket* rm)
{
	//TODO
}