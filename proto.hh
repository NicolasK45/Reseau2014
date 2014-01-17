#include "netez.hh"
#include "perso.cc"
#include "plateau.cc"
#include <string>

namespace get_out
{
  using namespace netez;

  struct proto: protocol<>
  {
    message<0,void(std::string)> move;
    message<1,void()> quit;
    message<2,void(std::string,std::string)> join;
     message<3,void(std::string,std::string)> use;
    message<4,void()> OK;
    message<5,void(std::string)> ERR;
    message<6,void(std::string)> left;
    message<7,void(std::string)>event;
    proto(socket& io): protocol<>(io), move(this), quit(this), join(this), use(this), OK(this), ERR(this),left(this),event(this){}
  };

  typedef session<proto> session_base;
}
