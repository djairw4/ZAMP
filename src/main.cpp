#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "Interp4Program.hh"
#include <memory>

using namespace std;

#define LINE_SIZE 100

bool ExecPreprocesor(const   char * NazwaPliku, istringstream & IStrm4Cmds )
{
  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;
  Cmd4Preproc += NazwaPliku;
  FILE * pProc = popen(Cmd4Preproc.c_str(),"r");
  if(!pProc)
    return false;
  while(fgets(Line,LINE_SIZE,pProc)){
    OTmpStrm<<Line;
  }
  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc) == 0;
}





int main(int argc, char **argv)
{
istringstream IStrm4Cmds;

ExecPreprocesor(argv[1],IStrm4Cmds);

 
 cout << endl <<"Zawartosc pliku opis_dzialan.cmd :"<<endl<< IStrm4Cmds.str() << endl; 	
Interp4Program LibInterp;
string Cmd;
 cout<< "Wczytane polecenia:" <<endl;
  while(IStrm4Cmds >> Cmd)
  {
   

    std::map<const std::string, std::shared_ptr<Interf4Plugin>>::const_iterator    Iter = LibInterp._LibList.find(Cmd);

    Interp4Command *pInterp = Iter->second->_pCreateCmd();

    pInterp->ReadParams(IStrm4Cmds);
    pInterp->PrintCmd();

    delete pInterp;
  }
/************************************** MOVE **********************************/
/*
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Move)(void);
  void *pFun;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);


  Interp4Command *pCmd = pCreateCmd_Move();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  dlclose(pLibHnd_Move);*/

/***************************************** SET ***********************************/
/*
 void *pLibHnd_Set = dlopen("libInterp4Set.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Set)(void);

  if (!pLibHnd_Set) {
    cerr << "!!! Brak biblioteki: Interp4Set.so" << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Set,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Set = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);


  pCmd = pCreateCmd_Set();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  dlclose(pLibHnd_Set);

*/
/*********************************** ROTATE ***********************************************/
/*
  void *pLibHnd_Rotate = dlopen("libInterp4Rotate.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Rotate)(void);

  if (!pLibHnd_Rotate) {
    cerr << "!!! Brak biblioteki: Interp4Rotate.so" << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Rotate,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Rotate = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);


  pCmd = pCreateCmd_Rotate();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  dlclose(pLibHnd_Rotate);*/

/********************************** PAUSE ************************************/
/*
void *pLibHnd_Pause = dlopen("libInterp4Pause.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Pause)(void);

  if (!pLibHnd_Pause) {
    cerr << "!!! Brak biblioteki: Interp4Pause.so" << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Pause,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Pause = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);


  pCmd = pCreateCmd_Pause();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  dlclose(pLibHnd_Pause);*/

/************************************** command **********************************/

  
}
