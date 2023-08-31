#include "block.h"
#include <cmath>
#include <iostream>

int Block::height() const {
  /* your code here */
  // The value below returns the number of rows in the 2D vector, 
  // which gives the height of the block
  // Number of rows in the block.
  return data[0].size();
}


int Block::width() const {
  /* your code here */
  // The value below returns the number of columns in the 2D vector, 
  // which gives the width of the block
  // Number of columns in the block.
  return data.size();
}


void Block::render(PNG &im, int x) const {
  /* your code here */
  // The for loop iterates through each row and column and sets the pixel in the image to the value
  // in the data 2D vector
  for (unsigned int y = 0; y < im.height(); y++) {
    for (unsigned int i = x; i < x + width(); i++) {
      *(im.getPixel(i,y)) = data[i-x][y];
      }
      } 
}

void Block::build(PNG &im, int x, int width) {
  /* your code here */
  // The for loop iterates through 
  for (unsigned int i = 0; i < width; i++) {
    // We get the single column of pixels in the image. 
    vector<HSLAPixel> verticalChunks;
    for (unsigned int y = 0; y < im.height(); y++) {
      HSLAPixel* pixel = im.getPixel(i + x,y);
      verticalChunks.push_back(*pixel);
      }
      data.push_back(verticalChunks);
      }   
}
