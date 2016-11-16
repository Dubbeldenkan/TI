#include "ResourceMarket.h"

ResourceMarket::ResourceMarket(int numberOfPlayers, GameBoard gameBoard)
{
	_numberOfPlayers = numberOfPlayers;
	switch (gameBoard)
	{
	case USA:
	{
		_amountOfCoal = 24;
		_amountOfOil = 18;
		_amountOfGarbage = 6;
		_amountOfUranium = 12;
		break;
	}
	default:
	{
		OutputDebugString("This GameBoard is not implemented yet.");
	}
	}
}

int ResourceMarket::GetPrice(Resource resource, int amount)
{
	int resultAmount = 0;
	int firstPos = GetFirstResPos(resource);
	for (int currentPos = firstPos; currentPos < currentPos + amount; currentPos++)
	{
		resultAmount = GetPriceForPos(resource, currentPos);
	}
	return resultAmount;
}

int ResourceMarket::GetPriceForPos(Resource resource, int pos)
{
	switch (resource)
	{
	case ResourceMarket::coal:
	case ResourceMarket::oil:
	case ResourceMarket::garbage:
		return pos / 3;
		break;
	case ResourceMarket::uranium:
		return pos;
		break;
	default:
		OutputDebugString("Undefined resource.");
		return 0;
		break;
	}
}

int ResourceMarket::GetFirstResPos(Resource resource)
{
	switch (resource)
	{
	case coal:
		return MAX_AMOUNT_RESOURCE - _amountOfCoal + 1;
		break;
	case oil:
		return MAX_AMOUNT_RESOURCE - _amountOfOil + 1;
		break;
	case garbage:
		return MAX_AMOUNT_RESOURCE - _amountOfGarbage + 1;
		break;
	case uranium:
		return MAX_AMOUNT_URAN - _amountOfUranium + 1;
		break;
	default:
		OutputDebugString("Undefined resource.");
		return 0;
		break;
	}
}

void ResourceMarket::ReSupplyResourceMarket(int step)
{
	_amountOfCoal += resourceSupplyMatrix[_numberOfPlayers + 2][step + 1][Resource::coal];
	_amountOfOil += resourceSupplyMatrix[_numberOfPlayers + 2][step + 1][Resource::oil];
	_amountOfGarbage += resourceSupplyMatrix[_numberOfPlayers + 2][step + 1][Resource::garbage];
	_amountOfUranium += resourceSupplyMatrix[_numberOfPlayers + 2][step + 1][Resource::uranium];

	_amountOfCoal = min(_amountOfCoal, MAX_AMOUNT_RESOURCE);
	_amountOfOil = min(_amountOfOil, MAX_AMOUNT_RESOURCE);
	_amountOfGarbage = min(_amountOfGarbage, MAX_AMOUNT_RESOURCE);
	_amountOfUranium = min(_amountOfUranium, MAX_AMOUNT_URAN);
}

int ResourceMarket::GetSizeOfMarket()
{
	return _marketSize;
}

int ResourceMarket::GetAmountOfCoal()
{
	return _amountOfCoal;
}

int ResourceMarket::GetAmountOfOil()
{
	return _amountOfOil;
}

int ResourceMarket::GetAmountOfGarbage()
{
	return _amountOfGarbage;
}

int ResourceMarket::GetAmountOfUran()
{
	return _amountOfUranium;
}