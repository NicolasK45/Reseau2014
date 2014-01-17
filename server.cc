#include "netez.hh"
#include "proto.hh"
#include <iostream>
#include <map>



namespace get_out
{
  using namespace std;
  using namespace netez;

 
    
  struct session_on_server: session_base
  {
    session_on_server(socket& io): session_base(io)
    {
      proto.join.sig_recv.connect(EZMETHOD(this,do_join));
  //    proto.use.sig_recv.connect(EZMETHOD(this,do_use));
  //    proto.move.sig_recv.connect(EZMETHOD(this,do_move));
      proto.quit.sig_recv.connect(EZMETHOD(this,do_quit));
      sig_end.connect(EZMETHOD(this,on_end));
     }
   
    void do_join(string name_player, string classe_player);
    //void do_move(string m);
    //void do_use(string cap, string direction);
    void do_quit();
    void on_end();
  };  
  

  map<int,session_on_server *> user;
  map<int,perso> players;
    
 
  void session_on_server::do_join(string name_player, string classe_player){
    int x;
    if(user.size()==0){
      cout<<"premier"<<endl;
      x=0;
    }
    else if(user.size()==1){
      x=9;
    }
    else if(user.size()==2){
      x=4;
    }
    else if(user.size()==3){
      x=7;
    }
    if(user.size()<4){
      perso player;
      if (classe_player=="warrior"){
	/*player.set_inventory("key",5);
	player.set_inventory("shock",4);
	player.set_inventory("life_potion",2);*/
	player.set_name(name_player);
	player.set_classe(classe_player);
	player.set_maxhp(15);
	player.set_damage(4);
	player.set_posx(x);
	player.set_posy(0);
      }
      if(classe_player=="mage"){
	/*player.set_inventory("fireball",6);
	player.set_inventory("fire_shield",3);
	player.set_inventory("key",3);
	player.set_inventory("life_potion",5);*/
	player.set_name(name_player);
	player.set_classe(classe_player);
	player.set_maxhp(10);
	player.set_damage(3);
	player.set_posx(x);
	player.set_posy(0);
      }
      if(classe_player=="ranger"){
	/*player.set_inventory("clairvoyance",12);
	player.set_inventory("escape",4);
	player.set_inventory("key",2);
	player.set_inventory("life_potion",3);*/
	player.set_name(name_player);
	player.set_classe(classe_player);
	player.set_maxhp(12);
	player.set_damage(4);
	player.set_posx(x);
	player.set_posy(0);
      }

      std::map<int,session_on_server *>::iterator it;
      
      bool ok=true;
      
      if(user.size()>0){
	cout<<"debut"<<endl;
	it=user.begin();
	while(it!=user.end() && ok){
	  if (it->second==this){proto.ERR("ERROR, Already a session");ok=false;}
	  else {cout<<"boucle"<<endl;++it;}
	}
	cout<<"fin"<<endl;
      }
      if (it == user.end() || user.size()==0){
	user[user.size()+1]=this;
	players[players.size()+1]=player;
      }	
     for (it=user.begin();it!=user.end();it++){
	  it->second->proto.event(name_player+" has join the game.");
     }
    } 
  }
  
  void session_on_server::do_quit()
  {
    auto au=user.begin();
    while(au->second!=this){++au;}
    auto nm=players[au->first];
    for (auto it=user.begin();it!=user.end();it++){
      if(it->second==this){
	       it->second->proto.quit();
      }
      else{
	       it->second->proto.left(nm.get_name());
      }
    }
  }

  void session_on_server::on_end()
  {
    for (auto it=user.begin();it!=user.end();it++){
      if (it->second==this){
        user.erase(it);
      }
    }
  }
};

int main(int argc, char** argv)
{
  netez::server<get_out::session_on_server> server(argc, argv);
  server.join();
  return 0;
}
