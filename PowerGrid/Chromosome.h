#ifndef CHROMOSOME_H
#define CHROMOSOME_H

class Chromosome
{
public:
	struct Phase2Struct
	{

	};
private:
	int _gen[3];

public:
	Chromosome() {};
	Chromosome(int, int, int);
	~Chromosome() {};
};

#endif // !CHROMOSOME_H