class Translation
{
public:
	int row;
	int column;
	int option;
	//0 - default move
	//1 - pawn capture
	//2 - pawn without capture
	//3 - short castling
	//4 - long castling
	Translation(int row, int column);
	Translation(int row, int column, int option);
	virtual ~Translation();
};