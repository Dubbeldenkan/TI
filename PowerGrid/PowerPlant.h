#ifndef POWER_PLANT_H
#define POWER_PLANT_H

class PowerPlant
{
public:
	enum EnergySource { coal, oil, coalOrOil, uranium, garbage, none, phase3};
private:
	int _powerPlantNumber;
	EnergySource _energySource;
	int _consumption;
	int _generatedEnergy;
	int _savedResources = 0;

public:
	PowerPlant();
	PowerPlant(int, EnergySource, int, int);
	~PowerPlant() {};

	int GetPowerPlantNumber();
	int GetPowerPlantConsumption();
	int GetPowerPlantProduction();
	EnergySource GetType();
};

#endif // !POWER_PLANT