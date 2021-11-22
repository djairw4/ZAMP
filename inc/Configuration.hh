#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <map>
#include <memory>
#include "Interf4Plugin.hh"

class Configuration {
  std::map<const std::string, std::shared_ptr<Interf4Plugin>> _LibList;
  std::map<std::string, std::shared_ptr<MobileObj>> _ObjList;
  
  public:
  void addLib(std::string LibName);
  void addObj();
  std::map<const std::string, std::shared_ptr<Interf4Plugin>> getLibList();
  std::map<std::string, std::shared_ptr<MobileObj>> getObjList();
  bool readFile(const char* sFileName);
};

#endif
