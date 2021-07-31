#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

class QTCompressor
{
  /* VARIABLES FOR PGMA FILE */
  int _height = 0,
      _width = 0,
      _x,
      _y,
      _maxVal;

  std::string _version,
         _comments;
         int idsf=12;
  std::vector<std::vector<int>> img = std::vector<std::vector<int>>(_height, std::vector<int> (_width));


public:

  std::string getStuff()
  {
    return _comments +
          "\nHeight: " +
          std::to_string(_height) +
          "\nWidth: " +
          std::to_string(_width) +
          "\n";
  }

  void writeToFile();
  void splitArray();
  void paintQt();
  double getVariance();
  int getMeanSum();
  void getHeaderInfo();
  void createArray();

};
