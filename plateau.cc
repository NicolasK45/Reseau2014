#include <iostream>
#include <cstdlib>
#include <ctime>
#include "case.cc"

class plateau{
private:
   perso players[4];
    cases c[10][10];
    int sortie;
    int nbjoueur;
public:
    plateau(){
        sortie=rand()%10;
  //      players=joueurs;
        nbjoueur=0;
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
    
    perso get_player(int i){
        return players[i];
    }

    void bouger(int nump, string direction){
        if (direction=="north"){
            int occ=c[players[nump].get_posx()][players[nump].get_posy()+1].occupant();
            if(occ==-1){
                players[nump].set_posy(players[nump].get_posy()+1);
            }
            else{
                if(players[nump].get_hp()/players[occ].get_damage()>players[occ].get_hp()/players[nump].get_damage()){
                    players[nump].set_hp(players[nump].get_hp()-(players[nump].get_hp()/players[occ].get_damage())*players[occ].get_damage());
                    players[occ].set_hp(players[occ].get_maxhp());
                    players[nump].set_posy(players[nump].get_posy()+1);
                    c[players[nump].get_posx()][players[nump].get_posy()].set_occupant(nump);
                    c[players[nump].get_posx()][players[nump].get_posy()-1].set_occupant(-1);
                    players[occ].set_posy(0);
                    c[players[occ].get_posx()][players[occ].get_posy()].set_occupant(occ);
                }


                if(players[nump].get_hp()/players[occ].get_damage()<players[occ].get_hp()/players[nump].get_damage()){
                    players[occ].set_hp(players[occ].get_hp()-(players[occ].get_hp()/players[nump].get_damage())*players[nump].get_damage());
                    players[nump].set_hp(players[nump].get_maxhp());
                    c[players[nump].get_posx()][players[nump].get_posy()].set_occupant(-1);
                    players[nump].set_posy(0);
                    c[players[nump].get_posx()][players[nump].get_posy()].set_occupant(nump);
                }

                if(players[nump].get_hp()/players[occ].get_damage()==players[occ].get_hp()/players[nump].get_damage()){
                    players[nump].set_hp(players[nump].get_hp()-(players[nump].get_hp()/players[occ].get_damage()-1)*players[occ].get_damage());
                    players[occ].set_hp(players[occ].get_maxhp());
                    players[nump].set_posy(players[nump].get_posy()+1);
                    c[players[nump].get_posx()][players[nump].get_posy()].set_occupant(nump);
                    c[players[nump].get_posx()][players[nump].get_posy()-1].set_occupant(-1);
                    players[occ].set_posy(0);
                    c[players[occ].get_posx()][players[occ].get_posy()].set_occupant(occ);
                }



            }
        }


        if(direction=="south"){
            int occ=c[players[nump].get_posx()][players[nump].get_posy()-1].occupant();
            if(occ==-1){
                players[nump].set_posy(players[nump].get_posy()-1);
            }
            else{
                if(players[nump].get_hp()/players[occ].get_damage()>players[occ].get_hp()/players[nump].get_damage()){
                    players[nump].set_hp(players[nump].get_hp()-(players[nump].get_hp()/players[occ].get_damage())*players[occ].get_damage());
                    players[occ].set_hp(players[occ].get_maxhp());
                    players[nump].set_posy(players[nump].get_posy()-1);
                    c[players[nump].get_posx()][players[nump].get_posy()].set_occupant(nump);
                    c[players[nump].get_posx()][players[nump].get_posy()+1].set_occupant(-1);
                    players[occ].set_posy(0);
                    c[players[occ].get_posx()][players[occ].get_posy()].set_occupant(occ);
                }


                if(players[nump].get_hp()/players[occ].get_damage()<players[occ].get_hp()/players[nump].get_damage()){
                    players[occ].set_hp(players[occ].get_hp()-(players[occ].get_hp()/players[nump].get_damage())*players[nump].get_damage());
                    players[nump].set_hp(players[nump].get_maxhp());
                    c[players[nump].get_posx()][players[nump].get_posy()].set_occupant(-1);
                    players[nump].set_posy(0);
                    c[players[nump].get_posx()][players[nump].get_posy()].set_occupant(nump);
                }

                if(players[nump].get_hp()/players[occ].get_damage()==players[occ].get_hp()/players[nump].get_damage()){
                    players[nump].set_hp(players[nump].get_hp()-(players[nump].get_hp()/players[occ].get_damage()-1)*players[occ].get_damage());
                    players[occ].set_hp(players[occ].get_maxhp());
                    players[nump].set_posy(players[nump].get_posy()-1);
                    c[players[nump].get_posx()][players[nump].get_posy()].set_occupant(nump);
                    c[players[nump].get_posx()][players[nump].get_posy()+1].set_occupant(-1);
                    players[occ].set_posy(0);
                    c[players[occ].get_posx()][players[occ].get_posy()].set_occupant(occ);
                }
            }
        }
        if (direction=="east"){
            int occ=c[players[nump].get_posx()+1][players[nump].get_posy()].occupant();
            if(occ==-1){
                players[nump].set_posx(players[nump].get_posy()+1);
            }
            else{
                if(players[nump].get_hp()/players[occ].get_damage()>players[occ].get_hp()/players[nump].get_damage()){
                    players[nump].set_hp(players[nump].get_hp()-(players[nump].get_hp()/players[occ].get_damage())*players[occ].get_damage());
                    players[occ].set_hp(players[occ].get_maxhp());
                    players[nump].set_posx(players[nump].get_posx()+1);
                    c[players[nump].get_posx()][players[nump].get_posy()].set_occupant(nump);
                    c[players[nump].get_posx()-1][players[nump].get_posy()].set_occupant(-1);
                    players[occ].set_posy(0);
                    c[players[occ].get_posx()][players[occ].get_posy()].set_occupant(occ);
                }


                if(players[nump].get_hp()/players[occ].get_damage()<players[occ].get_hp()/players[nump].get_damage()){
                    players[occ].set_hp(players[occ].get_hp()-(players[occ].get_hp()/players[nump].get_damage())*players[nump].get_damage());
                    players[nump].set_hp(players[nump].get_maxhp());
                    c[players[nump].get_posx()][players[nump].get_posy()].set_occupant(-1);
                    players[nump].set_posy(0);
                    c[players[nump].get_posx()][players[nump].get_posy()].set_occupant(nump);
                }

                if(players[nump].get_hp()/players[occ].get_damage()==players[occ].get_hp()/players[nump].get_damage()){
                    players[nump].set_hp(players[nump].get_hp()-(players[nump].get_hp()/players[occ].get_damage()-1)*players[occ].get_damage());
                    players[occ].set_hp(players[occ].get_maxhp());
                    players[nump].set_posx(players[nump].get_posx()+1);
                    c[players[nump].get_posx()][players[nump].get_posy()].set_occupant(nump);
                    c[players[nump].get_posx()-1][players[nump].get_posy()].set_occupant(-1);
                    players[occ].set_posy(0);
                    c[players[occ].get_posx()][players[occ].get_posy()].set_occupant(occ);
                }
            }
        }
        if(direction=="west"){
            int occ=c[players[nump].get_posx()-1][players[nump].get_posy()].occupant();
            if(occ==-1){
                players[nump].set_posx(players[nump].get_posx()-1);
            }
            else{
                if(players[nump].get_hp()/players[occ].get_damage()>players[occ].get_hp()/players[nump].get_damage()){
                    players[nump].set_hp(players[nump].get_hp()-(players[nump].get_hp()/players[occ].get_damage())*players[occ].get_damage());
                    players[occ].set_hp(players[occ].get_maxhp());
                    players[nump].set_posx(players[nump].get_posx()-1);
                    c[players[nump].get_posx()][players[nump].get_posy()].set_occupant(nump);
                    c[players[nump].get_posx()+1][players[nump].get_posy()].set_occupant(-1);
                    players[occ].set_posy(0);
                    c[players[occ].get_posx()][players[occ].get_posy()].set_occupant(occ);
                }


                if(players[nump].get_hp()/players[occ].get_damage()<players[occ].get_hp()/players[nump].get_damage()){
                    players[occ].set_hp(players[occ].get_hp()-(players[occ].get_hp()/players[nump].get_damage())*players[nump].get_damage());
                    players[nump].set_hp(players[nump].get_maxhp());
                    c[players[nump].get_posx()][players[nump].get_posy()].set_occupant(-1);
                    players[nump].set_posy(0);
                    c[players[nump].get_posx()][players[nump].get_posy()].set_occupant(nump);
                }

                if(players[nump].get_hp()/players[occ].get_damage()==players[occ].get_hp()/players[nump].get_damage()){
                    players[nump].set_hp(players[nump].get_hp()-(players[nump].get_hp()/players[occ].get_damage()-1)*players[occ].get_damage());
                    players[occ].set_hp(players[occ].get_maxhp());
                    players[nump].set_posy(players[nump].get_posy()-1);
                    c[players[nump].get_posx()][players[nump].get_posy()].set_occupant(nump);
                    c[players[nump].get_posx()+1][players[nump].get_posy()].set_occupant(-1);
                    players[occ].set_posy(0);
                    c[players[occ].get_posx()][players[occ].get_posy()].set_occupant(occ);
                }
            }
        }
    }

    bool gagner(int i){
        return players[i].get_posx()==sortie && players[i].get_posy()==9;
    }

    void ajoutplayer(perso joueur){
        players[nbjoueur]=joueur;
        nbjoueur++;
        c[joueur.get_posx()][joueur.get_posy()].set_occupant(nbjoueur);
    }

};