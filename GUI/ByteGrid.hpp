#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include <ncurses.h>

typedef unsigned int UINT;


class ByteGrid{
  public:
    ByteGrid( int aLeft, int aTop, int aWidth, int aHeight );

    int getWidth(void);
    void setWidth(int aWidth);
    
    int getHeight(void);
    void setHeight(int aHeight);

    int getLeft(void);
     void setLeft(int aLeft);
    
    int getTop(void);
    void setTop(int aTop);

    void setEnabled( bool aEnable );
    bool getEnabled(void);

    void setColor( int aColorPair );
    int  getColor(void);

    void setSelectColor( int aColorPair );
    int  getSelectColor(void);
    
    void setColumnSize( int aColumnSize );
    int  getColumnSize(void);
    
    void setActiveCell( int aPos );
    int  getActiveCell(void);
    
    void setByte(int aPos, char aByte);
    char getByte(int aPos);
    
    void Clear( void );

    void Paint(void) const;

  private:
    int Left;
    int Top;
    int Width;
    int Height;

    bool Enabled;
    
    int ColSize;

    int DefaultColor;
    int SelectColor;
    int SelectCellPos;

    std::vector<char> Data;
};