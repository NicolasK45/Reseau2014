#include <iostream>
#include <map>

using namespace std;


class perso{
  int posx, posy;
  string name;
  map<string,int> inventory;
  int hp, maxhp;
  int damage;
public:
  perso(){
    name="";
    maxhp=0;
    hp=0;
    damage=0;
    posx=0;
    posy=0;
  }

  perso(string name,int maxhp,int damage, int x, int y){
    this->name=name;
    this->maxhp=maxhp;
    this->hp=maxhp;
    this->damage=damage;
    posx=x;
    posy=y;
  }

  int get_posx()const{
    return posx;
  }

  int get_posy()const{
    return posy;
  }

  string get_name()const{
    return name;
  }

  int get_hp()const{
    return hp;
  }

  int get_maxhp()const{
    return maxhp;
  }

  int get_damage()const{
    return damage;
  }

  void set_inventory(string ob, int number){
    inventory[ob]=number;
  }

  void set_posx(int new_posx){
    posx=new_posx;
  }

  void set_posy(int new_posy){
    posx=new_posy;
  }

  void set_hp(int new_hp){
    hp=new_hp;
  }

  bool use_inventory(string ob){
    map<string,int> iterator it;
    it=inventory.find(ob);
    if(iter!=inventory.end()){
      if(iter->second > 0){
	iter->second--;
	return true;
      }
    }
    return false;
  }
};


class warrior:public perso{
public:
  warrior(){
    perso();
  }

  warrior(string name, int maxhp, int damage, int x, int y){
    perso(name, maxhp, damage, x, y);
    set_inventory("breakdoor", 5);
    set_inventory("shock", 3);
  }
};
 

int main(){
  warrior c("Nico", 10, 3, 0, 0);
  return 0;
}
