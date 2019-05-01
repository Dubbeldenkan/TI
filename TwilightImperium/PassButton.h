#ifndef PASS_BUTTON_H
#define PASS_BUTTON_H

#include "GameBoardObject.h"

class PassButton : public GameBoardObject
{
private:
	static std::string _imagePath;
	static const TupleInt _imageSize;

public:
	PassButton();
	PassButton& operator=(const PassButton&);
	~PassButton();

	void SetGraphicalPosBasedOnPlayer(int);
};

#endif // !PASS_BUTTON_H