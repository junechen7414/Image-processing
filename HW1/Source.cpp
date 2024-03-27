#include <iostream> 
#include <fstream> 
#include <sstream> // getline
#include <vector>
#include <cmath>
using namespace std;

int main() {
	int row = 0, col = 0, numrows = 0, numcols = 0;
	ifstream PGM("lena.pgm");
	ofstream equalized("equalized.pgm");
	if (PGM.fail() || equalized.fail())
	{
		cout << "file open failed";
		exit(1);
	}	
	string inputLine = "";
	// First line : pgm 
	getline(PGM, inputLine);
	if (inputLine.compare("P2") != 0) return 0;
	else equalized << inputLine << '\n';

	// Second line : comment
	getline(PGM, inputLine);
	equalized << inputLine << endl;
		
	// Third line : size
	PGM >> numcols >> numrows;
	equalized << numcols << " " << numrows << endl;

	//Fourth line : max number pixel
	PGM >> inputLine;	

	vector<int> temp(numcols);
	vector<vector<int>> pic; pic.resize(numrows, temp);
	
	long double *counting =new long double[256];	
	for (int i = 0; i < 256; i++) counting[i] = 0;
	int x = 0, y = 0;
	while (!PGM.eof()&& x< numrows)
	{
		PGM >> pic[x][y];
		y++;		
		if (y == numcols) {
			x++;
			y = 0;
		}				
	}
	// Following lines : data
	for (row = 0; row < numrows; row++)
		for (col = 0; col < numcols; col++) 
			counting[pic[row][col]]++;
	
	double sum = 0,MN = numcols*numrows;	
	for (int i = 0; i < 256; i++){
		counting[i] = counting[i] / MN;
		sum = sum + counting[i];
		counting[i] =round(sum*255);		
	}
	equalized << 255 << endl; //max pixel number changed
	int index =0;
	int *countafter = new int[256];
	for (int i = 0; i < 256; i++) countafter[i] = 0;
	for (int i = 0; i < numrows; i++)
	{
		for (int j = 0; j < numcols; j++) {			
		pic[i][j] = counting[pic[i][j]];
		countafter[pic[i][j]]++;
		if (index > 10)
		{
			equalized << pic[i][j] << ' '<<endl;
			index = 0;
		}		
		else
			equalized << pic[i][j] <<"  ";
		index++;
	}
	index = 1;
	equalized << endl;
	}	
	delete[] counting; temp.clear(); temp.shrink_to_fit(); pic.clear(); pic.shrink_to_fit(); delete[] countafter;
	PGM.close(); equalized.close();
	system("PAUSE");
	return 0;
}