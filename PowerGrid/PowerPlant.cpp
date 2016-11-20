#include "PowerPlant.h"

PowerPlant::PowerPlant()
{
	_powerPlantNumber = 0;
}

PowerPlant::PowerPlant(int powerPlantNumber, EnergySource energySource, int amountOfResources, int generatedEnergy)
{
	_powerPlantNumber = powerPlantNumber;
	_energySource = energySource;
	_consumption = amountOfResources;
	_generatedEnergy = generatedEnergy;
}

int PowerPlant::GetPowerPlantNumber()
{
	return _powerPlantNumber;
}

int PowerPlant::GetPowerPlantConsumption()
{
	return _consumption;
}

int PowerPlant::GetPowerPlantProduction()
{
	return _generatedEnergy;
}

PowerPlant::EnergySource PowerPlant::GetType()
{
	return _energySource;
}

void PowerPlant::ToggleActive()
{
	_active = !_active;
}

void PowerPlant::SetToInActive()
{
	_active = false;
}

void PowerPlant::SetToActive()
{
	_active = true;
}

bool PowerPlant::GetActive()
{
	return _active;
}