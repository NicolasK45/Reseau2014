#include "proto.hh"
#include <iostream>
#include <map>
#include "Plateau.cc"


namespace get_out
{
  using namespace std;
  using namespace netez;


  struct session_on_server: session_base
  {
    session_on_server(socket& io): session_base(io)
    {
      proto.join.sig_recv.connect(EZMETHOD(this,do_join));
      proto.use.sig_recv.connect(EZMETHOD(this,do_use));
      proto.move.sig_recv.connect(EZMETHOD(this,do_move));
      proto.quit.sig_recv.connect(EZMETHOD(this,do_quit));
      sig_end.connect(EZMETHOD(this,on_end));
     }

   
    void do_join(perso player);
    void do_move(string m);
    void do_use(string cap, string direction);
    void do_quit();
    void on_end();
  };  
  
  map<int,session_on_server *>user;
  map<int,perso *>players;
 
  void session_on_server::do_join(perso player){
    std::map<int,perso *>::iterator it;
    it =players.find(player);
    if (it==user.end()){
      user[]=this;
      players[]=player;
    }	
    else{
      proto.ERR("ERROR, Nickname already in use");
    }
  }
  


  
  void session_on_server::do_quit()
  {
    auto au=user.begin();
    while(au->second!=this){++au;}
    for (auto it=user.begin();it!=user.end();it++){
      if(it->second==this){
	it->second->proto.quit();
      }
      else{
	it->second->proto.left(au->first);
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
}

int main(int argc, char** argv)
{
  netez::server<chat::session_on_server> server(argc, argv);
  server.join();
  return 0;
}
