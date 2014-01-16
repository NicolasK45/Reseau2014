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
    void do_move(string m);
    void do_use(string cap, string direction);
    void do_quit();
    void on_end();
  };  
  

  map<int,session_on_server *> user;
  map<int,perso> players;
 
  void session_on_server::do_join(string name_player, string classe_player){
    perso player;
    if (classe_player=="warrior"){
      player.set_name(name_player);
      player.set_classe(classe_player);
      player.set_maxhp(20);
      player.set_damage(3);
      player.set_posy(0);
      player.set_inventory("breakdoor",5);
      player.set_inventory("life_potion",3);
    }
    std::map<int,session_on_server *>::iterator it;
    while (it-> second!=this && it != user.end()){++it;}
    if (it == user.end()){
      user[it->first]=this;
      players[it->first]=player;
    }	
    else{
      proto.ERR("ERROR, Already a session");
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
