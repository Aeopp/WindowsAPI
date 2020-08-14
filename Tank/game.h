#pragma once
#include "game_interface.h"
class game : public game_interface
{
public:
	virtual void update()override;
	virtual void render()override;
	virtual void initialize()override;
	virtual void release()override;
public:

};

