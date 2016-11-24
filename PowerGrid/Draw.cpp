#include "Draw.h"

Draw::Draw(HWND* hWnd, Board* board)
{
	_g = new Graphics(*hWnd);
	board->SetMapImage(_g->LoadImage(board->GetMapName()));
	_cityLabel = _g->LoadImage("Map/CityLabel.png");

	//load player images
	_playerLabelRed = _g->LoadImage("Player/PlayerLabelRed.png");
	_playerLabelBlue = _g->LoadImage("Player/PlayerLabelBlue.png");
	_playerLabelGreen = _g->LoadImage("Player/PlayerLabelGreen.png");
	_playerLabelYellow = _g->LoadImage("Player/PlayerLabelYellow.png");
	_playerLabelBlack = _g->LoadImage("Player/PlayerLabelBlack.png");
	_playerLabelPurple = _g->LoadImage("Player/PlayerLabelPurple.png");
	_redButton = _g->LoadImage("RedButton.png");
	_blueButton = _g->LoadImage("BlueButton.png");

	//Load power plant images
	_powerPlantCoalImage = _g->LoadImage("PowerPlant/PowerPlantCoalImage.png");
	_powerPlantOilImage = _g->LoadImage("PowerPlant/PowerPlantOilImage.png");
	_powerPlantCoalOilImage = _g->LoadImage("PowerPlant/PowerPlantCoalOilImage.png");
	_powerPlantGarbageImage = _g->LoadImage("PowerPlant/PowerPlantGarbageImage.png");
	_powerPlantUranImage = _g->LoadImage("PowerPlant/PowerPlantUranImage.png");
	_powerPlantEcoImage = _g->LoadImage("PowerPlant/PowerPlantEcoImage.png");

	//Resources
	_coalImage = _g->LoadImage("Resources/Coal.png");
	_oilImage = _g->LoadImage("Resources/Oil.png");
	_garbageImage = _g->LoadImage("Resources/Garbage.png");
	_uranImage = _g->LoadImage("Resources/Uran.png");

	//houses
	_redHouse = _g->LoadImage("Player/RedPlayerHouse.png");
	_blueHouse = _g->LoadImage("Player/BluePlayerHouse.png");
	_purpleHouse = _g->LoadImage("Player/PurplePlayerHouse.png");
	_yellowHouse = _g->LoadImage("Player/YellowPlayerHouse.png");
	_blackHouse = _g->LoadImage("Player/BlackPlayerHouse.png");
	_greenHouse = _g->LoadImage("Player/GreenPlayerHouse.png");

	_activeImage = _g->LoadImage("PowerPlant/Active.png");
	_inActiveImage = _g->LoadImage("PowerPlant/InActive.png");
}

Draw::Pos Draw::GetFirstCurrentPlantPos()
{
	return _firstCurrentPlantPos;
}

Draw::Pos Draw::GetSizeOfPowerPlant()
{
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

Draw::Pos Draw::GetFirstCoalPos()
{
	return _firstResourceCoalPos;
}

Draw::Pos Draw::GetFirstOilPos()
{
	return _firstResourceOilPos;
}

Draw::Pos Draw::GetFirstGarbagePos()
{
	return _firstResourceGarbagePos;
}

Draw::Pos Draw::GetFirstUranPos()
{
	return _firstResourceUranPos;
}

Draw::Pos Draw::GetUranDiff()
{
	return _uranDiff;
}

Draw::Pos Draw::GetResourceDiff()
{
	return _resourceDiff;
}

Draw::Pos Draw::GetSizeOfResource()
{
	Pos pos = Pos(_coalImage.GetxSize(), _coalImage.GetYSize());
	return pos;
}

Draw::Pos Draw::GetSizeOfCity()
{
	Pos pos = Pos(_cityLabel.GetxSize(), _cityLabel.GetYSize());
	return pos;
}

void Draw::DrawWholeBoard(DrawInput* dI)
{
	_g->Clear();
	_g->StartDrawing();
	DrawBoard(dI->board, dI->regionsInPlay);
	for (int i = 0; i < dI->playerVector.size(); i++)
	{
		DrawPlayer(dI->playerVector[i], i, dI->gamePhase);
	}
	PrintPlayerInTurn(dI->playerInTurn);
	DrawPowerPlantMarket(dI->powerPlantMarket, dI->gameStep);
	if (dI->gamePhase == 2 && !dI->placePowerPlant)
	{
		DrawButton(&_redButton, "Pass", _passButtonPos);
	}
	else if (dI->gamePhase == 3 || dI->gamePhase == 4 || dI->gamePhase == 5)
	{
		DrawButton(&_redButton, "Klar", _passButtonPos);
	}
	PrintText(dI);
	DrawResourceMarket(dI->resourceMarket);
	_g->StopDrawing();
	_g->Flip();
}

void Draw::DrawBoard(Board* board, std::vector<int> usedRegions)
{
	_g->Draw(board->GetMapImage(), _mapPos.x, _mapPos.y, _mapPos.s);
	typedef std::map<std::string, City*>::iterator it_type;
	for (it_type it = board->GetCityDictFirstIterator(); it != board->GetCityDictLastIterator(); it++)
	{
		for (int index = 0; index < usedRegions.size(); index++)
		{
			if (it->second->GetRegion() == usedRegions[index])
			{
				DrawCity(it->second);
			}
		}
	}
}

void Draw::DrawCity(City* city)
{
	Pos cityNamePos = Pos(1, 18);
	Pos firstColorPos = Pos(3, 2);
	Pos colorDiff = Pos(_redHouse.GetxSize() + 5, _redHouse.GetYSize());;
	_g->Draw(&_cityLabel, city->GetXPos(), city->GetYPos(), 1);
	for (int index = 0; index < 3; index++)
	{
		Image* image = NULL;
		switch (city->GetColorForPos(index))
		{
		case City::red:
		{
			image = &_redHouse;
			break;
		}
		case City::blue:
		{
			image = &_blueHouse;
			break;
		}
		case City::black:
		{
			image = &_blackHouse;
			break;
		}
		case City::yellow:
		{
			image = &_yellowHouse;
			break;
		}
		case City::green:
		{
			image = &_greenHouse;
			break;
		}
		case City::purple:
		{
			image = &_purpleHouse;
			break;
		}
		}
		if (image != NULL)
		{
			_g->Draw(image, city->GetXPos() + firstColorPos.x + colorDiff.x*index, 
				city->GetYPos() + firstColorPos.y, 1);
		}
	}
	_g->PrintText8(city->GetName(), city->GetXPos() + cityNamePos.x, 
		city->GetYPos() + cityNamePos.y, Graphics::WHITE);
}

void Draw::DrawPlayer(Player* player, int playerIndex, int gamePhase)
{
	int FontSize = 15;
	Pos nameDiff = Pos(6, 6);
	Pos firstRes = Pos(140, 6);
	Pos resDiff = Pos(30, 0);
	Pos elektroPos = Pos(220, 25);
	Pos suppliedcitiesPos = Pos(210, 45);
	Pos plusPos = Pos(225, 45);
	Pos citiesInNetworkPos = Pos(235, 45);
	Pos activePos = Pos(55, 2);
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
	_g->PrintText15(player->GetName(), _firstPlayerPos.x + nameDiff.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + nameDiff.y, Graphics::WHITE);

	_g->PrintText15(player->GetAmountOfResource(ResourceMarket::coal), _firstPlayerPos.x + firstRes.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + firstRes.y, Graphics::WHITE);
	_g->PrintText15(player->GetAmountOfResource(ResourceMarket::oil), _firstPlayerPos.x + firstRes.x + resDiff.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + firstRes.y, Graphics::WHITE);
	_g->PrintText15(player->GetAmountOfResource(ResourceMarket::garbage), _firstPlayerPos.x + firstRes.x + 2*resDiff.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + firstRes.y, Graphics::BLACK);
	_g->PrintText15(player->GetAmountOfResource(ResourceMarket::uranium), _firstPlayerPos.x + firstRes.x + 3 * resDiff.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + firstRes.y, Graphics::WHITE);

	_g->PrintText15(player->GetAmountOfElektro(), _firstPlayerPos.x + elektroPos.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + elektroPos.y, Graphics::BLACK);

	_g->PrintText15(player->GetNumberOfSuppliedCities(), _firstPlayerPos.x + suppliedcitiesPos.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + suppliedcitiesPos.y, Graphics::BLACK);
	_g->PrintText15("+", _firstPlayerPos.x + plusPos.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + plusPos.y, Graphics::BLACK);
	_g->PrintText15(player->GetNumberOfCitiesInNetwork() - player->GetNumberOfSuppliedCities(),
		_firstPlayerPos.x + citiesInNetworkPos.x,
		_firstPlayerPos.y + playerIndex * _playerPosDiff.y + citiesInNetworkPos.y, Graphics::BLACK);
	for (int index = 0; index < player->numberOfPowerPlants; index++)
	{
		if (player->GetPowerPlant(index)->GetPowerPlantNumber() != 0)
		{
			int xPos = _firstPlayerPos.x + _firstPlayerPowerPlantPos.x + _playerPowerPlantDiff.x*index;
			int yPos = _firstPlayerPos.y + _firstPlayerPowerPlantPos.y + _playerPosDiff.y*playerIndex;
			DrawPowerPlant(player->GetPowerPlant(index), xPos, yPos);
			if (gamePhase == 5)
			{
				Image* image;
				if (player->GetPowerPlant(index)->GetActive())
				{
					image = &_activeImage;
				}
				else
				{
					image = &_inActiveImage;
				}
				_g->Draw(image, xPos + activePos.x, yPos + activePos.y, 1);
			}
		}
	}
}

void Draw::PrintPlayerInTurn(Player* player)
{
	std::string str = "Nuvarande spelare är ";
	std::string strName(player->GetName());
	str = str + strName;
	_g->PrintText15((char*) str.c_str(), _playerInTurnPos.x, _playerInTurnPos.y, Graphics::WHITE);
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
	PrintHelpText((char*)str.c_str());
}

void Draw::PrintHelpText(char* text)
{
	_g->PrintText15(text, _infoTextPos.x, _infoTextPos.y, Graphics::WHITE);
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
		case PowerPlant::uranium:
			tempImage = &_powerPlantUranImage;
			break;
		}
		Pos plantTextPos = Pos(0, 18);
		_g->Draw(tempImage, xPos, yPos, 1);
		_g->PrintText15(powerPlant->GetPowerPlantNumber(), xPos, yPos, Graphics::BLACK);
		std::string str;
		str = std::to_string(powerPlant->GetPowerPlantConsumption());
		str += "->" + std::to_string(powerPlant->GetPowerPlantProduction());
		const char* buffer = str.c_str();

		_g->PrintText8((char*)buffer, xPos + plantTextPos.x, yPos + plantTextPos.y, Graphics::BLACK);
	}
}

void Draw::DrawPowerPlantMarket(PowerPlantMarket* ppm, int gameStep)
{
	//current market
	for (int index = 0; index < ppm->GetNumberInCurrentMarket(); index++)
	{
		if(gameStep < 3)
		{
			int xDiff = (index % 2)*_plantDiff.x;
			int yDiff = (index / 2)*_plantDiff.y;
			DrawPowerPlant(ppm->GetPowerPlantCurrentDeck(index), _firstCurrentPlantPos.x + xDiff,
				_firstCurrentPlantPos.y + yDiff);
			DrawPowerPlant(ppm->GetPowerPlantFutureDeck(index), _firstFuturePlantPos.x + xDiff,
				_firstFuturePlantPos.y + yDiff);
		}
		else
		{
			int xDiff = (index % 3)*_plantDiff.x;
			int yDiff = min(1, max(0, index - 2))*_plantDiff.y;
			DrawPowerPlant(ppm->GetPowerPlantCurrentDeck(index), _firstCurrentPlantPos.x + xDiff,
				_firstCurrentPlantPos.y + yDiff);
		}
	}
}

void Draw::DrawBidButtons(int nextBid)
{
	DrawButton(&_redButton, "Bjud", _continueButtonPos);
	DrawButton(&_redButton, "Öka", _increaseButtonPos);
	DrawButton(&_redButton, "Minska", _decreaseButtonPos);
	_g->PrintText15(nextBid, _nextBidPos.x, _nextBidPos.y, Graphics::WHITE);
}

void Draw::DrawButton(Image* image, char* text, Pos pos)
{
	Pos textDiff = Pos(2, 10);
	_g->Draw(image, pos.x, pos.y, 1);
	_g->PrintText15(text, pos.x + textDiff.x, pos.y + textDiff.x, Graphics::BLACK);
}

void Draw::DrawResourceMarket(ResourceMarket* rm)
{
	Pos firstMarketMarker = Pos(0, 530);
	Pos marketMarkerDiff = Pos(63, 32);
	Pos firstMarketNumber = Pos(50, 530);
	for (int index = 0; index < rm->GetSizeOfMarket(); index++)
	{
		Image* tempImage;
		if (index % 2 == 0)
		{
			tempImage = &_redButton;
		}
		else
		{
			tempImage = &_blueButton;
		}
		_g->Draw(tempImage, firstMarketMarker.x + index*marketMarkerDiff.x, firstMarketMarker.y, 1);
		_g->Draw(tempImage, firstMarketMarker.x + index*marketMarkerDiff.x,
			firstMarketMarker.y + marketMarkerDiff.y, 1);
		_g->Draw(tempImage, firstMarketMarker.x + index*marketMarkerDiff.x,
			firstMarketMarker.y + 1.5*marketMarkerDiff.y, 1);
	}

	DrawResource(rm->GetAmountOfCoal(), ResourceMarket::coal);
	DrawResource(rm->GetAmountOfOil(), ResourceMarket::oil);
	DrawResource(rm->GetAmountOfGarbage(), ResourceMarket::garbage);
	DrawResource(rm->GetAmountOfUran(), ResourceMarket::uranium);

	//Draw the background for the market
	for(int index = 0; index < rm->GetSizeOfMarket(); index++)
	{
		if (index < (rm->GetSizeOfMarket() - 1))
		{
			_g->PrintText15(index + 1, firstMarketNumber.x + index*marketMarkerDiff.x,
				firstMarketNumber.y, Graphics::BLACK);
		}
		else
		{
			for (int i = index + 2; i < ResourceMarket::MAX_AMOUNT_URAN + 5; i += 2)
			{
				int xDiff = marketMarkerDiff.x / max(((i - index) % 4), 1) - 10;
				int yDiff = GetSizeOfPowerPlant().y*min(1, max(0, i - 13));
				_g->PrintText15(i, firstMarketNumber.x + (index - 1)*marketMarkerDiff.x + xDiff,
					firstMarketNumber.y + yDiff, Graphics::BLACK);
			}
		}
	}
}

void Draw::DrawResource(int numberOfResources, ResourceMarket::Resource type)
{
	Image* tempImage = new Image();
	int maxNumberOfResources = ResourceMarket::MAX_AMOUNT_RESOURCE;;
	Pos firstPos = Pos(0, 0);
	Pos resourceDiff = _resourceDiff;
	bool uranium = false;
	switch (type)
	{
	case ResourceMarket::coal:
	{
		tempImage = &_coalImage;
		firstPos = _firstResourceCoalPos;
		break;
	}
	case ResourceMarket::oil:
	{
		tempImage = &_oilImage;
		firstPos = _firstResourceOilPos;
		break;
	}
	case ResourceMarket::garbage:
	{
		tempImage = &_garbageImage;
		firstPos = _firstResourceGarbagePos;
		break;
	}
	case ResourceMarket::uranium:
	{
		tempImage = &_uranImage;
		maxNumberOfResources = ResourceMarket::MAX_AMOUNT_URAN;
		firstPos = _firstResourceUranPos;
		resourceDiff = _uranDiff;
		uranium = true;
		break;
	}
		break;
	default:
		break;
	}
	if (!uranium)
	{
		for (int index = 0; index < maxNumberOfResources; index++)
		{
			if (index >= (maxNumberOfResources - numberOfResources))
			{
				_g->Draw(tempImage, firstPos.x + resourceDiff.x*index, firstPos.y, 1);
			}
		}
	}
	else
	{
		for (int index = 0; index < maxNumberOfResources; index++)
		{
			if((index >= maxNumberOfResources - 4) && 
				(index >= (maxNumberOfResources - numberOfResources)))
			{
				int xDiff = firstPos.x + resourceDiff.x*8 + resourceDiff.x/2*((index - 8) % 2);
				int yDiff = resourceDiff.y*min(0, max(-1, index - 10));
				_g->Draw(tempImage, xDiff, firstPos.y + yDiff, 1);
			}
			else if (index >= (maxNumberOfResources - numberOfResources))
			{
				_g->Draw(tempImage, firstPos.x + resourceDiff.x*index, firstPos.y, 1);
			}
		}
	}
}

void Draw::PrintText(DrawInput* dI)
{
	Pos textPos = _infoTextPos;
	textPos.y = textPos.y + 30;
	std::string str = "Omgång: ";
	std::string strNumber = std::to_string(dI->gameTurn);
	str = str + strNumber;
	str = str + ", Steg: ";
	strNumber = std::to_string(dI->gameStep);
	str = str + strNumber;
	_g->PrintText15((char*) str.c_str(), textPos.x, textPos.y, Graphics::WHITE);
	switch (dI->gamePhase)
	{
	case 2:
	{
		if (dI->selectedPowerPlant > -1 && !dI->placePowerPlant)
		{
			PrintPlantForSale(dI->powerPlantMarket->GetPowerPlantCurrentDeck(dI->selectedPowerPlant),
				dI->currentPowerPlantBiddingPrice, dI->lastBiddingPlayer->GetName());
			DrawBidButtons(dI->nextBid);
		}
		else if (dI->placePowerPlant)
		{
			PrintHelpText("Välj position för verket");
		}
		else
		{
			PrintHelpText("Välj ett kraftverk");
		}
		break;
	}
	case 3:
	{
		PrintHelpText("Köp Resurser");
		break;
	}
	case 4:
	{
		PrintHelpText("Bygg städer");
		break;
	}
	case 5:
	{
		PrintHelpText("Välj aktiva kraftverk");
	}
	default:
		break;
	}
}