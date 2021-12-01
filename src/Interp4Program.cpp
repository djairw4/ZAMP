#include "Interp4Program.hh"

using namespace std;

Interp4Program::Interp4Program(Configuration &Config, int Socket) {
   _Scn=Scene(Config.getObjList(),Socket);
   _LibList = Config.getLibList();
}

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


bool Interp4Program::ExecProgram(istringstream & IStrm4Cmds, AccessGuard * pAccCtrl ){
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
     
    std::map<const std::string, std::shared_ptr<Interf4Plugin>>::const_iterator    Iter = _LibList.find(Cmd);
    
    if (Iter == _LibList.end()) {
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
    pMobObj=_Scn.FindMobileObj(ObjName);
    if(pMobObj==nullptr){
      cerr << "Nie znaleziono obiektu na scenie" << endl;
      return false;
    }  
    }
    Tab4Threads.push_back(std::thread(Fun4Thread_ExecCmd,pInterp,pMobObj,pAccCtrl));
  }  
  for (std::thread &Th : Tab4Threads) Th.join();
  }
 return true;
}



