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
		playerpath=filepath;


	}else{
		Playerpath=filepath;


	}
	surface=img_load(playerPath.c_str());

	posRect.x=x;
	posRect.y=y;
	//set movement floats to players original x&&y
	pos_x=x;
	pos_Y=y;
	//set direction of joystick
	xDir=0;
	yDir=0;




}

void oncontrolleraxis(const SDL_ControllerAxisEvent event)
{
	//cheack if stick =0
		if(event.which==0&& playnum==0)
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
void Player::update(float deltatime)
{

	posRect.y=(int)(pos_Y)+0.5f);
	if(posRect.x<0)
	{
		PosRect.x=0;
		pos_X=posRect.x;
	}
	if(posRect.x>1024-posRect.w)
	{
		posRect.x=1024-posrect.w;
		Posx=posRect.x;
	}
	if(posRect.y<0)
	{
		posRect.y=0;
		posY=posRect.y;

	}


}

void Player::draw(SDL_Rendere*rend)
{
	SDL_RenderCopy(renderer,texture,NULLm&posRect);
}


