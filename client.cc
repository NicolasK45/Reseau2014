#include "proto.hh"
#include "plateau.cc"
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
      proto.quit.sig_recv.connect(EZMETHOD(this,do_quit));
    }

    void on_begin(){
      cout<<"Enter 'nick' and then your nickname"<<endl;
    }

    void do_OK(){cout<<"Your message have been transmited"<<endl;
    }
    
    void do_ERR(string r){cout<<"Error : "<<r<<endl;}
    
    void do_left(string p){cout<<p<<" left the the game."<<endl;}

    void do_quit(){finish();}
  };

  using boost::lexical_cast;

  struct shell: public command_processor
  {
    session_on_client& client;
    
    shell(session_on_client& c):client(c)
    {
      register_command("move", &shell::cmd_move);
      /*register_command("use", &shell::cmd_say);
	register_command("quit",&shell::cmd_quit);*/
    }
   
 
    void wrong_args(const char*cmd,int n)
    {cerr<<cmd<<" expects "<< n<< " arguments"<<endl;}

    void cmd_move(command_argv& argv){
      if (argv.size()!=1) wrong_args("move",1);
      else {
	if(argv[0]=="nord" || argv[0]=="sud" || argv[0]=="est" || argv[0]=="ouest"){ 
	string d=lexical_cast<string>(argv[0]);
	client.proto.move(d);
	}
      }
    }

      /*void cmd_say(command_argv& argv){
      if (argv.size()!=1) wrong_args("say",1);
      else{
	string c=lexical_cast<string>(argv[0]);
	client.proto.say(c);
      }   
    }
    void cmd_send(command_argv& argv){
      if(argv.size()!=2) wrong_args("send",2);
      else{
	string d=lexical_cast<string>(argv[0]);
	string m=lexical_cast<string>(argv[1]);
	client.proto.send(d,m);
      }
      
      }*/
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
