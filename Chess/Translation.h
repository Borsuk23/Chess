class Translation
{
public:
	int row;
	int column;
	int captureOnly;
	Translation(int row, int column);
	Translation(int row, int column, bool captureOnly);
	virtual ~Translation();
};