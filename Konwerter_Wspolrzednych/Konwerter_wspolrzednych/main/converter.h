/** @file */
#pragma once

/// klasa odpowadająca za konwersję pomiędzy systemami WGS84 i PL2000
class Converter {
	long double a = 6378137.00000;		///< równikowy promień ziemi
	long double e = 0.0818191910428;	///< pierwszy mimośród elipsoidy
	long double R0 = 6367449.145771;	///< promień sfery Lagrange'a
	long double m0 = 0.999923;			///< parametr przekształcenia do systemu PL2000
protected:	
	
	/** \brief Odwzorowanie Lagrange'a
	  * \param B szerokość geaograficzna danego punktu
	  * \param L długość geograficzna danego punktu
	  * \param phi wynik przekształcenia Lagrange'a dla podanej szerokości geograficznej danego punktu
	  * \param lambda różnica pomiędzy szerokościa południka środkowego dla danej strefy, a szerokością goegraficzna danego punktu
	  * 
	  * Funkcja odpowiada za realizację odwzorowania Lagrange'a dla punktu o podanej w stopniach długości i szereokości geograficznej.
	  * Jest to pierwszy z etapów potrzebnych do realizacji konwersji z trójwymiarowego systemu współrzędnych na dwuwymiarowy.
	*/
	void Lagrange(const long double& B, const long double& L, long double& phi, long double& lambda) const noexcept;
	
	/** \brief Odwzorowanie Mercatora
	  * \param phi wynik odwzorowania Lagrange'a dla punktu o podaych współrzędnych geograficznych
	  * \param lambda różnica pomiędzy szerokościa południka środkowego dla danej strefy, a szerokością goegraficzna danego punktu
	  * 
	  * Funkcja odpowiada za realizację odwzorowania Mercatora dla punktu opisanego za pomocą wyniku przekształcenia Lagrange'a.
	  * Jest to drugi z etapów potrzebnych do realizacji konwersji z trójwymiarowego systemu współrzędnych na dwuwymiarowy.
	  * Funkcja przyjmuje podane przez referencję wartości obliczone za pomocą odwzorowania Lagrange'a.
	  * Następnie wykonuje obliczenia i zwraca wynik do podanych zmiennych wejściowych.
	*/
	void Mercator(long double& phi, long double& lambda) const noexcept;
	
	/** \brief Odwzorowanie Gaussa-Krügera
	  * \param xmer współrzędna X punktu, otrzymana przy pomocy odwzorowania Mercatora
	  * \param ymer współrzędna Y punktu, otrzymana przy pomocy odwzorowania Mercatora
	  *
	  * Funkcja odpowiada za realizację odwzorowania Gaussa-Krügera, dla punktu o współrzędnych (xmer,ymer).
	  * Jest to ostatni z etapów potrzebnych do realizacji konwersji z trójwymiarowego systemu współrzędnych na dwuwymiarowy.
	  * Funkcja przyjmuje podane przez referencję współrzędne punktu obliczone za pomocą odwzorowania Mercatora.
	  * Następnie wykonuje obliczenia i zwraca wynik do podanych zmiennych wejściowych.
	*/
	void Kruger(long double& xmer, long double& ymer) const noexcept;
	
	/** \brief Odwrotne odwzorowanie Gaussa-Krügera
      * \param xgk współrzędna X punktu
      * \param ygk współrzędna Y punktu
	  * 
	  * Funkcja odpowiada za realizację odwrotnego odwzorowania Gaussa-Krügera, dla punktu o współrzędnych (xgk,ygk).
	  * Jest to pierwszy z etapów potrzebnych do realizacji konwersji z dwuwymiarowego systemu współrzędnych na trójwymiarowy.
	  * Funkcja przyjmuje podane przez referencję współrzędne punktu własciwe dla odwrotnego odwzorowania Gaussa-Krügera.
	  * Następnie wykonuje obliczenia i zwraca wynik do podanych zmiennych wejściowych.
	*/
	void ReverseKruger(long double& xgk, long double& ygk) const noexcept;
	
	/** \brief Odwrotne odwzorowanie Mercatora
	  * \param xmer współrzędna X punktu, otrzymana przy pomocy odwrotnego odwzorowania Gaussa-Krügera
	  * \param ymer współrzędna Y punktu, otrzymana przy pomocy odwrotnego odwzorowania Gaussa-Krügera
	  * 
	  * Funkcja odpowiada za realizację odwrotnego odwzorowania Mercatora, dla punktu o współrzędnych (xmer,ymer).
	  * Jest to drugi z etapów potrzebnych do realizacji konwersji z dwuwymiarowego systemu współrzędnych na trójwymiarowy.
	  * Funkcja przyjmuje podane przez referencję współrzędne punktu własciwe dla odwrotnego odwzorowania Mercatora.
	  * Następnie wykonuje obliczenia i zwraca wynik do podanych zmiennych wejściowych.
	*/
	void ReverseMercator(long double& xmer, long double& ymer) const noexcept;
	
	/** \brief Odwrotne odwzorowanie Lagrange'a
	  * \param phi współrzędna X punktu, otrzymana przy pomocy odwzorowania Mercatora
	  * \param lambda współrzędna Y punktu, otrzymana przy pomocy odwzorowania Mercatora
	  * \param E dlugosć geograficzna punktu wyrażona w metrach (w układzie dwuwymiarowym)
	  * \param ygk współrzędna y Gaussa-Krügera punktu
	  * 
	  * Funkcja odpowiada za realizację odwrtnego odwzorowania Lagrange'a.
	  * Jest to ostatni z etapów potrzebnych do konwersji z dwuwymiarowego systemu współrzędnych na trójwymiarowy.
	  * Funkcja przyjmuje podane przez referencję wartości obliczone za pomocą odwzorowania Mercatora.
	  * Następnie wykonuje obliczenia i zwraca wynik do podanych przez parametr zmiennych wejściowych.
	*/
	void ReverseLagrange(long double& phi, long double& lambda, const long double& E, const long double& ygk) const noexcept;
public:	
	/** \brief Metoda zarządzająca konwersją z systemu WGS84 na PL2000
	  * \param B szerokość geograficzna punktu wyrażona w stopniach
	  * \param L długość geograficzna punktu wyrazona w stopniach
	  * \param N szerokość geograficzna punktu wyrażona w metrach
	  * \param E długość geograficzna punktu wyrażona w  metrach
	  *
	  * Metoda zarządza przebiegiem konwersji z systemu WGS84 na system PL2000.
	  * Przyjmuje dwie wartości B i L określające współrzędne punktu które mają być skonwertowane.
	  * Następnie kolejno wywołuje metody realizujące kolejne odwzorowania matematyczne.
	  * Po czym zwraca otrzymane na skutek przekształceńwartości do zmiennych N i E.
	*/
	void PL2000(const long double& B, const long double& L, long double& N, long double& E) const noexcept;
	
	/** \brief Metoda zarządzająca konwersją z systemu WGS84 na PL2000
	  * \param N szerokość geograficzna punktu wyrażona w metrach
	  * \param E długość geograficzna punktu wyrażona w  metrach
	  * \param B szerokość geograficzna punktu wyrażona w stopniach
	  * \param L długość geograficzna punktu wyrazona w stopniach	
	  *
	  * Metoda zarządza przebiegiem konwersji z systemu PL2000 na system WGS84.
	  * Przyjmuje dwie wartości N i E określające współrzędne punktu które mają być skonwertowane.
	  * Następnie kolejno wywołuje metody realizujące kolejne odwzorowania matematyczne.
	  * Po czym zwraca otrzymane na skutek przekształceńwartości do zmiennych B i L.
	*/
	void WGS84(const long double& N, const long double& E, long double& B, long double& L) const noexcept;
};
/** \brief funkcja konwertująca podaną w stopniach wartość na radiany
  * \param value wartość która ma zostać skonwertowana
  * \return wartość skonwertowana
*/
long double DegToRad(long double value);

/** \brief funkcja konwertująca podaną w stopniach wartość na radiany
  * \param value wartość która ma zostać skonwertowana
  * \return wartość skonwertowana
*/
long double RadToDeg(long double value);