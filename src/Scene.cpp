#include "Scene.hh"


int Send(int Sk2Server, const char *sMesg){

  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);

  while ((IlWyslanych = write(Sk2Server,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    std::cerr << "*** Blad przeslania napisu." << std::endl;
  }
  return 0;
}

Scene::Scene(std::map<std::string, std::shared_ptr<MobileObj>> ObjList,int & Socket) : _ObjList(ObjList) {
  for ( const std::pair<std::string, std::shared_ptr<MobileObj>> & iter : _ObjList){ 
     std::string msg="AddObj";
     msg += iter.second->GetStateDesc();
     Send(Socket,msg.c_str());
     std::cout << msg.c_str();
     usleep(300000);
  }
  }  
 
  
  
std::shared_ptr<MobileObj> Scene::FindMobileObj(std::string Name){
    std::map<const std::string, std::shared_ptr<MobileObj>>::const_iterator    Iter = _ObjList.find(Name);
    
    if (Iter == _ObjList.end()) {
      std::cerr << "Nieznany obiekt " << Name<< std::endl;
      return nullptr;
    }
    return Iter->second;


}  
