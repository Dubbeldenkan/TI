#ifndef POWER_PLANT_H
#define POWER_PLANT_H

class PowerPlant
{
public:
	enum EnergySource { coal, oil, garbage, uranium, coalOrOil, none, phase3};
private:
	int _powerPlantNumber;
	EnergySource _energySource;
	int _consumption;
	int _generatedEnergy;
	bool _active = false;

public:
	PowerPlant();
	PowerPlant(int, EnergySource, int, int);
	~PowerPlant() {};

	int GetPowerPlantNumber();
	int GetPowerPlantConsumption();
	int GetPowerPlantProduction();
	void ToggleActive();
	void SetToInActive();
	void SetToActive();
	bool GetActive();
	EnergySource GetType();
};

#endif // !POWER_PLANT