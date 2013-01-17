#include <stdlib.h>
#include <stdio.h>

#include <ncurses.h>

using namespace std;

class AddrBlock{
  
  public:
        
    AddrBlock( int aLeft, int aTop, int aWidth, int aHeight );

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

    void setBeginAddress( unsigned int aAddress );
    unsigned int getBeginAddress(void);
    
    void setStep(int aStep);
    int getStep(void);
    
    void setColor( int aColorPair );
    int  getColor(void);

    void setSelectColor( int aColorPair );
    int  getSelectColor(void);
     
    void setSelectAddress( int aAddressIndex );
    int  getSelectAddress(void);

    void Paint(void) const;
  
  private:
    int Left;
    int Top;
    int Width;
    int Height;

    bool Enabled;

    unsigned int BeginAddress;
    int Step;

    int DefaultColor;
    int SelectColor;
    int SelectAddressIndex;
};