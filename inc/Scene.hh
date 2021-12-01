#ifndef SCENE_HH
#define SCENE_HH
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>
#include "AccessGuard.hh"
#include "Port.hh"
#include "MobileObj.hh"
#include <map>



/*!
 * \brief Namiastka sceny z prostą kolekcją trzech wizualizowanych obiektów.
 */
class Scene  {

  std::map<std::string, std::shared_ptr<MobileObj>> _ObjList;

  public:
  Scene(std::map<std::string, std::shared_ptr<MobileObj>> ObjList, int Socket); 
  
  std::map<std::string, std::shared_ptr<MobileObj>> getObjList(){return _ObjList;}
  
  std::shared_ptr<MobileObj> FindMobileObj(std::string Name);
  
  //std::vector<std::shared_ptr<MobileObj>> & getObjPtrs() {std::vector<std::shared_ptr<MobileObj>> Mob;}
  /*
  bool addObjs2Server( int Socket){ 
  std::map<const std::string, std::shared_ptr<MobileObj>>::const_iterator    Iter = _ObjList.begin;  
  if (Iter == (pScn->getObjList()).end()) {
    pScn->UnlockAccess();
    std::cerr << "Nieznany obiekt: " << _ObjName<< endl;
    return false;
  }
  std::shared_ptr<MobileObj> pObj=Iter->second;
  usleep(300000);
  return true;
   }*/
  
};


/*!
 * \brief Wysyła napis do poprzez gniazdo sieciowe.
 *
 * Wysyła napis do poprzez gniazdo sieciowe.
 * \param[in] Sk2Server - deskryptor gniazda sieciowego, poprzez które 
 *                        ma zostać wysłany napis w sensie języka C.
 * \param[in] sMesg - zawiera napis, który ma zostać wysłany poprzez
 *                    gniazdo sieciowe.
 */
 
int Send( int Sk2Server, const char *sMesg);

#endif //SCENE_HH
