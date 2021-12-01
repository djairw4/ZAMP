#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"
#include <map>

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
//Interp4Set::Interp4Set():_ObjName("Nieznany"), _X(0), _Y(0), _AngOX_deg(0), _AngOY_deg(0), _AngOZ_deg(0)
Interp4Set::Interp4Set():_ObjName("Nieznany"), _Position(), _Orientation()
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  //cout << GetCmdName() <<" " << _ObjName <<" "<< _X <<" " << _Y <<" " << _AngOX_deg<<" "<< _AngOY_deg<<" " << _AngOZ_deg << endl;
  cout << GetCmdName() <<" " << _ObjName <<" "<< _Position <<" " << _Orientation << endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd(std::shared_ptr<MobileObj> pMobObj, AccessGuard *pAccGrd)
{
  std::lock_guard<std::mutex>  Lock(pAccGrd->UseGuard());
  /*
  Vector3D v;//=pMobObj->GetPosition_m();
  v[0]=_X;
  v[1]=_Y;*/
  pMobObj->SetPosition_m(_Position);
  pMobObj->SetRot(_Orientation);
  /*
  pMobObj->SetAng_Roll_deg(_AngOX_deg);
  pMobObj->SetAng_Pitch_deg(_AngOY_deg);
  pMobObj->SetAng_Yaw_deg(_AngOZ_deg);
*/
  std::string msg="UpdateObj";
  msg +=  pMobObj->GetStateDesc();
  send(pAccGrd->GetSocket(),msg.c_str());
  //std::cout << msg.c_str();
  return true;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  //Strm_CmdsList >> _ObjName >> _X >> _Y >> _AngOX_deg >> _AngOY_deg >> _AngOZ_deg;
  Strm_CmdsList >> _ObjName >> _Position >> _Orientation;
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  Wsp_x  Wsp_y  Wsp_z  Kat_OX  Kat_OY  Kat_OZ" << endl;
}

const std::string Interp4Set::GetObjName(){
  return _ObjName;
}

int Interp4Set::send(int Sk2Server, const char *sMesg){
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
