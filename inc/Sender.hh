#ifndef SENDER_HH
#define SENDER_HH
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>
#include "AccessControl.hh"
#include "Port.hh"
#include "Scene.hh"


using namespace std;




/*!
 * \brief Funkcja jest treścią wątku komunikacyjnego
 * 
 * Funkcja jest treścią wątku komunikacyjnego.
 * \param[in] rSender - odpowiada za śledenie zmian na scenie 
 *                      i przesyłanie do serwera graficznego
 *                      aktualnego stanu sceny, gdy uległ on zmianie.
 */
/*void Fun_CommunicationThread(Sender  *pSender)
{
  pSender->Watching_and_Sending();
}
*/

/*!
 * Otwiera połączenie sieciowe
 * \param[out]  rSocket - deskryptor gniazda, poprzez które może być
 *                        realizowana komunikacja sieciowa.
 */
bool OpenConnection(int &rSocket)
{
  struct sockaddr_in  DaneAdSerw;

  bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);


  rSocket = socket(AF_INET,SOCK_STREAM,0);

  if (rSocket < 0) {
     cerr << "*** Blad otwarcia gniazda." << endl;
     return false;
  }

  if (connect(rSocket,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0)
   {
     cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
     return false;
   }
   
  Send(rSocket,"Clear\n"); 
  cout << "Clear\n";   
  return true;
}

#endif //SENDER_HH
