#include "qt.h"

void QTCompressor::writeToFile()
{
  std::ofstream outfile("resultant.txt", std::ios::binary);
  outfile << "TEST.";
  std::cout << "[+] Wrote to file.\n";
  outfile.close();
}

void QTCompressor::splitArray()
{

}

void QTCompressor::paintQt()
{

}

double QTCompressor::getVariance()
{
  return -1;
}

int QTCompressor::getMeanSum()
{
  return -1;
}

void QTCompressor::getHeaderInfo()
{
  std::stringstream ss;
  std::ifstream infile("baboon.pgma", std::ios::binary);

  getline(infile, _version);
  getline(infile, _comments);
  ss << infile.rdbuf();
  ss >> _height >> _width >> _maxVal;
  /*
  for(int row = 0; row < _height; ++row)
  {
    for(int col = 0; col < _width; ++col)
    {
      ss >> img[row][col];
    }
  }
  */
  infile.close();
}

void QTCompressor::createArray()
{

}
