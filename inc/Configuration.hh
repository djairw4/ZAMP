#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <map>
#include <memory>
#include "Interf4Plugin.hh"

/*!
 * \file
 * \brief Zawiera definicję klasy Configuration
 */

/*!
 * \brief Przechowuje listę obiektów i bibliotek 
 *
 *  Przechowuje listę obiektów i bibliotek wczytanych z pliku konfiguracyjnego 
 *  XML
 */
class Configuration {
  /*!
    * \brief Lista obiektów mobilnych
    */
  std::map<std::string, std::shared_ptr<MobileObj>> _ObjList;
  /*!
    * \brief Lista dostepnych bibliotek
    */
  std::map<const std::string, std::shared_ptr<Interf4Plugin>> _LibList;
  
public:
  /*!
   * \brief Dodaje bibliotekę do listy
   *
   * Zapisuje bibliotekę w parze z nazwą komendy i dodaje je na koniec 
   * listy bibliotek, które mają zostać wczytane.
   * \param [in] LibName - nazwa nowej biblioteki
   */
  void addLib(std::string LibName);
  /*!                                                                          
   * \brief Dodaje obiekt mobilny do konfiguracji                              
   *                                                                           
   * Zapisuje obiekt mobilny o wczytanych parametrach                          
   * na listę obiektów monilnych.                                              
   * \param [in] Name - nazwa obiektu                                          
   * \param [in] Shift - wektor przesunięcie środka ciężkości                  
   * \param [in] Scale - wektor wymiarów                                       
   * \param [in] Rot - wektor orientacji                                       
   * \param [in] Trans - wektor translacji                                     
   * \param [in] RGB - kolor obiektu wyrażony za pomocą wektora barw           
   * podstawowych RGB                                                          
   */
  void addObj(const std::string &Name, const Vector3D &Shift, const Vector3D &Scale, const Vector3D &Rot, const Vector3D &Trans, const Vector3D &RGB); 
  /*!                                                                          
   * \brief Dodaje obiekt mobilny do konfiguracji
   *                                           
   * Zapisuje obiekt mobilny na listę obiektów monilnych. 
   *                                             
   * \param [in] newObj - nowy obiekt, który ma zostać dodany do listy
   */
  void addObj(std::shared_ptr<MobileObj> & newObj);
  /*!                                                                          
   * \brief Zwraca listę bibliotek                                         
   */
  std::map<const std::string, std::shared_ptr<Interf4Plugin>> & getLibList();
   /*!                                                                                                                                      
   * \brief Zwraca listę obiektów mobilnych    
   */
  std::map<std::string, std::shared_ptr<MobileObj>> & getObjList();
   /*!                                                                                            
   * \brief Wczytuje konfigurację z pliku XML
   * \param [in] sFileName - ścieżka do pliku konfiguracyjnego
   * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
   * \retval false - w przeciwnym przypadku.
   */
  bool readFile(const char* sFileName);
};


#endif
