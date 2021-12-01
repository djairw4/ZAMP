#ifndef  INTERP4PROGRAM_HH
#define  INTERP4PROGRAM_HH


#include "Interf4Plugin.hh"
#include <map>
#include <memory>


class Interp4Program{
Scene _Scn;
std::map<const std::string, std::shared_ptr<Interf4Plugin>> _LibList;
public:
  Interp4Program();
  
};


#endif
