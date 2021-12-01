#include"Configuration.hh"

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"
#include <iostream>

using namespace std;
using namespace xercesc;

void Configuration::addLib(std::string LibName){
std::shared_ptr<Interf4Plugin> pLib = std::make_shared<Interf4Plugin>(LibName);
_LibList.insert(std::pair<const std::string, std::shared_ptr<Interf4Plugin>>(pLib->getCmdName(),pLib));
}

void Configuration::addObj(const std::string &Name, const Vector3D &Shift, const Vector3D &Scale, const Vector3D &Rot, const Vector3D &Trans, const Vector3D &RGB) 
{
  std::shared_ptr<MobileObj> newObj = std::make_shared<MobileObj>();

  newObj->SetName(Name.c_str());  
  newObj->SetShift(Shift);
  newObj->SetScale(Scale); 
  newObj->SetAng_Roll_deg(Rot[0]);
  newObj->SetAng_Pitch_deg(Rot[1]);
  newObj->SetAng_Yaw_deg(Rot[2]);
  newObj->SetPosition_m(Trans);
  newObj->SetColour(RGB);

  _ObjList.insert(std::pair<std::string,std::shared_ptr<MobileObj>>(Name,newObj));
}

void Configuration::addObj(std::shared_ptr<MobileObj> & newObj) 
{
  _ObjList.insert(std::pair<std::string,std::shared_ptr<MobileObj>>(newObj->GetName(),newObj));
}

std::map<const std::string, std::shared_ptr<Interf4Plugin>> & Configuration::getLibList(){
return _LibList;
}


std::map<std::string, std::shared_ptr<MobileObj>> & Configuration::getObjList(){
return _ObjList;
}

/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool Configuration::readFile(const char* sFileName)
{
   try {
            XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLInterp4Config(*this);
   //DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar("config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/actions.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}



