#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <map>
#include <memory>
#include "Interf4Plugin.hh"

class Configuration {
  
  std::map<std::string, std::shared_ptr<MobileObj>> _ObjList;
  std::map<const std::string, std::shared_ptr<Interf4Plugin>> _LibList;
  
  public:
  
  
  void addLib(std::string LibName);
  void addObj(const std::string &Name, const Vector3D &Shift, const Vector3D &Scale, const Vector3D &Rot, const Vector3D &Trans, const Vector3D &RGB); 
  std::map<const std::string, std::shared_ptr<Interf4Plugin>> & getLibList();
  std::map<std::string, std::shared_ptr<MobileObj>> & getObjList();
  bool readFile(const char* sFileName);
};

//bool readFile(const char* sFileName, Configuration &rConfig);

#endif
