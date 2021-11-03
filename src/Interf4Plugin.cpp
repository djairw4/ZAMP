#include "Interf4Plugin.hh"
#include <dlfcn.h>

Interf4Plugin::Interf4Plugin(const std::string LibName){

  void *pLibHnd = dlopen(LibName.c_str(),RTLD_LAZY);
  void *pFun;

  if (!pLibHnd) {
    std::cerr << "!!! Brak biblioteki: "<<LibName << std::endl;
   
  }


  pFun = dlsym(pLibHnd,"CreateCmd");
  if (!pFun) {
    std::cerr << "!!! Nie znaleziono funkcji CreateCmd" << std::endl;
  }

  _pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);

  this->_pLibHnd = pLibHnd;

  Interp4Command *pCmd = _pCreateCmd();
  this->_CmdName=pCmd->GetCmdName();
  delete pCmd;
}

Interf4Plugin::~Interf4Plugin(){

  dlclose(this->_pLibHnd);

}
