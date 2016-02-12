/*
 * player.h
 *
 *  Created on: Feb 1, 2016
 *      Author: eugeneorr
 */
#if defined(_WIN32)||(_WIN64)

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"



#endif
#if defined(__APPLE__)

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"

#endif

#if defined(__linux__)

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#endif


#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "bullet.h"

using namespace std;

class Player
{
public:

	int playerscore,oldscore,playerlives,oldlives;

	TTf_Font *font;
	SDL_Color colorP1 ={0,255,0,255};
	SDL_Color colorP2={0,0,255,255};

	SDL_Surface *scoreSurface,*livesSurface;
	SDL_Texture *scoretext,*livetext;

	SDL_Rect scorepos,livepos;
	string tempscore,templives;




	Mix_Chunk *laser;

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

	Player(SDL_Renderer *rend,int pnum,string filepath,string audiopath,float x,float y);





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
