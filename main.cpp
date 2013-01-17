#include <stdlib.h>
#include <stdio.h>

#include <ncurses.h>

#include "GUI/AddrBlock.hpp"
//#include "ncurses_utils.hpp"

using namespace std;

int main( int argc, const char* argv[] ){


  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  
  start_color();
  //bkgdset(COLOR_PAIR(1));
  int maxx = getmaxx(stdscr);
  int maxy = getmaxy(stdscr);
  
  init_pair(1, COLOR_YELLOW, COLOR_BLUE);
  init_pair(2, COLOR_WHITE, COLOR_BLUE );
  bkgdset(COLOR_PAIR(1));
  clear();
  attron(A_BOLD);
  //attron(COLOR_PAIR(1));
  
  AddrBlock *GUI_Addr = new AddrBlock( 0,1,9,maxy-2 );
  GUI_Addr->setSelectColor(2);
  GUI_Addr->setSelectAddress(0);
  GUI_Addr->Paint();
  
  attron(COLOR_PAIR(2));
  move(1, 10);
  vline(ACS_VLINE,37);
  //attron(COLOR_PAIR(2));
  //move(15,15);
  //addch(ACS_VLINE);
  //addchnstr("hello",-1);

  refresh(); // обновить
  
  while(true){
    int key = getch();

    switch(key){
      case KEY_DOWN:
        GUI_Addr->setSelectAddress( GUI_Addr->getSelectAddress() + 1 );
        break;
      case KEY_UP:
        GUI_Addr->setSelectAddress( GUI_Addr->getSelectAddress() - 1 );
        break;
    }

    if( key == 113 ){
      break;
    }
    GUI_Addr->Paint();
    refresh();
  }
  delete GUI_Addr;
  
  endwin(); // завершение работы с ncurses  
}