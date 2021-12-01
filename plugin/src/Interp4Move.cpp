#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"
#include "Scene.hh"
#include <unistd.h>
#include "MacierzRot3D.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): _ObjName("Nieznany"), _Speed_mS(0), _Dist_m(0)
{}


/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  cout << GetCmdName() <<" "<< _ObjName<< " " << _Speed_mS<< " "<< _Dist_m << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd(std::shared_ptr<MobileObj> pMobObj, AccessGuard *pAccGrd)
{	
  if(_Speed_mS!=0 && _Dist_m>=0){
  double Time_us=abs(1000000*_Dist_m/_Speed_mS);
  int delay_us=100000, iter=Time_us/delay_us;
  
  Vector3D v = pMobObj->GetPosition_m(),ex(0,1,0);
  MacierzRot3D RotX,RotY,RotZ;
  RotX.UstawRotX_st(pMobObj->GetAng_Roll_deg());
  RotY.UstawRotY_st(pMobObj->GetAng_Pitch_deg());
  RotZ.UstawRotY_st(pMobObj->GetAng_Pitch_deg());

  for (int i = 0; i < iter; ++i)
  {
  {
    std::lock_guard<std::mutex>  Lock(pAccGrd->UseGuard());
    v += (((RotZ*RotY)*RotX)*ex)*_Speed_mS/10;
    pMobObj->SetPosition_m(v);
    std::string msg="UpdateObj";
    msg +=  pMobObj->GetStateDesc();
    send(pAccGrd->GetSocket(),msg.c_str());
   // std::cout << msg.c_str();
   }
    usleep(delay_us);
  }
 }
  return true;
}
/*
bool Interp4Move::ExecCmd(std::shared_ptr<MobileObj> pMobObj, AccessGuard *pAccGrd)
{	
  if(_Speed_mS!=0 && _Dist_m>=0){
  double Time_us=abs(1000000*_Dist_m/_Speed_mS);
  int delay_us=100000, iter=Time_us/delay_us;
  
  Vector3D v = pMobObj->GetPosition_m();
  MacierzRot3D 
  double katOZ = pMobObj->GetAng_Yaw_deg();
  
  for (int i = 0; i < iter; ++i)
  {
    pAccGrd->LockAccess();
    v[0] += _Speed_mS * cos(M_PI * katOZ/180)/10;
    v[1] += _Speed_mS * sin(M_PI * katOZ/180)/10;
    
    pMobObj->SetPosition_m(v);
    std::string msg="UpdateObj";
    msg +=  pMobObj->GetStateDesc();
    send(pAccGrd->GetSocket(),msg.c_str());
    pAccGrd->UnlockAccess();
    std::cout << msg.c_str();
    usleep(delay_us);
  }
 }
  return true;
}
*/

/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _ObjName >> _Speed_mS >> _Dist_m ;
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}


const std::string Interp4Move::GetObjName(){
  return _ObjName;
}

int Interp4Move::send(int Sk2Server, const char *sMesg){
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
