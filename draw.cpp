#include <iostream>
#include <chrono>
#include <thread>
#include "draw.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;

const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};
const SDL_Color GAY_COLOR = {148, 170, 214};

const string HINH_NEN           = "nen.png";
const string FONT_CHU           = "font-times-new-roman.ttf";
const string GO                 = "GO.png";
const string DAY                = "day.png";
const string DAU                = "dau.png";
const string THAN               = "than.png";
const string PHAI               = "phai.png";
const string TRAI               = "TRAI.png";

bool check1(SDL_Rect a,SDL_Point mouse){
    if(mouse.x > a.x && mouse.x <a.w +a.x && mouse.y > a.y && mouse.y < a.h + a.y) return true;
    return false;
}

bool check(SDL_Rect a,SDL_Point oldMouse,SDL_Point newMouse){
    if((check1(a,oldMouse)==true && check1(a,newMouse))==true)return true;
    else return false;
}

void clearScreen(SDL_Renderer* renderer) {
    setRenderColor(renderer,BLACK_COLOR);
    SDL_RenderClear(renderer);
}

void renderGame(SDL_Renderer* renderer,const string& guessedWord, const string& badGuesses)
{
	clearScreen(renderer);

	int badGuessCount = badGuesses.length();

    SDL_Rect go1,go2,go3,dayRect,dauRect,ThanRect,tayPhaiRect,tayTraiRect,chanPhaiRect,chanTraiRect;

    go1.x = 64;
    go1.y = 261;
    go1.w = 200;
    go1.h = 18;

    go3.x = 147;
    go3.y = 78;
    go3.w = 250;
    go3.h = 18;

    go2.x = 147;
    go2.y = 78;
    go2.w = 18;
    go2.h = 200;

    dayRect.x = 309;
    dayRect.y = 96;
    dayRect.w = 74;
    dayRect.h = 74;

    dauRect.x = 325;
    dauRect.y = 133;
    dauRect.w = 43;
    dauRect.h = 44;

    ThanRect.x = 313;
    ThanRect.y = 160;
    ThanRect.w = 80;
    ThanRect.h = 83;

    tayPhaiRect.x = 311;
    tayPhaiRect.y = 153;
    tayPhaiRect.w = 58;
    tayPhaiRect.h = 61;

    tayTraiRect.x = 331;
    tayTraiRect.y = 153;
    tayTraiRect.w = 58;
    tayTraiRect.h = 61;

    chanPhaiRect.x = 308;
    chanPhaiRect.y = 197;
    chanPhaiRect.w = 64;
    chanPhaiRect.h = 67;

    chanTraiRect.x = 331;
    chanTraiRect.y = 200;
    chanTraiRect.w = 58;
    chanTraiRect.h = 61;


    TTF_Font* font = TTF_OpenFont(FONT_CHU.c_str(),30);

    string msg1 = "Secret word: " + guessedWord;
    string msg2 = "";
    if(badGuessCount >= 1){
        msg2 = "You've made " + to_string(badGuessCount) + " wrong " + (badGuessCount == 1 ? "guess" : "guesses") + ": " + badGuesses ;
    }



    SDL_Surface* textSurface1 = TTF_RenderText_Solid(font,msg1.c_str(),BLUE_COLOR);
    SDL_Surface* textSurface2 = (msg2 == "" ? nullptr:TTF_RenderText_Solid(font,msg2.c_str(),BLUE_COLOR));

    SDL_Surface* loadBkg = IMG_Load(HINH_NEN.c_str());
    SDL_Surface* loadGo = IMG_Load(GO.c_str());
    SDL_Surface* loadDay = IMG_Load(DAY.c_str());
    SDL_Surface* loadDau = IMG_Load(DAU.c_str());
    SDL_Surface* loadThan = IMG_Load(THAN.c_str());
    SDL_Surface* loadTayPhai = IMG_Load(PHAI.c_str());
    SDL_Surface* loadTayTrai = IMG_Load(TRAI.c_str());
    SDL_Surface* loadChanPhai = IMG_Load(PHAI.c_str());
    SDL_Surface* loadChanTrai = IMG_Load(TRAI.c_str());

    SDL_Texture* hinhnen = SDL_CreateTextureFromSurface(renderer,loadBkg);
    SDL_Texture* Go = SDL_CreateTextureFromSurface(renderer,loadGo);
    SDL_Texture* day = SDL_CreateTextureFromSurface(renderer,loadDay);
    SDL_Texture* dau = SDL_CreateTextureFromSurface(renderer,loadDau);
    SDL_Texture* than = SDL_CreateTextureFromSurface(renderer,loadThan);
    SDL_Texture* tayPhai = SDL_CreateTextureFromSurface(renderer,loadTayPhai);
    SDL_Texture* tayTrai = SDL_CreateTextureFromSurface(renderer,loadTayTrai);
    SDL_Texture* chanPhai = SDL_CreateTextureFromSurface(renderer,loadChanPhai);
    SDL_Texture* chanTrai = SDL_CreateTextureFromSurface(renderer,loadChanTrai);

    SDL_Texture* text1 = SDL_CreateTextureFromSurface(renderer,textSurface1);
    SDL_Texture* text2 = (textSurface2 == nullptr ? nullptr:SDL_CreateTextureFromSurface(renderer,textSurface2));


    SDL_Rect text1Rect,text2Rect;
    SDL_QueryTexture(text2,nullptr,nullptr,&text2Rect.w,&text2Rect.h);
    SDL_QueryTexture(text1,nullptr,nullptr,&text1Rect.w,&text1Rect.h);


    text2Rect.x = 300;
    text2Rect.y = 400 - text2Rect.h;

    text1Rect.x = 350;
    text1Rect.y = 350 - text1Rect.h;

    SDL_RenderCopy(renderer,hinhnen,nullptr,nullptr);

    switch(badGuessCount){
    case 1:
        SDL_RenderCopy(renderer,Go,nullptr,&go1);
        SDL_RenderCopy(renderer,Go,nullptr,&go2);
        SDL_RenderCopy(renderer,Go,nullptr,&go3);
        SDL_RenderCopy(renderer,day,nullptr,&dayRect);
        break;
    case 2:
        SDL_RenderCopy(renderer,Go,nullptr,&go1);
        SDL_RenderCopy(renderer,Go,nullptr,&go2);
        SDL_RenderCopy(renderer,Go,nullptr,&go3);
        SDL_RenderCopy(renderer,day,nullptr,&dayRect);
        SDL_RenderCopy(renderer,dau,nullptr,&dauRect);
        break;
    case 3:
        SDL_RenderCopy(renderer,Go,nullptr,&go1);
        SDL_RenderCopy(renderer,Go,nullptr,&go2);
        SDL_RenderCopy(renderer,Go,nullptr,&go3);
        SDL_RenderCopy(renderer,day,nullptr,&dayRect);
        SDL_RenderCopy(renderer,dau,nullptr,&dauRect);
        SDL_RenderCopy(renderer,than,nullptr,&ThanRect);
        break;
    case 4:
        SDL_RenderCopy(renderer,Go,nullptr,&go1);
        SDL_RenderCopy(renderer,Go,nullptr,&go2);
        SDL_RenderCopy(renderer,Go,nullptr,&go3);
        SDL_RenderCopy(renderer,day,nullptr,&dayRect);
        SDL_RenderCopy(renderer,dau,nullptr,&dauRect);
        SDL_RenderCopy(renderer,than,nullptr,&ThanRect);
        SDL_RenderCopy(renderer,tayPhai,nullptr,&tayPhaiRect);
        break;
    case 5:
        SDL_RenderCopy(renderer,Go,nullptr,&go1);
        SDL_RenderCopy(renderer,Go,nullptr,&go2);
        SDL_RenderCopy(renderer,Go,nullptr,&go3);
        SDL_RenderCopy(renderer,day,nullptr,&dayRect);
        SDL_RenderCopy(renderer,dau,nullptr,&dauRect);
        SDL_RenderCopy(renderer,than,nullptr,&ThanRect);
        SDL_RenderCopy(renderer,tayPhai,nullptr,&tayPhaiRect);
        SDL_RenderCopy(renderer,tayTrai,nullptr,&tayTraiRect);
        break;
    case 6:
        SDL_RenderCopy(renderer,Go,nullptr,&go1);
        SDL_RenderCopy(renderer,Go,nullptr,&go2);
        SDL_RenderCopy(renderer,Go,nullptr,&go3);
        SDL_RenderCopy(renderer,day,nullptr,&dayRect);
        SDL_RenderCopy(renderer,dau,nullptr,&dauRect);
        SDL_RenderCopy(renderer,than,nullptr,&ThanRect);
        SDL_RenderCopy(renderer,tayPhai,nullptr,&tayPhaiRect);
        SDL_RenderCopy(renderer,tayTrai,nullptr,&tayTraiRect);
        SDL_RenderCopy(renderer,chanPhai,nullptr,&chanPhaiRect);
        break;
    case 7:
        SDL_RenderCopy(renderer,Go,nullptr,&go1);
        SDL_RenderCopy(renderer,Go,nullptr,&go2);
        SDL_RenderCopy(renderer,Go,nullptr,&go3);
        SDL_RenderCopy(renderer,day,nullptr,&dayRect);
        SDL_RenderCopy(renderer,dau,nullptr,&dauRect);
        SDL_RenderCopy(renderer,than,nullptr,&ThanRect);
        SDL_RenderCopy(renderer,tayPhai,nullptr,&tayPhaiRect);
        SDL_RenderCopy(renderer,tayTrai,nullptr,&tayTraiRect);
        SDL_RenderCopy(renderer,chanPhai,nullptr,&chanPhaiRect);
        SDL_RenderCopy(renderer,chanTrai,nullptr,&chanTraiRect);
        break;
    }

    SDL_RenderCopy(renderer,text2,nullptr,&text2Rect);
    SDL_RenderCopy(renderer,text1,nullptr,&text1Rect);


    SDL_RenderPresent(renderer);

    TTF_CloseFont(font);

    SDL_FreeSurface(loadBkg);
    SDL_FreeSurface(loadGo);
    SDL_FreeSurface(loadDay);
    SDL_FreeSurface(loadDau);
    SDL_FreeSurface(loadThan);
    SDL_FreeSurface(loadTayPhai);
    SDL_FreeSurface(loadTayTrai);
    SDL_FreeSurface(loadChanPhai);
    SDL_FreeSurface(loadChanTrai);

    SDL_DestroyTexture(hinhnen);
    SDL_DestroyTexture(Go);
    SDL_DestroyTexture(dau);
    SDL_DestroyTexture(than);
    SDL_DestroyTexture(tayPhai);
    SDL_DestroyTexture(tayTrai);
    SDL_DestroyTexture(chanPhai);
    SDL_DestroyTexture(chanTrai);
}


void displayFinalResult(SDL_Renderer* renderer,bool won, const string& word) {
    clearScreen(renderer);
    string result = won ? "Congratulations! You win!" : "You lost.";
    string text = "The correct word is " + word;
    string text4 = "Press any key to continue";
    TTF_Font* font = TTF_OpenFont(FONT_CHU.c_str(),30);

    SDL_Rect text1Rect,text2Rect,text3Rect;

    text1Rect.x = 265;
    text1Rect.y = 155;
    text1Rect.w = 270;
    text1Rect.h = 70;

    text2Rect.x = 265;
    text2Rect.y = 225;
    text2Rect.w = 270;
    text2Rect.h = 70;

    text3Rect.x = 265;
    text3Rect.y = 325;
    text3Rect.w = 270;
    text3Rect.h = 70;


    SDL_Surface* hinhNen = IMG_Load(HINH_NEN.c_str());
    SDL_Surface* text1Surface = TTF_RenderText_Solid(font,result.c_str(),BLUE_COLOR);
    SDL_Surface* text2Surface = TTF_RenderText_Solid(font,text.c_str(),BLUE_COLOR);
    SDL_Surface* text3Surface = TTF_RenderText_Solid(font,text4.c_str(),BLUE_COLOR);


    SDL_Texture* nen = SDL_CreateTextureFromSurface(renderer,hinhNen);
    SDL_Texture* text1 = SDL_CreateTextureFromSurface(renderer,text1Surface);
    SDL_Texture* text2 = SDL_CreateTextureFromSurface(renderer,text2Surface);
    SDL_Texture* text3 = SDL_CreateTextureFromSurface(renderer,text3Surface);

    int w,h;

    SDL_QueryTexture(text1,nullptr,nullptr,&w,&h);
    text1Rect.x += (text1Rect.w - w)/2;
    text1Rect.y += (text1Rect.h - h)/2;
    text1Rect.h = h;
    text1Rect.w = w;

    SDL_QueryTexture(text2,nullptr,nullptr,&w,&h);
    text2Rect.x += (text2Rect.w - w)/2;
    text2Rect.y += (text2Rect.h - h)/2;
    text2Rect.h = h;
    text2Rect.w = w;

    SDL_QueryTexture(text3,nullptr,nullptr,&w,&h);
    text3Rect.x += (text3Rect.w - w)/2;
    text3Rect.y += (text3Rect.h - h)/2;
    text3Rect.h = h;
    text3Rect.w = w;

    SDL_RenderCopy(renderer,nen,nullptr,nullptr);
    SDL_RenderCopy(renderer,text1,nullptr,&text1Rect);
    SDL_RenderCopy(renderer,text2,nullptr,&text2Rect);
    SDL_RenderCopy(renderer,text3,nullptr,&text3Rect);


    SDL_RenderPresent(renderer);

    TTF_CloseFont(font);
    SDL_FreeSurface(text1Surface);
    SDL_FreeSurface(text2Surface);
    SDL_FreeSurface(text3Surface);
    SDL_FreeSurface(hinhNen);

    SDL_DestroyTexture(text1);
    SDL_DestroyTexture(text2);
    SDL_DestroyTexture(text3);
    SDL_DestroyTexture(nen);
}


bool trangChu(SDL_Renderer* renderer,bool choiLai){
    //return true;
    bool res = false;
    bool chay = true;
    clearScreen(renderer);

    SDL_Surface* hinhnen = IMG_Load(HINH_NEN.c_str());

    SDL_Texture* nen =  SDL_CreateTextureFromSurface(renderer,hinhnen);

    SDL_RenderCopy(renderer,nen,nullptr,nullptr);
//-----------------------------
    SDL_Event e;
    setRenderColor(renderer,GAY_COLOR);
    if(choiLai == false){
        ///home
        SDL_Rect tenGame,choi,thoat;
        SDL_Point oldMouse,newMouse;

        tenGame.x = 112;
        tenGame.y = 30;
        tenGame.w = 576;
        tenGame.h = 160;

        choi.x = 309;
        choi.y = 270;
        choi.w = 180;
        choi.h = 49;

        thoat.x = 309;
        thoat.y = 328;
        thoat.w = 180;
        thoat.h = 49;

        TTF_Font* font = TTF_OpenFont(FONT_CHU.c_str(),200);
        SDL_Surface* tenGameSurface = TTF_RenderText_Solid(font,"HANG MAN",BLUE_COLOR);
        TTF_CloseFont(font);

        font = TTF_OpenFont(FONT_CHU.c_str(),50);
        SDL_Surface* choiSurface = TTF_RenderText_Solid(font,"PLAY",BLUE_COLOR);
        SDL_Surface* thoatSurface = TTF_RenderText_Solid(font,"EXIT",BLUE_COLOR);

        SDL_Texture* tenGameTexture = SDL_CreateTextureFromSurface(renderer,tenGameSurface);
        SDL_Texture* choiTexture = SDL_CreateTextureFromSurface(renderer,choiSurface);
        SDL_Texture* thoatTexture = SDL_CreateTextureFromSurface(renderer,thoatSurface);

        SDL_RenderFillRect(renderer,&choi);
        SDL_RenderFillRect(renderer,&thoat);

        int w,h;
        SDL_QueryTexture(choiTexture,nullptr,nullptr,&w,&h);

        choi.x += (choi.w - w)/2;
        choi.y -= (choi.h - h)/2;
        choi.w = w;
        choi.h = h;

        SDL_QueryTexture(thoatTexture,nullptr,nullptr,&w,&h);
        thoat.x += (thoat.w - w)/2;
        thoat.y -= (thoat.h - h)/2;
        thoat.w = w;
        thoat.h = h;

        SDL_RenderCopy(renderer,tenGameTexture,nullptr,&tenGame);
        SDL_RenderCopy(renderer,choiTexture,nullptr,&choi);
        SDL_RenderCopy(renderer,thoatTexture,nullptr,&thoat);


        SDL_FreeSurface(tenGameSurface);
        SDL_FreeSurface(thoatSurface);
        SDL_FreeSurface(choiSurface);
        SDL_DestroyTexture(tenGameTexture);
        SDL_DestroyTexture(choiTexture);
        SDL_DestroyTexture(thoatTexture);
        TTF_CloseFont(font);

        SDL_RenderPresent(renderer);

        choi.x = 309;
        choi.y = 270;
        choi.w = 180;
        choi.h = 49;

        thoat.x = 309;
        thoat.y = 328;
        thoat.w = 180;
        thoat.h = 49;

        while(chay){
            while(SDL_PollEvent(&e) != 0){
                switch(e.type){
                case SDL_QUIT:
                    res = false;
                    chay = false;
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE){
                        res = false;
                        chay = false;
                        break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    newMouse.x = e.motion.x;
                    newMouse.y = e.motion.y;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(e.button.button == SDL_BUTTON_LEFT){
                        oldMouse = newMouse;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(e.button.button == SDL_BUTTON_LEFT){
                        if(check(choi,oldMouse,newMouse))
                            chay = false,res = true;

                        if(check(thoat,oldMouse,newMouse))
                            chay = false,res = false;
                    }
                }
            }
        }

    }
    else{
        SDL_Rect tenGame,choi,thoat;
        SDL_Point oldMouse,newMouse;

        tenGame.x = 112;
        tenGame.y = 30;
        tenGame.w = 576;
        tenGame.h = 160;

        choi.x = 309;
        choi.y = 270;
        choi.w = 180;
        choi.h = 49;

        thoat.x = 309;
        thoat.y = 328;
        thoat.w = 180;
        thoat.h = 49;

        TTF_Font* font = TTF_OpenFont(FONT_CHU.c_str(),200);
        SDL_Surface* tenGameSurface = TTF_RenderText_Solid(font,"RESTART?",BLUE_COLOR);
        TTF_CloseFont(font);

        font = TTF_OpenFont(FONT_CHU.c_str(),50);
        SDL_Surface* choiSurface = TTF_RenderText_Solid(font,"YES",BLUE_COLOR);
        SDL_Surface* thoatSurface = TTF_RenderText_Solid(font,"NO",BLUE_COLOR);

        SDL_Texture* tenGameTexture = SDL_CreateTextureFromSurface(renderer,tenGameSurface);
        SDL_Texture* choiTexture = SDL_CreateTextureFromSurface(renderer,choiSurface);
        SDL_Texture* thoatTexture = SDL_CreateTextureFromSurface(renderer,thoatSurface);

        SDL_RenderFillRect(renderer,&choi);
        SDL_RenderFillRect(renderer,&thoat);

        int w,h;
        SDL_QueryTexture(choiTexture,nullptr,nullptr,&w,&h);

        choi.x += (choi.w - w)/2;
        choi.y -= (choi.h - h)/2;
        choi.w = w;
        choi.h = h;
        SDL_QueryTexture(thoatTexture,nullptr,nullptr,&w,&h);


        thoat.x += (thoat.w - w)/2;
        thoat.y -= (thoat.h - h)/2;
        thoat.w = w;
        thoat.h = h;

        SDL_RenderCopy(renderer,tenGameTexture,nullptr,&tenGame);
        SDL_RenderCopy(renderer,choiTexture,nullptr,&choi);
        SDL_RenderCopy(renderer,thoatTexture,nullptr,&thoat);


        SDL_FreeSurface(tenGameSurface);
        SDL_FreeSurface(thoatSurface);
        SDL_FreeSurface(choiSurface);
        SDL_DestroyTexture(tenGameTexture);
        SDL_DestroyTexture(choiTexture);
        SDL_DestroyTexture(thoatTexture);
        TTF_CloseFont(font);

        SDL_RenderPresent(renderer);

        choi.x = 309;
        choi.y = 270;
        choi.w = 180;
        choi.h = 49;

        thoat.x = 309;
        thoat.y = 328;
        thoat.w = 180;
        thoat.h = 49;

        while(chay){
            while(SDL_PollEvent(&e)){
                switch(e.type){
                case SDL_QUIT:
                    res = false;
                    chay = false;
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE){
                        res = false;
                        chay = false;
                        break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    newMouse.x = e.motion.x;
                    newMouse.y = e.motion.y;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    oldMouse = newMouse;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(check(choi,oldMouse,newMouse))
                        chay = false,res = true;

                    if(check(thoat,oldMouse,newMouse))
                        chay = false,res = false;
                }
            }
        }
    }

    SDL_FreeSurface(hinhnen);

    SDL_DestroyTexture(nen);

    return res;
}


void setRenderColor(SDL_Renderer* renderer,SDL_Color cl){
    SDL_SetRenderDrawColor(renderer,cl.r,cl.g,cl.b,cl.a);
}
