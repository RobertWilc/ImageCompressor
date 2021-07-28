#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
using namespace std;


/* THE THRESHOLD FOR HOW HIGH QUALITY YOU WANT THE IMAGE TO BE. *
 * The lower THRESHOLD is, the higher the quality.              */
int THRESHOLD = 256;

/* READS IMAGE FILE INTO 2D VECTOR ARRAY */
void createArray(vector<vector<int>>& array, int width, int height,  stringstream& ss)
{
    for(int row = 0; row < height; ++row)
    {
        for(int col = 0; col < width; ++col)
        {
            ss >> array[row][col];
        }
    }
}

/* WRITES HEADER INFO INTO VARIABLES */
void getHeaderInfo( string& version,
                    string& comments,
                    int& numrows,
                    int& numcols,
                    int& max_val,
                    stringstream& ss,
                    ifstream& infile)
{
    getline(infile,version); //Reads the first line : PGM Version

    getline(infile,comments); //Reads the second line : Comment

    ss << infile.rdbuf(); //Reads the third line : width and height
    ss >> numcols >> numrows;

    ss >> max_val; //Reads the 4th line : maximum value 0-255
}

/* Gets the average sum of all  *
 * the pixels in the given area */
int getMeanSum(vector<vector<int>>& img, int x, int y, int width, int height)
{
	int meanSum = 0;
	for(int i = y; i < y + height; i++)
    {
        for(int j = x; j < x + width; j++)
        {
            meanSum += img[i][j];
        }
    }

    return meanSum;
}

/* Gets the variance sum of all the pixels in  *
 * the given area                              */
double getVariance(vector<vector<int>>& img, int x, int y, int width, int height, int average)
{
	int varianceSum = 0;
    for(int i = y; i < y + height; i++)
    {
        for(int j = x; j < x + width; j++)
        {
            varianceSum += ((img[i][j] - average) * (img[i][j] - average));
        }
    }
    return varianceSum;
}

/* Function that paints the given area the *
 * mean of all the pixels in the area.     */
void paintQt(vector<vector<int>>& img, int x, int y, int width, int height, int average)
{
	for(int i = y; i < y + height; i++)
    {
        for(int j = x; j < x + width; j++)
        {
            img[i][j] = average;
        }
    }
}

/*  WHERE THE MAGIC HAPPENS!							    *
 *  Checks to make sure the quadrant is bigger than 1(1)    *
 *  If it is then is continues and checks to see if the     *
 *  variance is under the threshold(2). If it is under the  *
 *  threshold then it replaces the pixels with the mean     *
 *  pixel color(3). If it is not then splitArray is called  *
 *  again until the variance is under the threshold(4).     */
void splitArray(vector<vector<int>>& img, int x, int y, int width, int height)
{
	/* (1) */
    if(height == 1 && width == 1)
    {
        return;
    }

    /* VARIABLES FOR QUADRANT */
    int area = height * width;
    int meanSum = getMeanSum(img, x, y, width, height);
    int average = meanSum/area;
    double varianceSum = getVariance(img, x, y, width, height, average);
    double v = varianceSum / (area - 1);

    /* (2) */
    if (v <= THRESHOLD)
    {
    	/* (3) */
    	paintQt(img, x, y, width, height, average);
        return;
    }
    else
    {
    	/* (4) */
        splitArray(img, x, y, width/2, height/2); //Top left Quadrant
        splitArray(img, x + width/2, y, width/2, height/2); //Top right Quadrant
        splitArray(img, x, y + height/2, width/2, height/2); //Bottom left quadrant
        splitArray(img, x + width/2, y + height/2, width/2, height/2); //Bottom right quadrant
    }
}

/* WRITES FINISHED QUADIMAGE TO FILE */
void writeToFile(vector<vector<int>> img, string version, string comments, int width, int height, int max_val)
{
	ofstream outfile("resultant.pgma", ios::binary);
    outfile << version << '\n' << comments << '\n' << width << " " << height << '\n' << max_val << '\n';

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            outfile << img[i][j] << " ";
        }
        outfile << '\n';
    }
    cout << "[+] Created QuadImage . . ." << endl;
    outfile.close();
}


int main() {

    /* VARIABLES FOR PGMA FILE */
    int height = 0;
    int width = 0;
    int x = 0;
    int y = 0;
    string version = "";
    string comments = "";
    int max_val = 0;

	/* READS IMAGE FILE AND STORES HEADER INFORMATION */
    stringstream ss; //Used to read the image into variables.
    ifstream infile("baboon.pgma", ios::binary); //Opens the image
    getHeaderInfo(version, comments, height, width, max_val, ss, infile);

    /* THE TWO DIMENSIONAL VECTOR ARRAY OF IMAGE  *
     * Each pixel is a number from 0-255          */
    vector<vector<int>> img(height, vector<int> (width));

    createArray(img, width, height, ss);
    splitArray(img, x, y, width, height);

    writeToFile(img, version, comments, width, height, max_val);

    return 0;
}
