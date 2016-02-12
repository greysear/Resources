/*
 * Player.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: eugeneorr
 */
#include "player.h"
//analog joy stick deads zone
const int JOYSTICK_DEAD_ZONE=8000;

Player::Player(SDL_Renderer*rend,int pnum,string filepath,string audiopath,float x,float y)
{

	playnum = pnum;
//cout<<pnum<<"player number is"<<endl;
	Speed=500.0f;
laser =Mix_LoadWAV((audiopath+"shoot.wav").c_str());

//init score and lives var;

playerscore=0;
oldscore=0;
playerlives=3;
oldlives=0;
//init font system

TTF_Init();

font=TTF_OpenFont((filepath+"Coalition_v2..ttf"))

	if(playnum==0)
	{
		playpath=filepath + "/player1.png";


	}else{
		playpath=filepath+ "/player2.png";


	}

	surface = IMG_Load(playpath.c_str());

	if (surface == NULL) {
			// In the case that the window could not be made...
			printf("Could not create surface: %s\n", SDL_GetError());

		}
	texture=SDL_CreateTextureFromSurface(rend,surface);
	if (texture == NULL) {
			// In the case that the window could not be made...
			printf("Could not create texture: %s\n", SDL_GetError());

		}


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
	
//string to create a path for bullets

	string bulletpath;
	if (playnum == 0)
	{
		bulletpath = filepath + "/p1bull.png";
		
	}
	else {
		bulletpath = filepath + "/p2bull.png";
	}

	for (int i = 0; i < 10; i++)
	{
		//create bullets offscreen
		bullet tmpbullet(rend, bulletpath, -1000,-1000);
		//addto bullet list
		bulletlist.push_back(tmpbullet);
	}


}

void Player::Createbullet()
{
	
	for (int i = 0; i < bulletlist.size(); i++)
	{
		
		if (bulletlist[i].active == false)
		{

			Mix_PlayChannel(-1,laser,0);
			bulletlist[i].active = true;

		bulletlist[i].bulpos.x = (posX + (posRect.w / 2));

		bulletlist[i].bulpos.x = (bulletlist[i].bulpos.x - (bulletlist[i].bulpos.w / 2));
		bulletlist[i].bulpos.y= posRect.y;

		bulletlist[i].xpos = posX;
		bulletlist[i].ypos = PosY;
		cout << bulletlist[i].bulpos.x << " X " << bulletlist[i].bulpos.y << " Y " << bulletlist[i].bulpos.w << "w" << endl;
		break;
		}

	}
}



void Player::oncontrollerbutton(const SDL_ControllerButtonEvent event)
{
	if(event.which==0 && playnum==0)
	{
		//if A button
		if(event.button==0)
		{
			cout<<"player 1 button a"<<endl;
			Createbullet();
			
		}
	}
	if(event.which==1 && playnum==1)
	{

		if(event.button==0)
		{
			cout<<"player2 button A"<<endl;
			Createbullet();
		}

	}
}



void Player:: oncontrolleraxis(const SDL_ControllerAxisEvent event)
{
	//cheack if stick =0
	if (event.which == 0 && playnum == 0)
	{



		//cheak x axis
		if (event.axis == 0)
		{
			if (event.value < -JOYSTICK_DEAD_ZONE)
			{
				xDir = -1.0f;
			}
			else if (event.value > JOYSTICK_DEAD_ZONE)
			{
				xDir = 1.0f;
			}
			else
			{
				xDir = 0.0f;
			}
		}



		//cheak y axis
		if (event.axis == 1)
		{
			if (event.value<-JOYSTICK_DEAD_ZONE)
			{
				yDir = -1.0f;
			}
			else if (event.value>JOYSTICK_DEAD_ZONE)
			{
				yDir = 1.0f;
			}
			else
			{
				yDir = 0.0f;
			}
		}

	}
		


		///**********second player*********///////////////
		

		
		if (event.which == 1 && playnum == 1)
			{



				//cheak x axis
				if (event.axis == 0)
				{
					if (event.value<
						-JOYSTICK_DEAD_ZONE)
					{
						xDir = -1.0f;
					}
					else if (event.value>JOYSTICK_DEAD_ZONE)
					{
						xDir = 1.0f;
					}
					else
					{
						xDir = 0.0f;
					}
				}
							//cheack y axis
				if (event.axis == 1)
				{
					if (event.value < -JOYSTICK_DEAD_ZONE)
					{
						yDir = -1.0f;
					}
					else if (event.value > JOYSTICK_DEAD_ZONE)
					{
						yDir = 1.0f;
					}
					else
					{
						yDir = 0.0f;
					}

				}

			}

}


void Player::update(float deltatime)
{


	posX+=(Speed *xDir)*deltatime;
	PosY+=(Speed *yDir)*deltatime;

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
		posRect.y=768-posRect.h;
		PosY=posRect.y;
	}
	
	for (int i = 0; i < bulletlist.size();i++)
			{
				if (bulletlist[i].active)
				{
					bulletlist[i].update(deltatime);
				}

	}


}

void Player::draw(SDL_Renderer*rend)
{
	//cout<<"draw player is called";
	SDL_RenderCopy(rend,texture,NULL,&posRect);

	for (int i = 0; i < bulletlist.size(); i++)
	{
		if (bulletlist[i].active)
		{
			bulletlist[i].Draw(rend);
		}
	}

}

Player::~Player()
{

	SDL_DestroyTexture(texture);
}

