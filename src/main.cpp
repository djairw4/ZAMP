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

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"
#include <iostream>
#include <list>

using namespace std;
using namespace xercesc;












/*!
 * \brief Ilość stanów każdego z obiektów.
 *
 * Ilość stanów każdego z obiektów.
 * Podział na kolejne stany obiektów wykorzystywany jest
 * do animacji ruchu obiektów.
 */
#define STATES_NUMBER   8



/*!
 * Zestaw poleceń odpowiadających kolejnym stanom obiektu nr 1
 * i obrazujących jego ruch.
 */
const char* Cmds4Obj1[STATES_NUMBER] = {
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,23)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,26)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,29)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,32)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,35)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,38)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,41)\n",
  "UpdateObj Name=Podstawa1 RotXYZ_deg=(0,-45,44)\n"  
 };


/*!
 * Zestaw poleceń odpowiadających kolejnym stanom obiektu nr 2
 * i obrazujących jego ruch.
 */
const char* Cmds4Obj2[STATES_NUMBER] = {
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-48,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-45,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-42,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-39,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-36,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-33,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-30,0)\n",
  "UpdateObj Name=Podstawa1.Ramie1 RotXYZ_deg=(0,-27,0)\n"
 };

/*!
 * Zestaw poleceń odpowiadających kolejnym stanom obiektu nr 3
 * i obrazujących jego ruch.
 */
const char* Cmds4Obj3[STATES_NUMBER] = {
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-48,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-51,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-54,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-57,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-60,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-63,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-66,0)\n",
  "UpdateObj Name=Podstawa2.Ramie1 RotXYZ_deg=(0,-69,0)\n"
 };






/*!
 * \brief Ta klasa trochę udaję klasę MobileObj, która jest w zadaniu.
 *
 */
class GeomObject {
  /*!
   * \brief Identyfikuje aktualny stan obiektu.
   *
   * Identyfikuje aktualny stan obiektu. Indeks ten pozwala
   * na wybór z tablicy \link GeomObject::_Cmd4StatDesc _Cmd4StatDesc\endlink
   * odpowiedniego polecenia dla serwera, które reprezentuje aktualne
   * położenie i orientację obiektu.
   */
   int _StateIdx = 0;
  /*!
   * \brief Zestaw sekwencji poleceń symulujących ruch obiektu.
   *
   * Zestaw sekwencji poleceń symulujących ruch obiektu.
   * Każde polecenie odpowiada kolejnym stanom obiektu.
   */
   const char** _Cmd4StatDesc = nullptr;
  
 public:

  /*!
   * \brief Ustawia zestaw poleceń odpowiadających kolejnym stanom
   *        obiektu.
   */
  void SetCmds(const char *CmdsTab[STATES_NUMBER]) { _Cmd4StatDesc = CmdsTab; }
  /*!
   * \brief Udostępnia kolejny zestaw poleceń umożliwiających
   *        zespołu obiektu.
   *
   * Udostępnia kolejny zestaw poleceń umożliwiających
   * zespołu obiektu. Ta metoda "udaje" metodę, która w oryginalnym
   * rozwiązaniu powinna wygenerować odpowiednie polecenie na podstawie
   * przechowywanej informacji o położeniu i orientacji obiektu.
   */
  const char* GetStateDesc() const
  {
    return _Cmd4StatDesc[_StateIdx];
  }
  /*!
   * \brief Zwiększa indeks stanu, o ile aktualny opis nie jest pusty.
   *
   *  Zwiększa indeks stanu, o ile aktualny opis nie jest pusty.
   *  Ta metoda "udaje" metodę, która w oryginalnym rozwiązaniu
   *  jest odpowiedzialna za zmianę stanu obiektu, tzn. zmianę jego
   *  położenia lub orientacji.
   */
  bool IncStateIndex() {
    if (_StateIdx >= STATES_NUMBER-1) return false;
    ++_StateIdx;
    return true;
  }
};






/*!
 * \brief Przykład wykonywania pojedynczej operacji z animacją.
 *
 * Przykład wykonywania pojedynczej operacji z animacją.
 * \param[in] pObj - wskaźnik na obiekt, dla którego ma być wykonana dana operacja
 *                   zmiany jego stanu.
 * \param[in] pAccCtrl - wskaźnik na obiekt, poprzez który przekazywana jest informacja
 *                   o zmianie na scenie, zaś w trakcie dokonywania zmianay
 *                   zamykany jest dostęp do całej sceny.
 * \retval true - Jeśli dokonan zosała zmiana stanu wszystkich obiektów.
 * \retval false - w przypadku przeciwnym.
 */
/*bool ChangeState(Scene &Scn) //GeomObject *pObj, AccessControl  *pAccCtrl)
{
  bool Changed;

  while (true) {
    Scn.LockAccess(); // Zamykamy dostęp do sceny, gdy wykonujemy
                            // modyfikacje na obiekcie.
    for (GeomObject &rObj : Scn._Container4Objects) {
       if (!(Changed = rObj.IncStateIndex())) { Scn.UnlockAccess();  return false; }
    }
    Scn.MarkChange();
    Scn.UnlockAccess();
    usleep(300000);
  }
  return true;
}*/

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
Configuration   Config;

if (!Config.readFile("config/config.xml")) return 1;

  cout << "Port: " << PORT << endl;
  
  int                 Socket4Sending;   
  

  if (!OpenConnection(Socket4Sending)) return 1;
  
  Scene Scn(Config.getObjList(),Socket4Sending);
  istringstream IStrm4Cmds;

ExecPreprocesor(argv[1],IStrm4Cmds);

 
 cout << endl <<"Zawartosc pliku opis_dzialan.cmd :"<<endl<< IStrm4Cmds.str() << endl; 	

string Cmd;
//cout<<" "<<Config._LibList.size()<<endl;
 cout<< "Wczytane polecenia:" <<endl;
 
  while(IStrm4Cmds >> Cmd)
  {
 
    std::map<const std::string, std::shared_ptr<Interf4Plugin>>::const_iterator    Iter = Config.getLibList().find(Cmd);
    
    if (Iter == Config.getLibList().end()) {
      cerr << "Nieznana komenda: " << Cmd<< endl;
      return false;
    }

    Interp4Command *pInterp = Iter->second->_pCreateCmd();

    if(!pInterp->ReadParams(IStrm4Cmds))
    {
      cerr << "Bład podczas wczytywania parametrow" << endl;
      delete pInterp;
      return false;
    }
    
    pInterp->PrintCmd();
    
    std::shared_ptr<MobileObj> pMobObj=nullptr;
    if(Cmd!="Pause"){
    string ObjName=pInterp->GetObjName();
    pMobObj=Scn.FindMobileObj(ObjName);
    if(pMobObj==nullptr){
      cerr << "Nie znaleziono obiektu na scenie" << endl;
      delete pInterp;
      return false;
    }
    
    }
    
  
    //pInterp->PrintCmd();
    pInterp->ExecCmd(pMobObj,Socket4Sending);
    std::string msg="UpdateObj";
  msg +=  pMobObj->GetStateDesc();
  Send(Socket4Sending,msg.c_str());
  std::cout << msg.c_str();
    /*
    if(!pInterp->ExecCmd(pMobObj,Socket4Sending))
    {
      cerr << "Bład podczas wykonywania polecenia" << endl;
      delete pInterp;
      return false;
    }
*/
    delete pInterp;
    usleep(300000);
  }
  //Sender   ClientSender(Socket4Sending,&Scn);
  //  thread   Thread4Sending(Fun_Sender, Socket4Sending, &ClientSender);

  //thread   Thread4Sending(Fun_CommunicationThread,&ClientSender);
  /*
  const char *sConfigCmds =
"Clear\n"
"AddObj Name=Podstawa1 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,20) Trans_m=(-1,3,0)\n"
"AddObj Name=Podstawa1.Ramie1 RGB=(200,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
"AddObj Name=Podstawa1.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n"       
"AddObj Name=Podstawa2 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(-1,-3,0)\n"
"AddObj Name=Podstawa2.Ramie1 RGB=(200,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
"AddObj Name=Podstawa2.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n";


  cout << "Konfiguracja:" << endl;
  cout << sConfigCmds << endl;
  
  Send(Socket4Sending,sConfigCmds);
  

  cout << "Akcja:" << endl;    
  while (ChangeState(Scn)) {
    usleep(20000);
    Scn.MarkChange();
    usleep(100000);
  }
  usleep(100000);*/

  //-------------------------------------
  // Należy pamiętać o zamknięciu połączenia.
  // Bez tego serwer nie będzie reagował na
  // nowe połączenia.
  //
  cout << "Close\n" << endl; // To tylko, aby pokazac wysylana instrukcje
  Send(Socket4Sending,"Close\n");
  //ClientSender.CancelCountinueLooping();
  //Thread4Sending.join();
  //close(Socket4Sending);

}


