#include "ResourceMarket.h"

const int ResourceMarket::uranCostArray[] = { 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14, 16 };

ResourceMarket::ResourceMarket(int numberOfPlayers, GameBoard gameBoard)
{
	_numberOfPlayers = numberOfPlayers;
	_log = new Logger("ResourceMarket");
	switch (gameBoard)
	{
	case USA:
	{
		_amountOfCoal = startValueCoal;
		_amountOfOil = startValueOil;
		_amountOfGarbage = startValueGarbage;
		_amountOfUranium = startValueUran;
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
	_amountOfCoal += GetReSupplyAmount(_numberOfPlayers, step, Resource::coal);
	_amountOfOil += GetReSupplyAmount(_numberOfPlayers, step, Resource::oil);
	_amountOfGarbage += GetReSupplyAmount(_numberOfPlayers, step, Resource::garbage);
	_amountOfUranium += GetReSupplyAmount(_numberOfPlayers, step, Resource::uranium);

	_amountOfCoal = min(_amountOfCoal, MAX_AMOUNT_RESOURCE);
	_amountOfOil = min(_amountOfOil, MAX_AMOUNT_RESOURCE);
	_amountOfGarbage = min(_amountOfGarbage, MAX_AMOUNT_RESOURCE);
	_amountOfUranium = min(_amountOfUranium, MAX_AMOUNT_URAN);

	std::stringstream ss;
	ss << "Kolet har fyllts på med " << _resourceSupplyMatrix[_numberOfPlayers - 2][step - 1][Resource::coal] <<
		" till " << _amountOfCoal << "\nOljan har fyllts på med " << 
		_resourceSupplyMatrix[_numberOfPlayers - 2][step - 1][Resource::oil] << " till " << _amountOfOil <<
		"\nSoporna har fyllts på med " << _resourceSupplyMatrix[_numberOfPlayers - 2][step - 1][Resource::garbage] << 
		" till " << _amountOfGarbage << "\nUranet har fyllts på med " <<
		_resourceSupplyMatrix[_numberOfPlayers - 2][step - 1][Resource::uranium] << " till " << _amountOfUranium;
	_log->Log(ss.str());
}

int ResourceMarket::GetReSupplyAmount(int numberOfPlayers, int step, ResourceMarket::Resource resource)
{
	return _resourceSupplyMatrix[numberOfPlayers - 2][step - 1][resource];
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

int ResourceMarket::GetCost(int amount, ResourceMarket::Resource resource)
{
	int result = 0;
	if (ResourceMarket::uranium == resource)
	{
		for (int index = 0; index < amount; index++)
		{
			int number = (MAX_AMOUNT_URAN - GetResourceAmount(resource)) + index;
			result += uranCostArray[number];
		}
	}
	else
	{
		for (int index = 0; index < amount; index++)
		{
			int number = (MAX_AMOUNT_RESOURCE - GetResourceAmount(resource)) + index;
			result += (number / 3) + 1;
		}
	}
	return result;
}

int ResourceMarket::GetResourceAmount(ResourceMarket::Resource resource)
{
	int result;
	switch (resource)
	{
	case ResourceMarket::coal:
		result = _amountOfCoal;
		break;
	case ResourceMarket::oil:
		result = _amountOfOil;
		break;
	case ResourceMarket::garbage:
		result = _amountOfGarbage;
		break;
	case ResourceMarket::uranium:
		result = _amountOfUranium;
		break;
	default:
		break;
	}
	return result;
}

void ResourceMarket::TransferResources(int amount, ResourceMarket::Resource resource)
{
	char* resourceName = "";
	switch (resource)
	{
	case ResourceMarket::coal:
		_amountOfCoal -= amount;
		resourceName = "kol";
		break;
	case ResourceMarket::oil:
		_amountOfOil -= amount;
		resourceName = "olja";
		break;
	case ResourceMarket::garbage:
		_amountOfGarbage -= amount;
		resourceName = "sopor";
		break;
	case ResourceMarket::uranium:
		_amountOfUranium -= amount;
		resourceName = "uran";
		break;
	default:
		break;
	}
	std::stringstream ss;
	ss << "Marknaden har sålt " << amount << " " << resource;
	_log->Log(ss.str());
}

void ResourceMarket::PrintResourceMarketData(int gameTurn)
{
	std::stringstream ss;
	ss << "\n\nOmgång " << gameTurn;
	_log->Log(ss.str());
}

void ResourceMarket::ResetResourceMarket()
{
	_amountOfCoal = startValueCoal;
	_amountOfOil = startValueOil;
	_amountOfGarbage = startValueGarbage;
	_amountOfUranium = startValueUran;
}