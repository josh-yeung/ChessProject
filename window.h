#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <png.h>
#include <vector>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[14];

 public:
  Xwindow(int width=500, int height=500);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.
  Xwindow(const Xwindow&) = delete;
  Xwindow &operator=(const Xwindow&) = delete;

  // Available colours.
  //enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};
  enum {Black=0, White, Red, Firebrick, Green, Olive, Blue, SkyBlue, Cyan, Teal, Yellow, Orange, Magenta, Violet};

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);

  void drawImage(int x, int y, const std::string& filename);

};

#endif
