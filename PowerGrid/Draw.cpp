#include "Draw.h"

Draw::Draw(HWND hWnd, Board* board)
{
	_g = new Graphics(hWnd);
	board->SetMapImage(_g->LoadImage(board->GetMapName()));
	_cityLabel = _g->LoadImage("CityLabel.png");

	//load player images
	_playerLabelRed = _g->LoadImage("PlayerLabelRed.png");
	_playerLabelBlue = _g->LoadImage("PlayerLabelBlue.png");
	_playerLabelGreen = _g->LoadImage("PlayerLabelGreen.png");
	_playerLabelYellow = _g->LoadImage("PlayerLabelYellow.png");
	_playerLabelBlack = _g->LoadImage("PlayerLabelBlack.png");
	_playerLabelPurple = _g->LoadImage("PlayerLabelPurple.png");

	//Load power plant images
	_powerPlantCoalImage = _g->LoadImage("PowerPlantCoalImage.png");
	_powerPlantOilImage = _g->LoadImage("PowerPlantOilImage.png");
	_powerPlantCoalOilImage = _g->LoadImage("PowerPlantCoalOilImage.png");
	_powerPlantGarbageImage = _g->LoadImage("PowerPlantGarbageImage.png");
	_powerPlantUranImage = _g->LoadImage("PowerPlantUranImage.png");
	_powerPlantEcoImage = _g->LoadImage("PowerPlantEcoImage.png");
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
	Pos cityNamePos = Pos(1, 18);
	_g->Draw(&_cityLabel, city->GetXPos(), city->GetYPos(), 1);
	//TODO:: gör något snyggare sätt att lägga in + 13
	_g->PrintText(city->GetName(), city->GetXPos() + cityNamePos.x, 
		city->GetYPos() + cityNamePos.y, Graphics::WHITE);

}

void Draw::DrawPlayer(Player* player, int playerIndex)
{
	int FontSize = 15;
	Pos playerDiff = Pos(0, 65);
	Pos powerPlantDiff = Pos(20, 0);
	Pos nameDiff = Pos(6, 6);
	Pos firstRes = Pos(140, 6);
	Pos resDiff = Pos(30, 0);
	Pos elektroPos = Pos(220, 25);
	Pos suppliedcitiesPos = Pos(210, 45);
	Pos plusPos = Pos(225, 45);
	Pos citiesInNetworkPos = Pos(235, 45);
	Image* tempPlayerLabel;
	switch (player->GetColor())
	{
	case Player::red:
		tempPlayerLabel = &_playerLabelRed;
		break;
	case Player::blue:
		tempPlayerLabel = &_playerLabelBlue;
		break;
	case Player::green:
		tempPlayerLabel = &_playerLabelGreen;
		break;
	case Player::yellow:
		tempPlayerLabel = &_playerLabelYellow;
		break;
	case Player::black:
		tempPlayerLabel = &_playerLabelBlack;
		break;
	case Player::purple:
		tempPlayerLabel = &_playerLabelPurple;
		break;
	default:
		tempPlayerLabel = &_playerLabelBlack;
		break;
	}
	_g->Draw(tempPlayerLabel, _firstPlayerPos.x, _firstPlayerPos.y + playerIndex * playerDiff.y, 1);
	_g->PrintText(player->GetName(), _firstPlayerPos.x + nameDiff.x,
		_firstPlayerPos.y + playerIndex * playerDiff.y + nameDiff.y, Graphics::WHITE, 15);

	_g->PrintText(player->GetAmountOfCoal(), _firstPlayerPos.x + firstRes.x,
		_firstPlayerPos.y + playerIndex * playerDiff.y + firstRes.y, Graphics::WHITE, 15);
	_g->PrintText(player->GetAmountOfOil(), _firstPlayerPos.x + firstRes.x + resDiff.x,
		_firstPlayerPos.y + playerIndex * playerDiff.y + firstRes.y, Graphics::WHITE, 15);
	_g->PrintText(player->GetAmountOfGarbage(), _firstPlayerPos.x + firstRes.x + 2*resDiff.x,
		_firstPlayerPos.y + playerIndex * playerDiff.y + firstRes.y, Graphics::BLACK, 15);
	_g->PrintText(player->GetAmountOfGarbage(), _firstPlayerPos.x + firstRes.x + 3 * resDiff.x,
		_firstPlayerPos.y + playerIndex * playerDiff.y + firstRes.y, Graphics::WHITE, 15);

	_g->PrintText(player->GetAmountOfElektro(), _firstPlayerPos.x + elektroPos.x,
		_firstPlayerPos.y + playerIndex * playerDiff.y + elektroPos.y, Graphics::BLACK, 15);

	_g->PrintText(player->GetNumberOfSuppliedCities(), _firstPlayerPos.x + suppliedcitiesPos.x,
		_firstPlayerPos.y + playerIndex * playerDiff.y + suppliedcitiesPos.y, Graphics::BLACK, 13);
	_g->PrintText("+", _firstPlayerPos.x + plusPos.x,
		_firstPlayerPos.y + playerIndex * playerDiff.y + plusPos.y, Graphics::BLACK, 13);
	_g->PrintText(player->GetNumberOfCitiesInNetwork(), _firstPlayerPos.x + citiesInNetworkPos.x,
		_firstPlayerPos.y + playerIndex * playerDiff.y + citiesInNetworkPos.y, Graphics::BLACK, 13);
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
		Image* tempImage = &_powerPlantCoalImage;
		switch (powerPlant->GetType())
		{
		case PowerPlant::coal:
			tempImage = &_powerPlantCoalImage;
			break;
		case PowerPlant::coalOrOil:
			tempImage = &_powerPlantCoalOilImage;
			break;
		case PowerPlant::oil:
			tempImage = &_powerPlantOilImage;
			break;
		case PowerPlant::garbage:
			tempImage = &_powerPlantGarbageImage;
			break;
		}
		Pos plantTextPos = Pos(15, 10);
		_g->Draw(tempImage, xPos, yPos, 1);
		_g->PrintText(powerPlant->GetPowerPlantNumber(), xPos, yPos, Graphics::BLACK, 15);
		std::string str;
		str = std::to_string(powerPlant->GetPowerPlantConsumption());
		str += "->" + std::to_string(powerPlant->GetPowerPlantProduction());
		const char* buffer = str.c_str();

		_g->PrintText((char*)buffer, xPos + plantTextPos.x, yPos + plantTextPos.y, Graphics::RED, 15);
	}
}

void Draw::DrawPowerPlantMarket(PowerPlantMarket* ppm)
{
	//current market
	Pos firstCurrentPlantPos = Pos(600, 530);

	Pos firstFuturePlantPos = Pos(900, 530);
	Pos plantDiff = Pos(100, 50);
	for (int index = 0; index < ppm->GetNumberInCurrentMarket(); index++)
	{
		int xDiff = (index % 2)*plantDiff.x;
		int yDiff = (index / 2)*plantDiff.y;
		DrawPowerPlant(&ppm->GetPowerPlantCurrentDeck(index), firstCurrentPlantPos.x + xDiff,
			firstCurrentPlantPos.y + yDiff);
		DrawPowerPlant(&ppm->GetPowerPlantFutureDeck(index), firstFuturePlantPos.x + xDiff,
			firstFuturePlantPos.y + yDiff);
	}
}

void Draw::DrawResourceMarket(ResourceMarket* rm)
{
	//TODO
}