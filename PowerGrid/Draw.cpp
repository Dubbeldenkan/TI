#include "Draw.h"

Draw::Draw(HWND* hWnd, Board* board)
{
	_g = new Graphics(*hWnd);
	board->SetMapImage(_g->LoadImage(board->GetMapName()));
	_cityLabel = _g->LoadImage("CityLabel.png");

	//load player images
	_playerLabelRed = _g->LoadImage("PlayerLabelRed.png");
	_playerLabelBlue = _g->LoadImage("PlayerLabelBlue.png");
	_playerLabelGreen = _g->LoadImage("PlayerLabelGreen.png");
	_playerLabelYellow = _g->LoadImage("PlayerLabelYellow.png");
	_playerLabelBlack = _g->LoadImage("PlayerLabelBlack.png");
	_playerLabelPurple = _g->LoadImage("PlayerLabelPurple.png");
	_redButton = _g->LoadImage("RedButton.png");

	//Load power plant images
	_powerPlantCoalImage = _g->LoadImage("PowerPlantCoalImage.png");
	_powerPlantOilImage = _g->LoadImage("PowerPlantOilImage.png");
	_powerPlantCoalOilImage = _g->LoadImage("PowerPlantCoalOilImage.png");
	_powerPlantGarbageImage = _g->LoadImage("PowerPlantGarbageImage.png");
	_powerPlantUranImage = _g->LoadImage("PowerPlantUranImage.png");
	_powerPlantEcoImage = _g->LoadImage("PowerPlantEcoImage.png");
}

Draw::Pos Draw::GetFirstCurrentPlantPos()
{
	return _firstCurrentPlantPos;
}

Draw::Pos Draw::GetSizeOfPowerPlant()
{
	//TODO kanske göra denna uträkning lite snyggare
	Pos pos = Pos(_powerPlantCoalImage.GetxSize(), _powerPlantCoalImage.GetYSize());
	return pos;
}

Draw::Pos Draw::GetPlantDiff()
{
	return _plantDiff;
}

Draw::Pos Draw::GetPassButtonPos()
{
	return _passButtonPos;
}

Draw::Pos Draw::GetIncreaseBidButtonPos()
{
	return _increaseButtonPos;
}

Draw::Pos Draw::GetDecreaseBidButtonPos()
{
	return _decreaseButtonPos;
}

Draw::Pos Draw::GetBidButtonPos()
{
	return _continueButtonPos;
}

Draw::Pos Draw::GetFirstPlayerPos()
{
	return _firstPlayerPos;
}

Draw::Pos Draw::GetPlayerDiff()
{
	return _playerPosDiff;
}

Draw::Pos Draw::GetFirstPlayerPowerPlantPos()
{
	return _firstPlayerPowerPlantPos;
}

Draw::Pos Draw::GetPlayerPowerPlantDiff()
{
	return _playerPowerPlantDiff;
}

void Draw::DrawWholeBoard(DrawInput* dI)
{
	_g->Clear();
	_g->StartDrawing();
	DrawBoard(dI->_board);
	for (int i = 0; i < dI->_playerVector.size(); i++)
	{
		DrawPlayer(dI->_playerVector[i], i);
	}
	PrintPlayerInTurn(dI->_playerInTurn);
	DrawPowerPlantMarket(dI->_powerPlantMarket);
	if (dI->_gamePhase == 2 || dI->_gamePhase == 3 || dI->_gamePhase == 4)
	{
		DrawButton(&_redButton, "Pass", _passButtonPos);
	}
	if (dI->_selectedPowerPlant > -1 && !dI->_placePowerPlant)
	{
		PrintPlantForSale(dI->_powerPlantMarket->GetPowerPlantCurrentDeck(dI->_selectedPowerPlant),
			dI->_currentPowerPlantBiddingPrice, dI->_lastBiddingPlayer->GetName());
		DrawBidButtons(dI->_nextBid);
	}
	else if (dI->_placePowerPlant)
	{
		PrintPlacePowerPlant();
	}
	DrawResourceMarket(dI->_resourceMarket);
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
	_g->PrintText(city->GetName(), city->GetXPos() + cityNamePos.x, 
		city->GetYPos() + cityNamePos.y, Graphics::WHITE);
}

void Draw::DrawPlayer(Player* player, int playerIndex)
{
	int FontSize = 15;
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
	_g->Draw(tempPlayerLabel, _firstPlayerPos.x, _firstPlayerPos.y + playerIndex * _playerPosDiff.y, 1);
	_g->PrintText(player->GetName(), _firstPlayerPos.x + nameDiff.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + nameDiff.y, Graphics::WHITE, 15);

	_g->PrintText(player->GetAmountOfCoal(), _firstPlayerPos.x + firstRes.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + firstRes.y, Graphics::WHITE, 15);
	_g->PrintText(player->GetAmountOfOil(), _firstPlayerPos.x + firstRes.x + resDiff.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + firstRes.y, Graphics::WHITE, 15);
	_g->PrintText(player->GetAmountOfGarbage(), _firstPlayerPos.x + firstRes.x + 2*resDiff.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + firstRes.y, Graphics::BLACK, 15);
	_g->PrintText(player->GetAmountOfGarbage(), _firstPlayerPos.x + firstRes.x + 3 * resDiff.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + firstRes.y, Graphics::WHITE, 15);

	_g->PrintText(player->GetAmountOfElektro(), _firstPlayerPos.x + elektroPos.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + elektroPos.y, Graphics::BLACK, 15);

	_g->PrintText(player->GetNumberOfSuppliedCities(), _firstPlayerPos.x + suppliedcitiesPos.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + suppliedcitiesPos.y, Graphics::BLACK, 13);
	_g->PrintText("+", _firstPlayerPos.x + plusPos.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + plusPos.y, Graphics::BLACK, 13);
	_g->PrintText(player->GetNumberOfCitiesInNetwork(), _firstPlayerPos.x + citiesInNetworkPos.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + citiesInNetworkPos.y, Graphics::BLACK, 13);
	for (int index = 0; index < player->numberOfPowerPlants; index++)
	{
		DrawPowerPlant(player->GetPowerPlant(index),
			_firstPlayerPos.x + _firstPlayerPowerPlantPos.x + _playerPowerPlantDiff.x*index,
			_firstPlayerPos.y + _firstPlayerPowerPlantPos.y + _playerPosDiff.y*playerIndex);
	}
}

void Draw::PrintPlayerInTurn(Player* player)
{
	std::string str = "Nuvarande spelare är ";
	std::string strName(player->GetName());
	str = str + strName;
	_g->PrintText((char*) str.c_str(), _playerInTurnPos.x, _playerInTurnPos.y, Graphics::WHITE, 15);
}

void Draw::PrintPlantForSale(PowerPlant* powerPlant, int bidingPrice, char* playerName)
{
	std::string str = "Verk nr ";
	std::string strNumber = std::to_string(powerPlant->GetPowerPlantNumber());
	str = str + strNumber;
	str = str + " för ";
	strNumber = std::to_string(bidingPrice);
	str = str + strNumber;
	str = str + " elek till ";
	str = str + std::string(playerName);
	_g->PrintText((char*)str.c_str(), _infoTextPos.x, _infoTextPos.y, Graphics::WHITE, 15);
}

void Draw::PrintPlacePowerPlant()
{
	_g->PrintText("Välj position för verket.", _infoTextPos.x, _infoTextPos.y, Graphics::WHITE,	15);
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
		Pos plantTextPos = Pos(0, 18);
		_g->Draw(tempImage, xPos, yPos, 1);
		_g->PrintText(powerPlant->GetPowerPlantNumber(), xPos, yPos, Graphics::BLACK, 15);
		std::string str;
		str = std::to_string(powerPlant->GetPowerPlantConsumption());
		str += "->" + std::to_string(powerPlant->GetPowerPlantProduction());
		const char* buffer = str.c_str();

		_g->PrintText((char*)buffer, xPos + plantTextPos.x, yPos + plantTextPos.y, Graphics::BLACK, 8);
	}
}

void Draw::DrawPowerPlantMarket(PowerPlantMarket* ppm)
{
	//current market
	for (int index = 0; index < ppm->GetNumberInCurrentMarket(); index++)
	{
		int xDiff = (index % 2)*_plantDiff.x;
		int yDiff = (index / 2)*_plantDiff.y;
		DrawPowerPlant(ppm->GetPowerPlantCurrentDeck(index), _firstCurrentPlantPos.x + xDiff,
			_firstCurrentPlantPos.y + yDiff);
		DrawPowerPlant(ppm->GetPowerPlantFutureDeck(index), _firstFuturePlantPos.x + xDiff,
			_firstFuturePlantPos.y + yDiff);
	}
}

void Draw::DrawBidButtons(int nextBid)
{
	DrawButton(&_redButton, "Bjud", _continueButtonPos);
	DrawButton(&_redButton, "Öka", _increaseButtonPos);
	DrawButton(&_redButton, "Minska", _decreaseButtonPos);
	_g->PrintText(nextBid, _nextBidPos.x, _nextBidPos.y, Graphics::WHITE, 15);
}

void Draw::DrawButton(Image* image, char* text, Pos pos)
{
	Pos textDiff = Pos(2, 10);
	_g->Draw(image, pos.x, pos.y, 1);
	_g->PrintText(text, pos.x + textDiff.x, pos.y + textDiff.x, Graphics::BLACK, 15);
}

void Draw::DrawResourceMarket(ResourceMarket* rm)
{
	//TODO
}