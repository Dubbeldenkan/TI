#ifndef AI_H
#define AI_H

#include "Player.h"
#include "Chromosome.h"

class AI
{
	Player* player;
	Chromosome _chrom;
public:
	AI() {};
	AI(Chromosome, Player*);
	~AI() {};

	//TODO ska anv�ndas f�r att s�tta AI:n till en ny spelare
	void SetPlayer(Player*);
};

#endif // !AI_H