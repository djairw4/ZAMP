#ifndef SMACIERZ_HH
#define SMACIERZ_HH

#include <iostream>
#include "geomVector.hh"


/*!
 * \file
 *  \brief Klasa Macierz modeluje pojecie macierzy kwadratowej o rozmiarze
 *  ROZMIAR x ROZMIAR za pomoca tablicy dwuwymiarowej.
 *
 *  Dostepne metody:
 *  - odczytywanie i zapisywanie odpowiednich wspolczynikow macierzy
 *    za pomoca przeciazenia operatora funkcyjnego,
 *  - mnozenie macierzy przez wektor,
 *  - wstawianie do macierzy wektora zamiast jednego z wierszy,
 *  - zamienianie ze soba wierszy,
 *  - odejmowanie od wiersza innego wiersza pomnozonego przez liczbe,
 *  - obliczanie wyznacznika macierzy.
 */
template<typename TYP,int WYMIAR>
class SMacierz {
 
  TYP  _Tab[WYMIAR][WYMIAR];
  
public:

  /*!
   * \brief Metoda pozwala wypisywac wartosci odpowiednich wspolczynnikow
   */
  inline TYP operator () (int Wie, int Kol) const {return _Tab[Wie][Kol];}

  /*!
   * \brief Metoda pozwala przypisywac wartosci odpowiednim wspolczynnikom
   */
  inline TYP& operator () (int Wie, int Kol) {return _Tab[Wie][Kol];}

  /*!
   * \brief Metoda realizujaca mnozenie macierzy przez wektor
   * o tych samych rozmiarach.
   * Parametry:
   *  \param  Wek - obiekt typu Wektor, mnożnik
   * \return Zwraca wektor bedacy wynikiem mnozenia.
   */
  geom::Vector<TYP,WYMIAR> operator * (const geom::Vector<TYP,WYMIAR> &Wek) const;

   /*!
   * \brief Metoda pozwala wstawic wektor zamiast jednego z wierszy macierzy.
   * Parametry:
   *  \param  Wek - wstawiany wektor
   *  \param  Wiersz - numer wiersza ktory zostanie zamieniony z wektorem
   * Warunki:
   *  \pre  - numer wiersza musi byc nieujemny i mniejszy od rozmiaru macierzy
   */
  /*inline void wstaw_wektor(SWektor<TYP,WYMIAR> Wek, unsigned int Wiersz){
    assert(Wiersz<WYMIAR);
    for(int i=0;i<WYMIAR;++i){ _Tab[Wiersz][i]=Wek[i]; }
  }
*/
  /*!
   * \brief Metoda pozwala zamienic ze soba wiersze macierzy.
   * Parametry:
   *  \param  wie1, wie2 - numery zamienianych wierszy 
   * Warunki:
   *  \pre  - numer wiersza musi byc nieujemny i mniejszy od rozmiaru macierzy
   */
  /*inline void zamien_wiersze(unsigned int wie1,unsigned int wie2){
    assert(wie1<WYMIAR && wie2<WYMIAR);
    for(int i=0;i<WYMIAR;++i){ std::swap(_Tab[wie1][i],_Tab[wie2][i]); }
  }*/
  
  /*!
   * \briefMetoda pozwala od jednego wiersza odjac przeskalowany inny wiersz macierzy
   * Parametry:
   *  \param  wie1 - wiersz od ktorego odejmujemy
   *  \param  skala - mnoznik wiersza odejmowanego
   *  \param  wie2 - wiersz ktory odejmujemy
   * Warunki:
   *  \pre  - numer wiersza musi byc nieujemny i mniejszy od rozmiaru macierzy
   */
  inline void odejmij_wiersz(unsigned int wie1, TYP skala,unsigned int wie2){
    assert(wie1<WYMIAR && wie2<WYMIAR);
    for(int i=0;i<WYMIAR;++i){_Tab[wie1][i]=_Tab[wie1][i]-skala*_Tab[wie2][i];}
  }

  /*!
   * \brief Metoda zwracajaca wyznacznik macierzy
   */
  TYP wyznacznik() const;
  /*!
   * \brief Metoda ustawiajaca macierz rotacji
   */
  void UstawRotX_st(double kat_st);
  void UstawRotY_st(double kat_st);
  void UstawRotZ_st(double kat_st);
  
  SMacierz<TYP,WYMIAR> operator * (const SMacierz<TYP,WYMIAR> &Mac) const;
  
};


/*!
 * \brief Funkcja wczytuje ze strumienia wspolczynniki macierzy.
 *
 *  \param  Strm - strumien z ktorego czytamy
 *  \param  Mac  - obiekt klasy Macierz
 *    
 * \return Zwraca strumien wejsciowy, jesli operacja czytania nie powiodla sie 
 * strumien w stanie fail.
 */
template<typename TYP,int WYMIAR>
std::istream& operator >> (std::istream &Strm, SMacierz<TYP,WYMIAR> &Mac){
  for(int i=0;i<WYMIAR;++i){
    for(int j=0;j<WYMIAR;++j){
      Strm>>Mac(i,j); if(!Strm){return Strm;}
    }
  }
  return Strm;
}

/*!
 * \brief Funkcja wypisuje macierz do strumienia.
 *
 *  \param  Strm - strumien do ktorego zapisujemy wspolrzedne
 *  \param  Mac  - obiekt klasy Macierz
 *    
 * \return Zwraca strumien wyjsciowy z wypisanymi wspolczynnikami macierzy.
 */
template<typename TYP,int WYMIAR>
std::ostream& operator << (std::ostream &Strm, const SMacierz<TYP,WYMIAR> &Mac){
  for(int i=0;i<WYMIAR;++i){
    for(int j=0;j<WYMIAR;++j){
      Strm.width(3);
      Strm<<Mac(i,j)<<" ";
    }
    Strm<<std::endl;
  }
  return Strm;
}

template<typename TYP,int WYMIAR>
geom::Vector<TYP,WYMIAR> SMacierz<TYP,WYMIAR>::operator * (const geom::Vector<TYP,WYMIAR> &Wek) const{
  geom::Vector<TYP,WYMIAR> Wynik={0,0,0};
  for(int i=0;i<WYMIAR;++i){
    for(int j=0;j<WYMIAR;++j){
      Wynik[i]+=(_Tab[i][j]*Wek[j]);
    }
  }
  return Wynik;
}

template<typename TYP,int WYMIAR>
TYP SMacierz<TYP,WYMIAR>::wyznacznik()const{
  SMacierz<TYP,WYMIAR> Kopia=*this;
  TYP Skala, Wynik;
  int znak=1;
  for(int r=0;(r+2)<WYMIAR;++r){
    int wiersz=1;
    while(Kopia(r,r)==0 && wiersz+r<WYMIAR){
      Kopia.zamien_wiersze(r,wiersz+r);
      ++wiersz;
    }
    if((wiersz+r)==WYMIAR){return 0;}
    if(((wiersz+r)%2)==0){znak=znak*(-1);}
    for(int i=r+1;i<WYMIAR;++i){
      Skala=Kopia(i,r)/Kopia(r,r);
      Kopia.odejmij_wiersz(i,Skala,r);
    }
  }
  Wynik = ( Kopia((WYMIAR-2),(WYMIAR-2)) * Kopia((WYMIAR-1),(WYMIAR-1)) - Kopia((WYMIAR-1),(WYMIAR-2)) * Kopia((WYMIAR-2),(WYMIAR-1)) )*znak;
  
  for(int i=0;(i+2)<WYMIAR;++i){
    Wynik = Wynik*Kopia(i,i);
  }
  return Wynik;
}

template<>
void SMacierz<double,3>::UstawRotX_st(double kat_st){
  double kat_rad=M_PI*kat_st/180;
  _Tab[1][1]=cos(kat_rad);
  _Tab[1][2]=-sin(kat_rad);
  _Tab[2][1]=cos(kat_rad);
  _Tab[2][2]=sin(kat_rad);
  _Tab[0][0]=1;
  _Tab[0][1]=0;
  _Tab[0][2]=0;
  _Tab[1][0]=0;
  _Tab[2][0]=0; 
}

template<>
void SMacierz<double,3>::UstawRotY_st(double kat_st){
  double kat_rad=M_PI*kat_st/180;
  _Tab[0][0]=cos(kat_rad);
  _Tab[0][2]=sin(kat_rad);
  _Tab[2][2]=cos(kat_rad);
  _Tab[2][0]=-sin(kat_rad);
  _Tab[1][1]=1;
  _Tab[0][1]=0;
  _Tab[2][1]=0;
  _Tab[1][2]=0;
  _Tab[1][0]=0; 
}

template<>
void SMacierz<double,3>::UstawRotZ_st(double kat_st){
  double kat_rad=M_PI*kat_st/180;
  _Tab[0][0]=cos(kat_rad);
  _Tab[0][1]=-sin(kat_rad);
  _Tab[1][1]=cos(kat_rad);
  _Tab[1][0]=sin(kat_rad);
  _Tab[2][2]=1;
  _Tab[0][2]=0;
  _Tab[1][2]=0;
  _Tab[2][1]=0;
  _Tab[2][0]=0; 
}


template<>
SMacierz<double,3> SMacierz<double,3>::operator * (const SMacierz<double,3> &Mac) const{
SMacierz<double,3> C;
for(int i = 0; i < 3; i++ ){
    for(int j = 0; j < 3; j++ )
    {
      double suma = 0;
      for( int k = 0; k < 3; k++ ) suma += (*this)(i,k) * Mac(k,j);
      C(i,j) = suma;
    }
 }  
 return C;  
}

#endif
