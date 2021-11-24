#include <iostream>
#include "Interp4Pause.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Pause"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}


/*!
 *
 */
Interp4Pause::Interp4Pause(): _Time_ms(0)
{}


/*!
 *
 */
void Interp4Pause::PrintCmd() const
{
  cout << GetCmdName() << " "<< _Time_ms << endl;
}


/*!
 *
 */
const char* Interp4Pause::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Pause::ExecCmd(std::shared_ptr<MobileObj> pMobObj, int Socket)const
{
  usleep(_Time_ms*1000);
  return true;
}


/*!
 *
 */
bool Interp4Pause::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _Time_ms;
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}

const std::string Interp4Pause::GetObjName(){
  return "pusto";
}


/*!
 *
 */
void Interp4Pause::PrintSyntax() const
{
  cout << "   Pause  NazwaObiektu  Czas_pauzy_ms" << endl;
}
