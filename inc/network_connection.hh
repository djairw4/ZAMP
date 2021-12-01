#ifndef NETWORK_CONNECTION_HH
#define NETWORK_CONNECTION_HH

/*!
 * \file
 * \brief Zawiera funkcje wykorzystywane do nawiązania połączenia seciowego
 *        i przesyłania komunikatów tekstowych.
 */

/*!
 * \brief Wysyła napis do serwera poprzez gniazdo sieciowe.
 *
 * Wysyła napis do serwera poprzez gniazdo sieciowe.
 * \param[in] Sk2Server - deskryptor gniazda sieciowego, poprzez które
 *                        ma zostać wysłany napis w sensie języka C.
 * \param[in] sMesg - zawiera napis, który ma zostać wysłany poprzez
 *                    gniazdo sieciowe.
 */
int Send(int Sk2Server, const char *sMesg);

/*!
 * Otwiera połączenie sieciowe
 * \param[out]  rSocket - deskryptor gniazda, poprzez które może być
 *                        realizowana komunikacja sieciowa.
 * \returnval true - gdy poprawnie otwarto połączenie
 * \returnval false - w przeciwnym wypadku
 */
bool OpenConnection(int &rSocket);

#endif
