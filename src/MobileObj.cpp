#include "MobileObj.hh"



std::istream & operator >> (std::istream &IStrm, MobileObj & MObj)
{
std::string ParamName, NameValue;
Vector3D ParamValue;
IStrm>>ParamName>>NameValue;	
 	if (IStrm.fail()) {
     	cerr << " Blad!!!" << endl;
 	} else {
     	cout << ParamName << endl;
     	cout << "     " << NameValue << endl;
 	}
 	MObj.SetName(NameValue);
    for(int i=1;i<6;++i){
 	//IStrm.clear();
 	IStrm>>ParamName>>ParamValue;	
 	if (IStrm.fail()) {
     	cerr << " Blad!!!" << endl;
 	} else {
     	cout << ParamName << endl;
     	cout << "     " << ParamValue << endl;
 	}
 	if(ParamName=="Shift"){
 	MObj.SetShift(ParamValue);
 	}
 	else if(ParamName=="Scale"){
 	MObj.SetScale(ParamValue);
 	}
 	else if(ParamName=="RotXYZ_deg"){
 	MObj.SetRot(ParamValue);
 	}
 	else if(ParamName=="Trans_m"){
 	MObj.SetPosition_m(ParamValue);
 	}
 	else if(ParamName=="RGB"){
 	MObj.SetColour(ParamValue);
 	}
 	
   }
   return IStrm;
}

