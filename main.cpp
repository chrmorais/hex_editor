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
  
  AddrBlock *GUI_Addr = new AddrBlock( 1,1,9,10 );

  move(10,0);
  printw("%08X",GUI_Addr->getLeft() );
  delete GUI_Addr;

  move(0,0);
  printw("%08X",0); // вывод строки
  move(1,0);
  printw("%08X",15); // вывод строки
  move(2,0);
  printw("%08X",31); // вывод строки
  move(3,0);
  printw("%08X",47); // вывод строки 
  
  
  //addchnstr("hello",-1);

  refresh(); // обновить
  
  getch(); // ждём нажатия символа
  
  endwin(); // завершение работы с ncurses  
}