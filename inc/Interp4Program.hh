#ifndef  INTERP4PROGRAM_HH
#define  INTERP4PROGRAM_HH


#include "Interf4Plugin.hh"
#include<map>
#include <memory>

typedef std::map<const std::string, std::shared_ptr<Interf4Plugin>> Interp4Program;

#endif
