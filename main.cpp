#include <stdlib.h>
#include <stdio.h>

#include <ncurses.h>
#include "GUI/AddrBlock.hpp"

using namespace std;

int main( int argc, const char* argv[] ){


  initscr();


  start_color();
  //bkgdset(COLOR_PAIR(1));
  int maxx = getmaxx(stdscr);
  int maxy = getmaxy(stdscr);
  
  init_pair(1, COLOR_YELLOW, COLOR_BLUE);
  attron(A_BOLD);
  attron(COLOR_PAIR(1));
  
  AddrBlock *GUI_Addr = new AddrBlock( 0,1,9,maxy-2 );
  GUI_Addr->Paint();
  
  delete GUI_Addr;
  
  //addchnstr("hello",-1);

  refresh(); // обновить
  
  getch(); // ждём нажатия символа
  
  endwin(); // завершение работы с ncurses  
}