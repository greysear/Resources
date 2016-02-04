/*
 * Player.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: eugeneorr
 */
#include "player.h"
//analog joy stick deads zone
const int JOYSTICK_DEAD_ZONE=8000;

Player::Player(SDL_Renderer*rend,int pnum,string filepath,float x,float y)
{

	playnum=pnum;

	Speed=500.0f;

	if(playnum==0)
	{
		playpath=filepath + "player1.png";


	}else{
		playpath=filepath+ "player2.png";


	}
	surface = IMG_Load(playpath.c_str());

	texture=SDL_CreateTextureFromSurface(rend,surface);

	SDL_FreeSurface(surface);

	posRect.x=x;
	posRect.y=y;
	int w,h;
	SDL_QueryTexture(texture,NULL,NULL,&w,&h);
	posRect.w=w;
	posRect.h=h;
	//set movement floats to players original x&&y
	posX=x;
	PosY=y;
	//set direction of joystick
	xDir=0;
	yDir=0;




}
/*
void oncontrolleraxis(const SDL_ControllerAxisEvent event)
{
	//cheack if stick =0
		if(event.which==0&&playnum==0)
		{



		//cheak x axis
		if(event.axis==0)
		{
			if(event.value<-JOYSTICK_DEAD_ZONE)
					{
						xDir=-1.0f;
					}else if(event.value>JOYSTICK_DEAD_ZONE)
					{
						xDir=1.0f;
					}
					else
					{
						xDir=0.0f;
					}
		}
		//cheack y axis
		if(event.axis==1)
		{
			if(event.value<-JOYSTICK_DEAD_ZONE)
							{
								yDir=-1.0f;
							}else if(event.value>JOYSTICK_DEAD_ZONE)
							{
								yDir=1.0f;
							}
							else
							{
								yDir=0.0f;
							}

		}
		}


}

*/
void Player::update(float deltatime)
{


	posX+=(Speed *xDir)*deltatime;
	PosY+=(Speed *xDir)*deltatime;

	posRect.x=(int)(posX+0.5f);
	posRect.y=(int)(PosY+0.5f);

	if(posRect.x<0)
	{
		posRect.x=0;

		posX=posRect.x;
	}
	if(posRect.x>1024-posRect.w)
	{
		posRect.x=1024-posRect.w;

		posX=posRect.x;
	}
	if(posRect.y<0)
	{
		posRect.y=0;

		PosY=posRect.y;

	}
	if(posRect.y>768-posRect.h)
	{
		posRect.y=768*posRect.h;
		PosY=posRect.y;
	}


}

void Player::draw(SDL_Renderer*rend)
{
	SDL_RenderCopy(rend,texture,NULL,&posRect);
}


