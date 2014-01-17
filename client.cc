#include "proto.hh"
#include <iostream>
#include <cstdlib>
#include "netez/command_processor.hh"
#include <boost/lexical_cast.hpp>

namespace get_out
{
  using namespace std;
  using namespace netez;
  
  string nickname;

  struct session_on_client: public session_base
  {
    session_on_client(socket& io): session_base(io)
    {
      sig_begin.connect(EZMETHOD(this,on_begin));
      proto.left.sig_recv.connect(EZMETHOD(this,do_left));
      proto.ERR.sig_recv.connect(EZMETHOD(this,do_ERR));
      proto.OK.sig_recv.connect(EZMETHOD(this,do_OK));
      proto.event.sig_recv.connect(EZMETHOD(this,do_event));
      proto.quit.sig_recv.connect(EZMETHOD(this,do_quit));
    }

    void on_begin(){
      cout<<"Enter 'nick' and then your nickname and then your class (warrior, mage, ranger)"<<endl;
    }

    void do_OK(){cout<<"Your message have been transmited"<<endl;
    }
    
    void do_ERR(string r){cout<<"Error : "<<r<<endl;}
    
    void do_left(string p){cout<<p<<" left the the game."<<endl;}

    void do_event(string e){cout<<e<<endl;}

    void do_quit(){finish();}
  };

  using boost::lexical_cast;

  struct shell: public command_processor
  {
    session_on_client& client;
    
    shell(session_on_client& c):client(c)
    {
      register_command("nick", &shell::cmd_nick);
      register_command("move", &shell::cmd_move);
      register_command("use", &shell::cmd_use);
      register_command("quit",&shell::cmd_quit);
    }
  
    void wrong_args(const char*cmd,int n)
    {cerr<<cmd<<" expects "<< n<< " arguments"<<endl;}

    void cmd_nick(command_argv& argv){
      if(argv.size()!=2) wrong_args("nick",2);
      else{
	string n=lexical_cast<string>(argv[0]);
	string p=lexical_cast<string>(argv[1]);
	bool fin=false;
	while(!fin){
	  if(p=="warrior" || p=="mage" || p=="ranger"){
	     client.proto.join(n,p);
	     fin=true;
	  }
	  else{
	    cout<<"Votre nom de classe n'est pas bon, réécrivez le"<<endl;
	    cin>>p;
	  }
	}
      }
    }

    void cmd_move(command_argv& argv){
      if (argv.size()!=1) wrong_args("move",1);
      else {
	string d=lexical_cast<string>(argv[0]);
	if(d=="nord" || d=="sud" || d=="est" || d=="ouest" || d=="here"){ 
	  client.proto.move(d);
	}
	else{
	  client.proto.ERR("vous ne pouvez pas passer par là");
	}
      }
    }

    void cmd_use(command_argv& argv){
      if (argv.size()!=2) wrong_args("use",2);
      else{
	string o=lexical_cast<string>(argv[0]);
	string d=lexical_cast<string>(argv[1]);
	if(d=="nord" || d=="sud" || d=="est" || d=="ouest" || d=="here"){
	  client.proto.use(o,d);
	}
      }   
    }

    void cmd_quit(command_argv&){
      client.proto.quit();
      stop();
    }
  };
    

};

int main(int argc, char** argv)
{
  netez::client<get_out::session_on_client> client(argc, argv);
  get_out::shell shell(client.session);
  shell.run();
  client.join();
  return 0;
}
