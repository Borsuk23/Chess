/*!
* \brief Translation class klasa definiuj¹ca mo¿liwe translacje ruchów
*/
class Translation
{
public:
	int row;	//! wiersz
	int column;		//! kolumn
	int option;		//!  opcja ruchu
	//0 - default move
	//1 - pawn capture
	//2 - pawn without capture
	//3 - short castling
	//4 - long castling
	/*!
	* \brief Translation konstruktor sparametryzowany
	* \param row wiersz
	* \param kolumna
	*/
	Translation(int row, int column);
	/*!
	* \brief Translation konstruktor sparametryzowany
	* \param row wiersz
	* \param kolumna
	* \param opcja ruchu
	*/
	Translation(int row, int column, int option);
	/*!
	* \brief Translation destruktor
	*/
	virtual ~Translation();
};