#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

class QTCompressor
{
  /* VARIABLES FOR PGMA FILE */
  int _height,
      _width,
      _x,
      _y,
      _maxVal;

  std::string _version,
         _comments;

  std::vector<std::vector<int>> img(_height, std::vector<int> (_width));


public:

  std::string getStuff() { return _comments; }

  void writeToFile();
  void splitArray();
  void paintQt();
  double getVariance();
  int getMeanSum();
  void getHeaderInfo();
  void createArray();

};
