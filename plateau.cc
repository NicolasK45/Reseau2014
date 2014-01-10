#include <iostream>
#include <cstdlib>
#include <ctime>
#include "case.cc"

class plateau{
private:
   // perso players[4];
    cases c[10][10];
    int sortie;
public:
    plateau(){
        sortie=rand()%10;
  //      players=joueurs;
    }
    cases getcase(int i,int j){return c[i][j];}
    bool open_path(int posx,int posy,string direction){
        if (direction=="north"){
            return c[posx][posy].open("north")&&c[posx][posy-1].open("south");
        }
        if (direction=="south"){
            return c[posx][posy].open("south")&&c[posx][posy+1].open("north");
        }
        if (direction=="east"){
            return c[posx][posy].open("east")&&c[posx+1][posy].open("west");
        }
        if (direction=="west"){
            return c[posx][posy].open("west")&&c[posx-1][posy].open("east");
        }
    }
    int getsortie(){return sortie;}
    void destroywall(int posx,int posy,string direction){
        if (direction=="north"){
            c[posx][posy].destroy("north");
            c[posx][posy-1].destroy("south");
        }
        if (direction=="south"){
            c[posx][posy].destroy("south");
            c[posx][posy+1].destroy("north");
        }
        if (direction=="east"){
            c[posx][posy].destroy("east");
            c[posx+1][posy].destroy("west");
        }
        if (direction=="west"){
            c[posx][posy].destroy("west");
            c[posx-1][posy].destroy("east");
        }
    }

 //   void bouger(int nump, string direction){
   //     if (openpath(player[nump].getposx(),player[nump].getposy(),direction)){
     //       if (direction=="north"){
       //         player[nump].setposy(player[nump].getposy()-1);
         //   }
           // if(direction=="south"){
             //   player[nump].setposy(player[nump].getposy()+1);
  //          }
//        }

   // }
};
