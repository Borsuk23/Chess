class Translation
{
public:
	int row;
	int column;
	int option;
	//0 - domyslne
	//1 - bicie
	//2 - roszada
	Translation(int row, int column);
	Translation(int row, int column, int option);
	virtual ~Translation();
};