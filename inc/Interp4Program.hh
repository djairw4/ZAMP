#ifndef  INTERP4PROGRAM_HH
#define  INTERP4PROGRAM_HH


#include "Interf4Plugin.hh"
#include "Configuration.hh"
#include "AccessGuard.hh"
#include <map>
#include <memory>
#include <sstream>

#define LINE_SIZE 100


/*!
 * \brief Przechowuje informacje o scenie i listę bibliotek
 * Klasa odpowiedzialna za wykonanie programu
 */
class Interp4Program{
Scene _Scn;
std::map<const std::string, std::shared_ptr<Interf4Plugin>> _LibList;
public:

  
  Interp4Program(Configuration &Config,int Socket);
  /*!
   * \brief Uruchomienie wykonywania głównej pętli programu.
   * \return Zwraca true gdy operacja się powiedzie
   */
  bool ExecProgram(std::istringstream & IStrm4Cmds, AccessGuard * pAccCtrl);
};
/*!                                                                           
   * \brief Uruchomienie preprocesora dla pliku z opisem poleceń          
   * \return Zwraca true gdy operacja się powiedzie                             
   */

bool ExecPreprocesor(const char * NazwaPliku, std::istringstream & IStrm4Cmds );

/*!                                                                           
   * \brief Funkcja wątku wykonująca polecenia                             
   */

void Fun4Thread_ExecCmd(std::shared_ptr<Interp4Command> CmdInterp, std::shared_ptr<MobileObj> pMObj, AccessGuard *pAccCtrl);


#endif
