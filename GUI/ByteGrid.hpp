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

    void setCursorColor( int aColorPair );
    int  getCursorColor(void);
    
    void setColumnSize( int aColumnSize );
    int  getColumnSize(void);
    
    void setCursorPos( int aPos );
    int  getCursorPos(void);
    

    void setByte(int aPos, char aByte);
    char getByte(int aPos);

    void setByteCount( UINT aCount );
    UINT getByteCount(void);
    
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
    int CursorColor;
    int CursorPos;

    std::vector<char> Data;
};