#include "netez.hh"
#include <string>

namespace get_out
{
  using namespace netez;

  struct proto: protocol<>
  {
    message<0,void(std::string)> move;
    message<1,void()> quit;
    message<2,void(perso)> join;
    message<3,void(std::string,std::string)> use;
    //message<4,void()> OK;
    //message<5,void(std::string)> ERR;
    //message<6,void(std::string)> joined;
    //message<7,void(std::string)> left;
    //message<8,void(std::string,std::string)> said;
    //message<9,void(std::string,std::string)> sent;
    proto(socket& io): protocol<>(io), nick(this), say(this), join(this){}
  };

  typedef session<proto> session_base;
}
