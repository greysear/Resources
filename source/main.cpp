/*
 main.cpp
 *
 *  Created on: Jan 21, 2016
 *      Author: eugeneorr
 */
#if defined(_WIN32)||(_WIN64)

#include "SDL.h"

#endif

#if defined(__APPLE__)

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#endif

#if defined(__linux__)

#include "SDL2/SDL.h"

#endif



#include <stdio.h>
#include <iostream>
using namespace std;
float deltatime=0.0;
int thistime=0;
int lasttime;

   //set speed
   int backspeed=100;


     //set speed
     int backspeed2=100;


//sdl rect pos bg1 and 2

SDL_Rect bkgd1Pos,bkgd2Pos;
///background temp var
float bg1pos_x=0,bg1pos_y=0;
float bg2pos_x=0,bg2pos_y=-768;
//move background
void updatebackground()
{
	//update background one

			 bg1pos_y +=(backspeed*1)*deltatime;

			 //set the new back ground one pos
			 bkgd1Pos.y= (int)( bg1pos_y + 0.5f);

			 //reset when off bottom the bottom of the screen
			 if(bkgd1Pos.y>=768)
			 {
				bkgd1Pos.y=-768;
				bg1pos_y=bkgd1Pos.y;


			 }

			 bg2pos_y +=(backspeed2*1)*deltatime;

					 //set the new back ground one pos
					 bkgd2Pos.y=(int)( bg2pos_y+0.5f);

					 //reset when off bottom the bottom of the screen
					 if(bkgd2Pos.y>=768)
					 {
						bkgd2Pos.y=-768;
						bg2pos_y=bkgd2Pos.y;


					 }

}





int main(int argc, char* argv[]) {




#if defined(_WIN32)||(_WIN64)

cout<< "Running on windows  "<<endl;

#endif

#if defined(__APPLE__)

cout<<"running on mac"<<endl;
//get current working dir
string s_cwd(getcwd(NULL,0));

//create string lincing mac image folder

string s_cwd_images = s_cwd +"/Resources/images";
//test
cout<<s_cwd_images<<endl;

#endif

#if defined(__linux__)

cout<<"running on linux"<<endl;
cout<<"effectivly ran on linux"<<endl;

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
    SDL_Renderer *rend=NULL;

    //create the renderer
    rend=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    string BKGDpath=s_cwd_images+"/back1.png";
    cout<<BKGDpath<<endl;

    SDL_Surface *surface=IMG_Load(BKGDpath.c_str());

    //create sdl texture
    SDL_Texture *bkgd1;
    //place surface info into the tesxture bkgd1;
    bkgd1=SDL_CreateTextureFromSurface(rend,surface);




    //create backcround2

    string bg2=s_cwd_images+"/back2.png";
             // cout<<curpath<<endl;
    //create surface for cursor
              surface=IMG_Load(bg2.c_str());


    //create sdl texture
       SDL_Texture *bkgd2;
       //place surface info into the tesxture bkgd2;
       bkgd2=SDL_CreateTextureFromSurface(rend,surface);
       //freee the surface
      // SDL_FreeSurface(surface);



     //  SDL_Rect bkgd2Pos;
        //set xywand h for rect
        bkgd2Pos.x=0;
        bkgd2Pos.y=-768;
        bkgd2Pos.w=1024;
        bkgd2Pos.h=768;




    //create a rectangle xywh

    //SDL_Rect bkgd1Pos;
    //set xywand h for rect
    bkgd1Pos.x=0;
    bkgd1Pos.y=0;
    bkgd1Pos.w=1024;
    bkgd1Pos.h=768;





      //load path to cursor

      string curpath=s_cwd_images+"/cursor.png";
          cout<<curpath<<endl;
//create surface for cursor
          surface=IMG_Load(curpath.c_str());

          //create sdl texture
          SDL_Texture *cur;
          //place surface info into the texture for cursor;
          cur=SDL_CreateTextureFromSurface(rend,surface);

          SDL_FreeSurface(surface);

          SDL_Rect curpos;
          curpos.x=100;
          curpos.y=100;
          curpos.w=50;
          curpos.h=50;


///////***********menu start********////////////////
     //******titles**********////////
          string titl=s_cwd_images+"/title.png";
                      // cout<<curpath<<endl;
             //create surface for cursor
                       surface=IMG_Load(titl.c_str());


             //create sdl texture
                SDL_Texture *title;
                //place surface info into the tesxture bkgd2;
                title=SDL_CreateTextureFromSurface(rend,surface);
                SDL_Rect titlep;
                         titlep.x=0;
                         titlep.y=0;
                         titlep.w=1024;
                         titlep.h=200;

                         SDL_FreeSurface(surface);
                         /////*********title ends///


                         ///******play one button*****/////

                         string p1b=s_cwd_images+"/playonenorm.png";
                                              // cout<<curpath<<endl;
                                     //create surface for cursor
                                               surface=IMG_Load(p1b.c_str());


                                     //create sdl texture
                                        SDL_Texture *p1bb;
                                        //place surface info into the tesxture bkgd2;
                                        p1bb=SDL_CreateTextureFromSurface(rend,surface);

                                        SDL_Rect p1bp;
                                                 p1bp.x=150;
                                                 p1bp.y=300;
                                                 p1bp.w=200;
                                                 p1bp.h=100;

                                                 SDL_FreeSurface(surface);
                                                 ///play one over state
                      string p1bo=s_cwd_images+"/olayeroneover.png";
                                                                                              // cout<<curpath<<endl;
                                                                                     //create surface for cursor
                     surface=IMG_Load(p1bo.c_str());


                                                                                     //create sdl texture
             SDL_Texture *p1bbo;
                                                                                        //place surface info into the tesxture bkgd2;
         p1bbo=SDL_CreateTextureFromSurface(rend,surface);

                                                                                  //      SDL_Rect p1bp;
                                                                                        //         p1bp.x=150;
                                                                                         //        p1bp.y=300;
                                                                                         //        p1bp.w=200;
                                                                                          //       p1bp.h=100;

              SDL_FreeSurface(surface);




                         ////****play one button ends******//////

     //********************play two button begins***************************/////////////////////////////////

        string p2b=s_cwd_images+"/twoplayernorm.png";

          surface=IMG_Load(p2b.c_str());


                SDL_Texture *p2bb;

        p2bb=SDL_CreateTextureFromSurface(rend,surface);

       SDL_Rect p2bp;
     p2bp.x=150;
     p2bp.y=450;
     p2bp.w=200;
     p2bp.h=100;

   SDL_FreeSurface(surface);
         ///play two over state
    string p2bo=s_cwd_images+"/twoplayerover.png";
                                                                                                                                                                                         ;

surface=IMG_Load(p2bo.c_str());

   SDL_Texture *p2bbo;
                   //place surface info into the tesxture bkgd2;
     p2bbo=SDL_CreateTextureFromSurface(rend,surface);

  SDL_FreeSurface(surface);

//end play two over button


  ////////********instructions  button******************//////////////////

//instruct normal
  string ins=s_cwd_images+"/instructnorm.png";

      surface=IMG_Load(ins.c_str());


            SDL_Texture *insn;

    insn=SDL_CreateTextureFromSurface(rend,surface);

   SDL_Rect insnp;
 insnp.x=500;
 insnp.y=300;
 insnp.w=200;
 insnp.h=100;

SDL_FreeSurface(surface);
     ///instruct over
string ino=s_cwd_images+"/instructover.png";
                                                                                                                                                                                     ;

surface=IMG_Load(ino.c_str());

SDL_Texture *inso;
               //place surface info into the tesxture bkgd2;
 inso=SDL_CreateTextureFromSurface(rend,surface);

SDL_FreeSurface(surface);







  //////////***********instructions button end*********************///////


/////*********quit button**********//////////////////////




//quit normal
  string quitn=s_cwd_images+"/quitnorm.png";

      surface=IMG_Load(quitn.c_str());


            SDL_Texture *qn;

    qn=SDL_CreateTextureFromSurface(rend,surface);

   SDL_Rect qnp;
 qnp.x=500;
 qnp.y=450;
 qnp.w=200;
 qnp.h=100;

SDL_FreeSurface(surface);
     ///quit  over
string quito=s_cwd_images+"/quitover.png";
                                                                                                                                                                                     ;

surface=IMG_Load(quito.c_str());

SDL_Texture *qo;
               //place surface info into the tesxture bkgd2;
 qo=SDL_CreateTextureFromSurface(rend,surface);

SDL_FreeSurface(surface);





/////********quit button ends***********//////




	//set up game controller
	SDL_GameController* gGameController=NULL;

	//****** open game controller up
	gGameController=SDL_GameControllerOpen(0);
	//turn on game controller events
	SDL_GameControllerEventState(SDL_ENABLE);

	//SDL event to handle input

	SDL_Event event;
	//***set up variable for game states
	enum GameState{MENU,instruct,Playone,play2,win,lose};

	//set up initial state
	GameState gamestate=MENU;
	//bool values to controll movement through states
	bool menu,instruction,play1,players2,Win,Lose,quit;



	//Fill the surface white
	///SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 42, 254 ) );

	//Update the surface
	//SDL_UpdateWindowSurface( window );

    // The window is open: could enter program loop here (see SDL_PollEvent())
	while(!quit)
	{
		switch(gamestate)
		{
		case MENU:

			menu=true;

			cout<<"the game state is menu"<<endl;
			cout<<"press A button for instructions"<<endl;
			cout<<" B for one player"<<endl;
			cout<<" x button for 2 player"<<endl;
			cout<<" y button for quit"<<endl;

			while (menu)
			{



				//cheack for input events

				thistime=SDL_GetTicks();
				deltatime=(float)(thistime-lasttime)/1000;
				lasttime=thistime;
				//cheack for input events
				if(SDL_PollEvent(&event))
				{
					//check to see if the sdl window is closed player hits x in window
					if(event.type==SDL_QUIT)
					{
						quit=true;
						menu=false;
						break;
					}
					switch(event.type)
					{

					case SDL_CONTROLLERBUTTONDOWN:

						if(event.cdevice.which==0)
						{
							if(event.cbutton.button==SDL_CONTROLLER_BUTTON_A)
							{
								menu=false;
								gamestate=instruct;
							}
							if(event.cbutton.button==SDL_CONTROLLER_BUTTON_B)
														{
															menu=false;
															gamestate=Playone;
														}
							if(event.cbutton.button==SDL_CONTROLLER_BUTTON_X)
														{
															menu=false;
															gamestate=play2;
														}
							if(event.cbutton.button==SDL_CONTROLLER_BUTTON_Y)
														{
															menu=false;
															quit=true;
														}
						}
						break;
					}
				}

				updatebackground();





				SDL_RenderClear(rend);
				//draw imagebackground1
				SDL_RenderCopy(rend,bkgd1,NULL,&bkgd1Pos);
				SDL_RenderCopy(rend,bkgd2,NULL,&bkgd2Pos);
				SDL_RenderCopy(rend,title,NULL,&titlep);
				SDL_RenderCopy(rend,p1bb,NULL,&p1bp);//play one over state change p1bb to p1bbo
				SDL_RenderCopy(rend,p2bb,NULL,&p2bp);//play two over state change p2bb to p2bbo
				SDL_RenderCopy(rend,insn,NULL,&insnp);//instruct over state is inso
				SDL_RenderCopy(rend,qn,NULL,&qnp);///quit over state is qo not qn


				SDL_RenderCopy(rend,cur,NULL,&curpos);

				SDL_RenderPresent(rend);

			}
			break;

			//case two begins
		case instruct:

					instruction=true;

					cout<<"the game state is insrtructions"<<endl;
					cout<<"press A button for main menu"<<endl;
				cout<<endl;

					while (instruction)
					{
						//cheack for input events
						if(SDL_PollEvent(&event))
						{
							//check to see if the sdl window is closed player hits x in window
							if(event.type==SDL_QUIT)
							{
								quit=true;
								instruction=false;
								break;
							}
							switch(event.type)
							{

							case SDL_CONTROLLERBUTTONDOWN:

								if(event.cdevice.which==0)
								{
									if(event.cbutton.button==SDL_CONTROLLER_BUTTON_A)
									{
										instruction=false;
										gamestate=MENU;
									}

								}
								break;
							}
						}

					}
					break;//end instructions case

		case Playone:

							play1=true;

							cout<<"the game state is play1"<<endl;
							cout<<"press A button for win"<<endl;
							cout<<"press B for lose"<<endl;
						cout<<endl;

							while (play1)
							{
								//cheack for input events
								if(SDL_PollEvent(&event))
								{
									//check to see if the sdl window is closed player hits x in window
									if(event.type==SDL_QUIT)
									{
										quit=true;
										play1=false;
										break;
									}
									switch(event.type)
									{

									case SDL_CONTROLLERBUTTONDOWN:

										if(event.cdevice.which==0)
										{
											if(event.cbutton.button==SDL_CONTROLLER_BUTTON_A)
											{
												play1=false;
												gamestate=win;
											}
											if(event.cbutton.button==SDL_CONTROLLER_BUTTON_B)
																						{
																							play1=false;
																							gamestate=lose;
																						}

										}
										break;
									}
								}

							}
							break;//end play1


		case play2:

							players2=true;

							cout<<"the game state is play2"<<endl;
							cout<<"press A button for win"<<endl;
							cout<<"press B for lose"<<endl;
						cout<<endl;

							while (players2)
							{
								//cheack for input events
								if(SDL_PollEvent(&event))
								{
									//check to see if the sdl window is closed player hits x in window
									if(event.type==SDL_QUIT)
									{
										quit=true;
										players2=false;
										break;
									}
									switch(event.type)
									{

									case SDL_CONTROLLERBUTTONDOWN:

										if(event.cdevice.which==0)
										{
											if(event.cbutton.button==SDL_CONTROLLER_BUTTON_A)
											{
												players2=false;
												gamestate=win;
											}
											if(event.cbutton.button==SDL_CONTROLLER_BUTTON_B)
																						{
																							players2=false;
																							gamestate=lose;
																						}

										}
										break;
									}
								}

							}
							break;//end play2




		case win:

							Win=true;

							cout<<"the game state is win"<<endl;
							cout<<"press A button for menu"<<endl;
							cout<<"press B for quit"<<endl;
						cout<<endl;

							while (Win)
							{
								//cheack for input events
								if(SDL_PollEvent(&event))
								{
									//check to see if the sdl window is closed player hits x in window
									if(event.type==SDL_QUIT)
									{
										quit=true;
										Win=false;
										break;
									}
									switch(event.type)
									{

									case SDL_CONTROLLERBUTTONDOWN:

										if(event.cdevice.which==0)
										{
											if(event.cbutton.button==SDL_CONTROLLER_BUTTON_A)
											{
												Win=false;
												gamestate=MENU;
											}
											if(event.cbutton.button==SDL_CONTROLLER_BUTTON_B)
																						{
																							Win=false;
																							quit=true;
																						}

										}
										break;
									}
								}

							}
							break;//end play2



		case lose:

							Lose=true;

							cout<<"the game state is lose"<<endl;
							cout<<"press A button for menu"<<endl;
							cout<<"press B for quit"<<endl;
						cout<<endl;

							while (Lose)
							{
								//cheack for input events
								if(SDL_PollEvent(&event))
								{
									//check to see if the sdl window is closed player hits x in window
									if(event.type==SDL_QUIT)
									{
										quit=true;
										Lose=false;
										break;
									}
									switch(event.type)
									{

									case SDL_CONTROLLERBUTTONDOWN:

										if(event.cdevice.which==0)
										{
											if(event.cbutton.button==SDL_CONTROLLER_BUTTON_A)
											{
												Lose=false;
												gamestate=MENU;
											}
											if(event.cbutton.button==SDL_CONTROLLER_BUTTON_B)
																						{
																							Lose=false;
																							quit=true;
																						}

										}
										break;
									}
								}

							}
							break;//end play2



		}
	}

  // SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}





