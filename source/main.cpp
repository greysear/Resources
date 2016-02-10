/*
main.cpp
*
*  Created on: Jan 21, 2016
*      Author: eugeneorr
*/

# include "Player.h"
#if defined(_WIN32)||(_WIN64)

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"



#endif

#if defined(_WIN32)||(_WIN64)
#include <direct.h>
#define getcwd _getcwd
#endif

#if defined(__APPLE__)

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"


#endif

#if defined(__linux__)

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"


#endif
#if defined(__linux__)
#include <unistd.h>


#endif



#include <stdio.h>

#include <iostream>

using namespace std;

float deltatime = 0.0;
int thistime = 0;
int lasttime;

bool menu, instruction, play1, players2, Win, Lose, quit;

const int JOYSTICK_DEAD_ZONE=8000;
float xDir,yDir;
float posX,posY;

SDL_Rect curpos,activpos;
int curspeed=400;
//set speed
int backspeed = 100;


//set speed
int backspeed2 = 100;
/////***************bool to cheak if mouse is over a button**********/////
bool play1over=false,play2over=false,instructover=false,menuover=false,quitover=false;
bool playaginover=false;
//sdl rect pos bg1 and 2

SDL_Rect bkgd1Pos, bkgd2Pos;
///background temp var
float bg1pos_x = 0, bg1pos_y = 0;
float bg2pos_x = 0, bg2pos_y = -768;
//move background
void updatebackground(float deltatime)
{
	//update background one

	bg1pos_y += (backspeed * 1)*deltatime;

	//set the new back ground one pos
	bkgd1Pos.y = (int)(bg1pos_y + 0.5f);

	//reset when off bottom the bottom of the screen
	if (bkgd1Pos.y >= 768)
	{
		bkgd1Pos.y = -768;
		bg1pos_y = bkgd1Pos.y;

	}

	bg2pos_y += (backspeed2 * 1)*deltatime;

	//set the new back ground one pos
	bkgd2Pos.y = (int)(bg2pos_y + 0.5f);

	//reset when off bottom the bottom of the screen
	if (bkgd2Pos.y >= 768)
	{
		bkgd2Pos.y = -768;
		bg2pos_y = bkgd2Pos.y;


	}

}

void moveCursor(const SDL_ControllerAxisEvent event)
{
	//cheack if stick =0
	if(event.which==0)
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
//update cursor on screen
void updatecursor(float deltaTime)
{
	posX+=(curspeed*xDir)*deltaTime;
	posY+=(curspeed*yDir)*deltaTime;

	//assomge rect ints x amd y

	curpos.x=(int)(posX+0.5f);
	curpos.y=(int)(posY+0.5f);

	activpos.x=curpos.x;
	activpos.y=curpos.y;

	if(curpos.x<0)
	{
		curpos.x=0;
		posX=curpos.x;
	}

	if(curpos.x>1024-curpos.w)
	{
		curpos.x=1024-curpos.w;
		posX=curpos.x;
	}
	if(curpos.y<0)
	{
		curpos.y=0;
		posY=curpos.y;
	}
	if(curpos.y>768-curpos.h)
	{
		curpos.y=768-curpos.h;
		posY=curpos.y;
	}


}



int main(int argc, char* argv[]) {




#if defined(_WIN32)||(_WIN64)

	cout << "Running on windows  " << endl;

	string currentworkingdirectory(getcwd(NULL, 0));

	//create string lincking pc image folder

	string images_dir = currentworkingdirectory + "\\Resources\\images";
	string audio_dir = currentworkingdirectory + "\\Resources\\audio";

#endif

#if defined(__APPLE__)

	cout << "running on mac" << endl;
	//get current working dir
	string currentworkingdirectory(getcwd(NULL, 0));

	//create string lincing mac image folder

	string images_dir = currentworkingdirectory + "/Resources/images";
	//test

	string audio_dir=currentworkingdirectory+"/Resources/audio/";

#endif

#if defined(__linux__)

	cout << "running on linux" << endl;
	cout << "effectivly ran on linux" << endl;

	string currentworkingdirectory(getcwd(NULL, 0));

	//create string lincking mac image folder

	string images_dir = currentworkingdirectory + "/Resources/images";
	
	string audio_dir = currentworkingdirectory + "/Resources/audio";




#endif


	SDL_Window *window;                    // Declare a pointer

	SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2

												// Create an application window with the following settings:
	window = SDL_CreateWindow(
		"An SDL2 window",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		1024,                               // width, in pixels
		768,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
		);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	//declare the renderer
	SDL_Renderer *rend = NULL;

	//create the renderer
	rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Player Player1 = Player(rend,0,images_dir.c_str(),250.0,500.0);
	Player Player2 = Player(rend, 1, images_dir.c_str(), 750.0, 500.0);

	string BKGDpath = images_dir + "/back1.png";
	//
	//cout << BKGDpath<<endl;

	SDL_Surface *surface = IMG_Load(BKGDpath.c_str());

	//create sdl texture
	SDL_Texture *bkgd1;
	//place surface info into the tesxture bkgd1;
	bkgd1 = SDL_CreateTextureFromSurface(rend, surface);




	//create backcround2

	string bg2 = images_dir + "/back2.png";
	// cout<<curpath<<endl;
	//create surface for cursor
	surface = IMG_Load(bg2.c_str());


	//create sdl texture
	SDL_Texture *bkgd2;
	//place surface info into the tesxture bkgd2;
	bkgd2 = SDL_CreateTextureFromSurface(rend, surface);
	//freee the surface
	// SDL_FreeSurface(surface);



	//  SDL_Rect bkgd2Pos;
	//set xywand h for rect
	bkgd2Pos.x = 0;
	bkgd2Pos.y = -768;
	bkgd2Pos.w = 1024;
	bkgd2Pos.h = 768;




	//create a rectangle xywh

	//SDL_Rect bkgd1Pos;
	//set xywand h for rect
	bkgd1Pos.x = 0;
	bkgd1Pos.y = 0;
	bkgd1Pos.w = 1024;
	bkgd1Pos.h = 768;





	//load path to cursor

	string curpath = images_dir + "/cursor.png";
	//cout<<curpath<<endl;
	//create surface for cursor
	surface = IMG_Load(curpath.c_str());

	//create sdl texture
	SDL_Texture *cur;
	//place surface info into the texture for cursor;
	cur = SDL_CreateTextureFromSurface(rend, surface);

	SDL_FreeSurface(surface);

	//SDL_Rect curpos;
	curpos.x = 100;
	curpos.y = 100;
	curpos.w = 50;
	curpos.h = 50;



	activpos.x=curpos.x;
	activpos.y=curpos.y+1;
	activpos.w=10;
	activpos.h=10;




	///////***********menu start********////////////////
	//******titles**********////////
	string titl = images_dir + "/title.png";
	// cout<<curpath<<endl;
	//create surface for cursor
	surface = IMG_Load(titl.c_str());


	//create sdl texture
	SDL_Texture *title;
	//place surface info into the tesxture bkgd2;
	title = SDL_CreateTextureFromSurface(rend, surface);
	SDL_Rect titlep;
	titlep.x = 0;
	titlep.y = 0;
	titlep.w = 1024;
	titlep.h = 200;

	SDL_FreeSurface(surface);
	/////*********title ends///


	///******play one button*****/////

	string p1b = images_dir + "/playonenorm.png";
	// cout<<curpath<<endl;
	//create surface for cursor
	surface = IMG_Load(p1b.c_str());


	//create sdl texture
	SDL_Texture *p1bb;
	//place surface info into the tesxture bkgd2;
	p1bb = SDL_CreateTextureFromSurface(rend, surface);

	SDL_Rect p1bp;
	p1bp.x = 150;
	p1bp.y = 300;
	p1bp.w = 200;
	p1bp.h = 100;

	SDL_FreeSurface(surface);
	///play one over state
	string p1bo = images_dir + "/olayeroneover.png";
	// cout<<curpath<<endl;
	//create surface for cursor
	surface = IMG_Load(p1bo.c_str());


	//create sdl texture
	SDL_Texture *p1bbo;
	//place surface info into the tesxture bkgd2;
	p1bbo = SDL_CreateTextureFromSurface(rend, surface);

	//      SDL_Rect p1bp;
	//         p1bp.x=150;
	//        p1bp.y=300;
	//        p1bp.w=200;
	//       p1bp.h=100;

	SDL_FreeSurface(surface);




	////****play one button ends******//////

	//********************play two button begins***************************/////////////////////////////////

	string p2b = images_dir + "/twoplayernorm.png";

	surface = IMG_Load(p2b.c_str());


	SDL_Texture *p2bb;

	p2bb = SDL_CreateTextureFromSurface(rend, surface);

	SDL_Rect p2bp;
	p2bp.x = 150;
	p2bp.y = 450;
	p2bp.w = 200;
	p2bp.h = 100;

	SDL_FreeSurface(surface);
	///play two over state
	string p2bo = images_dir + "/twoplayerover.png";
	;

	surface = IMG_Load(p2bo.c_str());

	SDL_Texture *p2bbo;
	//place surface info into the tesxture bkgd2;
	p2bbo = SDL_CreateTextureFromSurface(rend, surface);

	SDL_FreeSurface(surface);

	//end play two over button


	////////********instructions  button******************//////////////////

	//instruct normal
	string ins = images_dir + "/instructnorm.png";

	surface = IMG_Load(ins.c_str());


	SDL_Texture *insn;

	insn = SDL_CreateTextureFromSurface(rend, surface);

	SDL_Rect insnp;
	insnp.x = 500;
	insnp.y = 300;
	insnp.w = 200;
	insnp.h = 100;

	SDL_FreeSurface(surface);
	///instruct over
	string ino = images_dir + "/instructover.png";
	;

	surface = IMG_Load(ino.c_str());

	SDL_Texture *inso;
	//place surface info into the tesxture bkgd2;
	inso = SDL_CreateTextureFromSurface(rend, surface);

	SDL_FreeSurface(surface);







	//////////***********instructions button end*********************///////


	/////*********quit button**********//////////////////////




	//quit normal
	string quitn = images_dir + "/quitnorm.png";

	surface = IMG_Load(quitn.c_str());


	SDL_Texture *qn;

	qn = SDL_CreateTextureFromSurface(rend, surface);

	SDL_Rect qnp;
	qnp.x = 500;
	qnp.y = 450;
	qnp.w = 200;
	qnp.h = 100;

	SDL_FreeSurface(surface);
	///quit  over
	string quito = images_dir + "/quitover.png";
	;

	surface = IMG_Load(quito.c_str());

	SDL_Texture *qo;
	//place surface info into the tesxture bkgd2;
	qo = SDL_CreateTextureFromSurface(rend, surface);

	SDL_FreeSurface(surface);





	/////********quit button ends***********//////

	///***********Instuction screen************///////////



	string ititl = images_dir + "/instruct.png";
	// cout<<curpath<<endl;
	//create surface for cursor
	surface = IMG_Load(ititl.c_str());


	//create sdl texture
	SDL_Texture *ititle;
	//place surface info into the tesxture bkgd2;
	ititle = SDL_CreateTextureFromSurface(rend, surface);
	SDL_Rect ititlep;
	ititlep.x = 0;
	ititlep.y = 200;
	ititlep.w = 1024;
	ititlep.h = 200;

	SDL_FreeSurface(surface);
	//********mainmenubutton*************////

	string memn = images_dir + "/mainmenunorm.png";

	surface = IMG_Load(memn.c_str());


	SDL_Texture *memun;

	memun = SDL_CreateTextureFromSurface(rend, surface);

	SDL_Rect memunp;
	memunp.x = 500;
	memunp.y = 450;
	memunp.w = 200;
	memunp.h = 100;

	SDL_FreeSurface(surface);
	///menu  over
	string memuo = images_dir + "/mainmenuover.png";
	;

	surface = IMG_Load(memuo.c_str());

	SDL_Texture *memo;
	//place surface info into the tesxture bkgd2;
	memo = SDL_CreateTextureFromSurface(rend, surface);

	SDL_FreeSurface(surface);




	///************Instruction screen ends************////////////

	///************ one player***************/////////////////////


	string ptitl = images_dir + "/playerone!.png";
	// cout<<curpath<<endl;
	//create surface for cursor
	surface = IMG_Load(ptitl.c_str());


	//create sdl texture
	SDL_Texture *ptitle;
	//place surface info into the tesxture bkgd2;
	ptitle = SDL_CreateTextureFromSurface(rend, surface);
	SDL_Rect ptitlep;
	ptitlep.x = 0;
	ptitlep.y = 200;
	ptitlep.w = 1024;
	ptitlep.h = 200;



	//**************oneplayerends****************/////////////////


	//************playertwoscreen******************///////////////


	string p2titl = images_dir + "/twoplayert.png";
	// cout<<curpath<<endl;
	//create surface for cursor
	surface = IMG_Load(p2titl.c_str());


	//create sdl texture
	SDL_Texture *p2title;
	//place surface info into the tesxture bkgd2;
	p2title = SDL_CreateTextureFromSurface(rend, surface);
	SDL_Rect p2titlep;
	p2titlep.x = 0;
	p2titlep.y = 200;
	p2titlep.w = 1024;
	p2titlep.h = 200;






	//************playertwoscreenends******************///////////////
	/// ********************WIN SCREEN***************/////////////

	string wtitl = images_dir + "/win.png";
	// cout<<curpath<<endl;
	//create surface for cursor
	surface = IMG_Load(wtitl.c_str());


	//create sdl texture
	SDL_Texture *wtitle;
	//place surface info into the tesxture bkgd2;
	wtitle = SDL_CreateTextureFromSurface(rend, surface);

	SDL_FreeSurface(surface);

	string plagn = images_dir + "/playagain.png";

	surface = IMG_Load(plagn.c_str());


	SDL_Texture *playn;

	playn = SDL_CreateTextureFromSurface(rend, surface);

	SDL_Rect playnp;
	playnp.x = 200;
	playnp.y = 650;
	playnp.w = 200;
	playnp.h = 100;

	SDL_FreeSurface(surface);

	string plago = images_dir + "/playagainover.png";

	surface = IMG_Load(plago.c_str());


	SDL_Texture *playo;

	playo = SDL_CreateTextureFromSurface(rend, surface);

	SDL_FreeSurface(surface);

	/// ********************WIN SCREEN end***************/////////////


	///****loseScreen***********//////////////////////



	string ltitl = images_dir + "/losetitle.png";
	// cout<<curpath<<endl;
	//create surface for cursor
	surface = IMG_Load(ltitl.c_str());


	//create sdl texture
	SDL_Texture *ltitle;
	//place surface info into the tesxture bkgd2;
	ltitle = SDL_CreateTextureFromSurface(rend, surface);

	SDL_FreeSurface(surface);




	///****loseScreen***********//////////////////////

///******


	

	
	
	//turn on game controller events
	SDL_GameControllerEventState(SDL_ENABLE);
	//set up game controller
	SDL_GameController* gGameController0 = NULL;
	//****** open game controller up
	gGameController0 = SDL_GameControllerOpen(0);


	//set up game controller2
	//turn on game controller events

	//set up game controller
	SDL_GameController* gGameController1 = NULL;
	//****** open game controller up
	gGameController1 = SDL_GameControllerOpen(1);

	//SDL event to handle input

	SDL_Event event;
	//***set up variable for game states
	enum GameState { MENU, instruct, Playone, play2, win, lose };

	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
	Mix_Music *bgn=Mix_LoadMUS((audio_dir+"Theyre-Closing-In.mp3").c_str());

	if(!Mix_PlayingMusic())
		Mix_PlayMusic(bgn,-1);

	Mix_Chunk *oversound=Mix_LoadWAV((audio_dir+"over.wav").c_str());
	Mix_Chunk *pressedsound=Mix_LoadWAV((audio_dir+"pressed.wav").c_str());
	bool alreadyover=false;


	//set up initial state
	GameState gamestate = MENU;
	//bool values to controll movement through states




	//Fill the surface white
	///SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 42, 254 ) );

	//Update the surface
	//SDL_UpdateWindowSurface( window );

	// The window is open: could enter program loop here (see SDL_PollEvent())
	while (!quit)
	{
		switch (gamestate)
		{
		case MENU:

			menu = true;


			while (menu)
			{



				//cheack for input events

				thistime = SDL_GetTicks();
				deltatime = (float)(thistime - lasttime) / 1000;
				lasttime = thistime;
				//cheack for input events
				if (SDL_PollEvent(&event))
				{
					//check to see if the sdl window is closed player hits x in window
					if (event.type == SDL_QUIT)
					{
						quit = true;
						menu = false;
						break;
					}
					switch (event.type)
					{

					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0)
						{
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
							{
								if(play1over)
								{
									menu=false;
									gamestate=Playone;
									play1over=false;
								}

								if(play2over)
								{
									gamestate=play2;
									menu=false;
									play2over=false;
								}
								if(instructover)
								{
								gamestate = instruct;
								menu=false;
							instructover=false;
								}
								if(quitover)
								{
									menu=false;
									quit=true;
								}

										}break;

					case SDL_CONTROLLERAXISMOTION:
						moveCursor(event.caxis);
							break;

						}


					}
				}
////////***************menu update//////****************

				updatebackground(deltatime);

				updatecursor(deltatime);

 play1over=SDL_HasIntersection(&activpos,&p1bp);
 play2over=SDL_HasIntersection(&activpos,&p2bp);
 instructover=SDL_HasIntersection(&activpos,&insnp);
 quitover=SDL_HasIntersection(&activpos,&qnp);



				SDL_RenderClear(rend);
				//draw imagebackground1
				SDL_RenderCopy(rend, bkgd1, NULL, &bkgd1Pos);
				SDL_RenderCopy(rend, bkgd2, NULL, &bkgd2Pos);
				SDL_RenderCopy(rend, title, NULL, &titlep);

				//////////***************logic for button states*********//////////
				if(play1over)
				{
				SDL_RenderCopy(rend, p1bbo, NULL, &p1bp);
				}else
				{
					SDL_RenderCopy(rend, p1bb, NULL, &p1bp);
				}
				if(play2over)
				{
				SDL_RenderCopy(rend, p2bbo, NULL, &p2bp);

				}else
				{

					SDL_RenderCopy(rend, p2bb, NULL, &p2bp);

				}
				if(instructover)
				{
				SDL_RenderCopy(rend, inso, NULL, &insnp);
				}else
				{
					SDL_RenderCopy(rend, insn, NULL, &insnp);
				}
				if(quitover)
				{

				SDL_RenderCopy(rend, qo, NULL, &qnp);
				}else
				{
					SDL_RenderCopy(rend, qn, NULL, &qnp);
				}
				//////////***************logic for button states ends*********//////////

				SDL_RenderCopy(rend, cur, NULL, &curpos);

				SDL_RenderPresent(rend);


			}
			break;

			//case two begins
		case instruct:

			instruction = true;

		

			while (instruction)
			{


				thistime = SDL_GetTicks();
				deltatime = (float)(thistime - lasttime) / 1000;
				lasttime = thistime;
				//cheack for input events
				if (SDL_PollEvent(&event))
				{
					//check to see if the sdl window is closed player hits x in window
					if (event.type == SDL_QUIT)
					{
						quit = true;
						instruction = false;
						break;
					}
					switch (event.type)
					{

					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0)
						{
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
							{
								if(menuover)
								{

								instruction = false;
								gamestate = MENU;
								menuover=false;
								}
							}

						}
						break;



					case SDL_CONTROLLERAXISMOTION:
					     moveCursor(event.caxis);
					       break;

					}

				}

				updatebackground(deltatime);

				updatecursor(deltatime);


				//cheack cursor over menu button

				menuover=SDL_HasIntersection(&activpos,&memunp);

				SDL_RenderClear(rend);
				//draw imagebackground1
				SDL_RenderCopy(rend, bkgd1, NULL, &bkgd1Pos);
				SDL_RenderCopy(rend, bkgd2, NULL, &bkgd2Pos);
				SDL_RenderCopy(rend, title, NULL, &titlep);
				SDL_RenderCopy(rend, ititle, NULL, &ititlep);

				if(menuover)
				{

					SDL_RenderCopy(rend, memo, NULL, &memunp);

				}else
				{

				SDL_RenderCopy(rend, memun, NULL, &memunp);//menu overstate memuo
				}



				SDL_RenderCopy(rend, cur, NULL, &curpos);
				SDL_RenderPresent(rend);

			}
			break;//end instructions case

		case Playone:

			play1 = true;



			while (play1)
			{
				thistime = SDL_GetTicks();
				deltatime = (float)(thistime - lasttime) / 1000;
				lasttime = thistime;
				//cheack for input events
				if (SDL_PollEvent(&event))
				{
					//check to see if the sdl window is closed player hits x in window
					if (event.type == SDL_QUIT)
					{
						quit = true;
						play1 = false;
						break;
					}
					switch (event.type)
					{

					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0)
						{
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X)
							{
								play1 = false;
								gamestate = win;
							}
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
							{
								play1 = false;
								gamestate = lose;
							}
							Player1.oncontrollerbutton(event.cbutton);

						}
						break;
					case SDL_CONTROLLERAXISMOTION:
						Player1.oncontrolleraxis(event.caxis);
						break;
					}
				}

				updatebackground(deltatime);
				//updateplayer
				   Player1.update(deltatime);


				SDL_RenderClear(rend);
				//draw imagebackground1
				SDL_RenderCopy(rend, bkgd1, NULL, &bkgd1Pos);
				SDL_RenderCopy(rend, bkgd2, NULL, &bkgd2Pos);
				//SDL_RenderCopy(rend, title, NULL, &titlep);
				//SDL_RenderCopy(rend, ptitle, NULL, &ptitlep);

                      Player1.draw(rend);


				//SDL_RenderCopy(rend, cur, NULL, &curpos);
				SDL_RenderPresent(rend);

			}
			break;//end play1


		case play2:

			players2 = true;

			

			while (players2)
			{
				thistime = SDL_GetTicks();
				deltatime = (float)(thistime - lasttime) / 1000;
				lasttime = thistime;
				//cheack for input events
				if (SDL_PollEvent(&event))
				{
					//check to see if the sdl window is closed player hits x in window
					if (event.type == SDL_QUIT)
					{
						quit = true;
						players2 = false;
						break;
					}
					switch (event.type)
					{

					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0 || event.cdevice.which == 1)
						{
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_X)
							{
								players2 = false;
								gamestate = win;
							}
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
							{
								players2 = false;
								gamestate = lose;
							}
							Player1.oncontrollerbutton(event.cbutton);
							Player2.oncontrollerbutton(event.cbutton);
						}
						break;
					case SDL_CONTROLLERAXISMOTION:

						Player1.oncontrolleraxis(event.caxis);
						Player2.oncontrolleraxis(event.caxis);

						break;
					}
				}
				updatebackground(deltatime);
				Player1.update(deltatime);
				Player2.update(deltatime);


				SDL_RenderClear(rend);
				SDL_RenderCopy(rend, bkgd1, NULL, &bkgd1Pos);
				SDL_RenderCopy(rend, bkgd2, NULL, &bkgd2Pos);
				//SDL_RenderCopy(rend, title, NULL, &titlep);
				//SDL_RenderCopy(rend, p2title, NULL, &ptitlep);

				Player1.draw(rend);
				Player2.draw(rend);


				//SDL_RenderCopy(rend, cur, NULL, &curpos);
				SDL_RenderPresent(rend);

			}
			break;//end play2




		case win:

			Win = true;

			cout << "the game state is win" << endl;
			cout << "press A button for menu" << endl;
			cout << "press B for quit" << endl;
			cout << endl;

			while (Win)
			{
				thistime = SDL_GetTicks();
				deltatime = (float)(thistime - lasttime) / 1000;
				lasttime = thistime;
				//cheack for input events
				if (SDL_PollEvent(&event))
				{
					//check to see if the sdl window is closed player hits x in window
					if (event.type == SDL_QUIT)
					{
						quit = true;
						Win = false;
						break;
					}
					switch (event.type)
					{

					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0)
						{
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
							{

							  if(play1over)
							  {
								  Win = false;
								gamestate = Playone;
								play1over=false;

							}
							  if(menuover)
							  {
								  Win=false;
								  gamestate=MENU;
								  menuover=false;
							  }

						}
						break;


					case SDL_CONTROLLERAXISMOTION:
					     moveCursor(event.caxis);
					       break;

					}
				}

				}
				updatebackground(deltatime);

				updatecursor(deltatime);

				menuover=SDL_HasIntersection(&activpos,&memunp);
				play1over=SDL_HasIntersection(&activpos,&playnp);



				SDL_RenderClear(rend);
				SDL_RenderCopy(rend, bkgd1, NULL, &bkgd1Pos);
				SDL_RenderCopy(rend, bkgd2, NULL, &bkgd2Pos);
				SDL_RenderCopy(rend, title, NULL, &titlep);
				SDL_RenderCopy(rend, wtitle, NULL, &ptitlep);
				//playo

				if(menuover)
							{

								SDL_RenderCopy(rend, memo, NULL, &memunp);

							}else
							{

							SDL_RenderCopy(rend, memun, NULL, &memunp);//menu overstate memuo
							}

				if(play1over)
				{
					SDL_RenderCopy(rend, playo, NULL, &playnp);
				}else
				{
					SDL_RenderCopy(rend, playn, NULL, &playnp);
				}



				SDL_RenderCopy(rend, cur, NULL, &curpos);
				SDL_RenderPresent(rend);

			}
			break;//end play2



		case lose:

			Lose = true;

			cout << "the game state is lose" << endl;

			cout << endl;

			while (Lose)
			{

				thistime = SDL_GetTicks();
				deltatime = (float)(thistime - lasttime) / 1000;
				lasttime = thistime;
				//cheack for input events
				if (SDL_PollEvent(&event))
				{
					//check to see if the sdl window is closed player hits x in window
					if (event.type == SDL_QUIT)
					{
						quit = true;
						Lose = false;
						break;
					}
					switch (event.type)
					{

					case SDL_CONTROLLERBUTTONDOWN:

						if (event.cdevice.which == 0)
						{
							if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
							{
								if(playaginover)
														  {
															  Lose = false;
															  playaginover = false;
															gamestate = Playone;
															

														}
														  if(menuover)
														  {
															  
															  Lose =false;
															  menuover = false;
															  gamestate=MENU;
															  
														  }

							}

						}
						break;
					case SDL_CONTROLLERAXISMOTION:
										     moveCursor(event.caxis);
										       break;
					}
				}

				updatebackground(deltatime);

				updatecursor(deltatime);

								menuover=SDL_HasIntersection(&activpos,&memunp);
								playaginover =SDL_HasIntersection(&activpos,&playnp);



				SDL_RenderClear(rend);
				SDL_RenderCopy(rend, bkgd1, NULL, &bkgd1Pos);
				SDL_RenderCopy(rend, bkgd2, NULL, &bkgd2Pos);
				SDL_RenderCopy(rend, title, NULL, &titlep);
				SDL_RenderCopy(rend, ltitle, NULL, &ptitlep);

				if(menuover)
											{

												SDL_RenderCopy(rend, memo, NULL, &memunp);

											}else
											{

											SDL_RenderCopy(rend, memun, NULL, &memunp);//menu overstate memuo
											}

								if(playaginover)
								{
									SDL_RenderCopy(rend, playo, NULL, &playnp);
								}else
								{
									SDL_RenderCopy(rend, playn, NULL, &playnp);
								}




				SDL_RenderCopy(rend, cur, NULL, &curpos);
				SDL_RenderPresent(rend);

			}
			break;



		}
	}


	// SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}





