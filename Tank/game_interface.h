#pragma once

class game_interface
{
public:
	virtual void update()abstract;
	virtual void render()abstract;
	virtual void initialize()abstract;
	virtual void release()abstract;
};

