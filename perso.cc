#include <iostream>
#include <map>

using namespace std;


class perso{
  int posx, posy;
  string name;
  string class_perso;
  //map<string,int> inventory;
  int hp;
  int maxhp;
  int damage;
public:
  perso(){
    name="nameless";
    class_perso="aucune";
    maxhp=0;
    hp=0;
    damage=0;
    posx=0;
    posy=0;
  }

  /*perso(string name,string class_perso,int maxhp,int damage, int x, int y):posx(x),posy(y),name(name),class_perso(class_perso),hp(maxhp),maxhp(maxhp),damage(damage){}*/

  int get_posx()const{
    return posx;
  }

  int get_posy()const{
    return posy;
  }

  string get_name()const{
    return name;
  }

   string get_class_perso()const{
    return class_perso;
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

  void set_name(string new_name){
    name=new_name;
  }

  void set_classe(string new_classe){
    class_perso=new_classe;
  }

  /*void set_inventory(string ob, int number){
    inventory[ob]=number;
    }*/

  void set_posx(int new_posx){
    posx=new_posx;
  }

  void set_damage(int new_damage){
    damage=new_damage;
  }

  void set_posy(int new_posy){
    posx=new_posy;
  }

  void set_maxhp(int new_maxhp){
    maxhp=new_maxhp;
    hp=maxhp;
  }


  void set_hp(int new_hp){
    hp=new_hp;
  }

  /*bool use_inventory(string ob){
    map<string,int>:: iterator it;
    it=inventory.find(ob);
    if(it!=inventory.end()){
      if(it->second > 0){
        it->second--;
	      return true;
      }
    }
    return false;
    }*/

  /*bool operator==(perso p){
      return this->name==p.name;
      }*/

};

