#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "Interp4Program.hh"
#include "network_connection.hh"
#include "Scene.hh"
#include "xmlinterp.hh"
#include <memory>
#include <iostream>


using namespace std;


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
  Interp4Program ProgInt(Config,Socket4Sending);

  ExecPreprocesor(argv[1],IStrm4Cmds);
 
  cout << endl <<"Zawartosc pliku opis_dzialan.cmd :"<<endl<< IStrm4Cmds.str() << endl; 	

  cout<< "Wczytane polecenia:" <<endl;
  if(!ProgInt.ExecProgram(IStrm4Cmds, &Guard )){return 1;}
 
  cout << "Close\n" << endl;
  Send(Socket4Sending,"Close\n");
  close(Socket4Sending); 
}


