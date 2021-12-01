#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "Interp4Program.hh"
#include "Sender.hh"
#include "Scene.hh"
#include <memory>


#include "xmlinterp.hh"
#include <iostream>
#include <list>

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

void Fun4Thread_ExecCmd(shared_ptr<Interp4Command> CmdInterp, std::shared_ptr<MobileObj> pMObj, AccessGuard *pAccCtrl)
{
  CmdInterp->ExecCmd(pMObj,pAccCtrl); 
}


bool ExecProgram(istringstream & IStrm4Cmds, Configuration & Config,Scene & Scn, AccessGuard * pAccCtrl ){
  string Cmd;
  
  while(IStrm4Cmds >> Cmd)
  {
    std::vector<std::thread> Tab4Threads;
    Tab4Threads.reserve(10);
    while (Cmd != "Begin_Parallel_Actions")
    {
      IStrm4Cmds >> Cmd;
    }
    while (Cmd != "End_Parallel_Actions")
    {
      IStrm4Cmds >> Cmd;
      if (Cmd == "End_Parallel_Actions")
      {
        break;
      }
     
    std::map<const std::string, std::shared_ptr<Interf4Plugin>>::const_iterator    Iter = Config.getLibList().find(Cmd);
    
    if (Iter == Config.getLibList().end()) {
      cerr << "Nieznana komenda: " << Cmd<< endl;
      return false;
    }

    shared_ptr<Interp4Command> pInterp = Iter->second->CreateCmd();

    if(!pInterp->ReadParams(IStrm4Cmds))
    {
      cerr << "Bład podczas wczytywania parametrow" << endl;
      return false;
    }
    
    pInterp->PrintCmd();
    
    std::shared_ptr<MobileObj> pMobObj=nullptr;
    if(Cmd!="Pause"){
    string ObjName=pInterp->GetObjName();
    pMobObj=Scn.FindMobileObj(ObjName);
    if(pMobObj==nullptr){
      cerr << "Nie znaleziono obiektu na scenie" << endl;
      return false;
    }  
    }
    Tab4Threads.push_back(std::thread(Fun4Thread_ExecCmd,pInterp,pMobObj,pAccCtrl));
    /*if(!pInterp->ExecCmd(pMobObj,pAccCtrl))
    {
      cerr << "Bład podczas wykonywania polecenia" << endl;
      return false;
    }
    */
  }  
  for (std::thread &Th : Tab4Threads) Th.join();
  }
  cout << "  Koniec" << endl;
 return true;
}



int main(int argc, char **argv)
{
Configuration   Config;

if (!Config.readFile("config/config.xml")) return 1;

  cout << "Port: " << PORT << endl;
  
  int Socket4Sending;   
  

  if (!OpenConnection(Socket4Sending)) return 1;
  
  Scene Scn(Config.getObjList(),Socket4Sending);
  AccessGuard Guard(Socket4Sending);
  istringstream IStrm4Cmds;

ExecPreprocesor(argv[1],IStrm4Cmds);

 
 cout << endl <<"Zawartosc pliku opis_dzialan.cmd :"<<endl<< IStrm4Cmds.str() << endl; 	

//string Cmd;
 cout<< "Wczytane polecenia:" <<endl;
 if(!ExecProgram(IStrm4Cmds, Config,Scn, &Guard )){return 1;}
 /*
  while(IStrm4Cmds >> Cmd)
  {
 
    std::map<const std::string, std::shared_ptr<Interf4Plugin>>::const_iterator    Iter = Config.getLibList().find(Cmd);
    
    if (Iter == Config.getLibList().end()) {
      cerr << "Nieznana komenda: " << Cmd<< endl;
      return false;
    }

    shared_ptr<Interp4Command> pInterp = Iter->second->CreateCmd();

    if(!pInterp->ReadParams(IStrm4Cmds))
    {
      cerr << "Bład podczas wczytywania parametrow" << endl;
      return false;
    }
    
    pInterp->PrintCmd();
    
    std::shared_ptr<MobileObj> pMobObj=nullptr;
    if(Cmd!="Pause"){
    string ObjName=pInterp->GetObjName();
    pMobObj=Scn.FindMobileObj(ObjName);
    if(pMobObj==nullptr){
      cerr << "Nie znaleziono obiektu na scenie" << endl;
      return false;
    }
    
    }
    if(!pInterp->ExecCmd(pMobObj,&Guard))
    {
      cerr << "Bład podczas wykonywania polecenia" << endl;
      return false;
    }

  }*/
  //  thread   Thread4Sending(Fun_Sender, Socket4Sending, &ClientSender);

  //thread   Thread4Sending(Fun_CommunicationThread,&ClientSender);


  // Czekamy na zakończenie wątków.
  
  //for (std::thread &Th : Tab4Threads) Th.join();
  //cout << "  Koniec" << endl; 
  //-------------------------------------
  // Należy pamiętać o zamknięciu połączenia.
  // Bez tego serwer nie będzie reagował na
  // nowe połączenia.
  //
  cout << "Close\n" << endl; // To tylko, aby pokazac wysylana instrukcje
  Send(Socket4Sending,"Close\n");
  close(Socket4Sending);

}


