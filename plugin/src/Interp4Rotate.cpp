#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate():_ObjName("Nieznany"), _AngSpeed_degS(0), _Axis('z'), _RotAng_deg(0)
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  cout << GetCmdName() <<" "<< _ObjName <<" "<< _AngSpeed_degS<<" "<< _Axis<<" "<< _RotAng_deg<< endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Rotate::ExecCmd(std::shared_ptr<MobileObj> pMobObj, int Socket)const
{
  if(_AngSpeed_degS!=0 && _RotAng_deg>0){
  double Time_us=abs(1000000*_RotAng_deg/_AngSpeed_degS);
  int delay_us=100000, iter=Time_us/delay_us;
  double kat=0;
 
  switch(_Axis){
  case 'x': kat = pMobObj->GetAng_Roll_deg();
  break;
  case 'y': kat = pMobObj->GetAng_Pitch_deg();
  break;
  case 'z': kat = pMobObj->GetAng_Yaw_deg();
  break;
  }
  for (int i = 0; i < iter; ++i)
  {
    
    kat += _RotAng_deg/10;
    
    switch(_Axis){
      case 'x': pMobObj->SetAng_Roll_deg(kat);
      break;
      case 'y': pMobObj->SetAng_Pitch_deg(kat);
      break;
      case 'z': pMobObj->SetAng_Yaw_deg(kat);
      break;
    }    
    std::string msg="UpdateObj";
    msg +=  pMobObj->GetStateDesc();
    Send(Socket,msg.c_str());
    std::cout << msg.c_str();
    usleep(delay_us);
  }
  }
  return true;
}


/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _ObjName >> _AngSpeed_degS >> _Axis >> _RotAng_deg;
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  szybkosc_katowa(stopnie/sek) nazwa_osi kat_obrotu(stopnie)" << endl;
}

const std::string Interp4Rotate::GetObjName(){
  return _ObjName;
}
