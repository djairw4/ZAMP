#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"
#include "Scene.hh"
#include <unistd.h>

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
bool Interp4Move::ExecCmd(std::shared_ptr<MobileObj> pMobObj, int Socket)const
{	
  if(_Speed_mS!=0 && _Dist_m>=0){
  double Time_us=abs(1000000*_Dist_m/_Speed_mS);
  int delay_us=100000, iter=Time_us/delay_us;
  
  Vector3D v = pMobObj->GetPosition_m();
  double katOZ = pMobObj->GetAng_Yaw_deg();
  
  for (int i = 0; i < iter; ++i)
  {
    v[0] += _Speed_mS * cos(M_PI * katOZ/180)/10;
    v[1] += _Speed_mS * sin(M_PI * katOZ/180)/10;
    
    pMobObj->SetPosition_m(v);
    std::string msg="UpdateObj";
    msg +=  pMobObj->GetStateDesc();
    //Send(Socket,msg.c_str());
    std::cout << msg.c_str();
    usleep(delay_us);
  }
 }
  return true;
}


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
