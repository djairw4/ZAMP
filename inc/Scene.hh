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
 * \file
 * \brief Definicja klasy Scene
 *
 * Plik zawiera definicję klasy Scene, moedelującej scenę, po której
 * poruszają się obiekty
 */


/*!
 * \brief Modeluje scenę dla obiektów mobilnych
 *
 *  Klasa modeluje scenę, po której poruszać mogą się obiekty mobilne,
 *  przechowuje mapę znajdujących się na niej obiektów.
 *
 */
class Scene  {
  /*!
   * \brief Lista obiektów na scenie
   *
   *  Mapa mobilnych obiektów na scenie, której kluczami są nazwy posczególnych
   *  obiektów
   */
  std::map<std::string, std::shared_ptr<MobileObj>> _ObjList;

  public:
  /*!
   * \brief Konstruktor bezparametryczny
   */
  Scene(){}
  /*!
   * \brief Wczytuje listę obiektów z konfiguracji
   * 
   * Wczytuje z konfiguracji zestaw obiektów mobilnych oraz wysyła ich parametry do serwera
   */
  Scene(std::map<std::string, std::shared_ptr<MobileObj>> ObjList,int & Socket);
  /*!
   * \brief Przekazuje listę obiektów dostępnych  na scenie
   * \return  listę obiektów mobilnych
   */
  std::map<std::string, std::shared_ptr<MobileObj>> getObjList(){return _ObjList;}
  /*!
   * \brief Znajduje obiekt na scenie
   *
   *  Znajduje obiekt, o podanej nazwie, w zbiorze obiektów,
   *  znajdujących się na scenie i zwraca wskaźnik na niego.
   * \param[in] Name - nazwa obiektu
   * \return Wskaźnik dzielony na znaleziony obiekt
   */
  std::shared_ptr<MobileObj> FindMobileObj(std::string Name);
  
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
