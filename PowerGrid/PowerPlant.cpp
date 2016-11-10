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