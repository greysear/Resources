/*
 * player.h
 *
 *  Created on: Feb 1, 2016
 *      Author: eugeneorr
 */
#if defined(_WIN32)||(_WIN64)

#include "SDL.h"
#include "SDL_image.h"



#endif
#if defined(__APPLE__)

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#endif

#if defined(__linux__)

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#endif


#include <stdio.h>
#include <string>
#include <iostream>

#include <vector>
#include "bullet.h"

using namespace std;

class Player
{
public:

	//bullet list 
	vector<bullet> bulletlist;
	//strting holds play texture
	string playpath;
	//int play number 1 || 0
	int playnum;

	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Rect posRect;

	float xDir;
	float yDir;

	float Speed;

	float posX,PosY;

	Player(SDL_Renderer *rend,int pnum,string filepath,float x,float y);





	//get joystick axis
	void oncontrolleraxis(const SDL_ControllerAxisEvent event);

	//get button events
	void oncontrollerbutton(const SDL_ControllerButtonEvent event);



	void update(float deltatime);
	void draw(SDL_Renderer*rend);
	//destroy player

	~Player();
private:
	void Createbullet();

};
