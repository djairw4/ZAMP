#ifndef  INTERF4PLUGIN_HH
#define  INTERF4PLUGIN_HH


#include "Interp4Command.hh"


class Interf4Plugin
{
  void * _pLibHnd;
  std::string _CmdName;
public:

  Interf4Plugin(std::string LibName);
  ~Interf4Plugin();
  Interp4Command *(*_pCreateCmd)(void);
  
  std::string getCmdName(){ return _CmdName;}
};

#endif
