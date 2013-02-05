#include "ByteGrid.hpp"

ByteGrid::ByteGrid( int aLeft, int aTop, int aWidth, int aHeight ){
  this->setLeft(aLeft);
  this->setTop(aTop);
  this->setWidth(aWidth);
  this->setHeight(aHeight);

  this->Enabled = true;

  this->ColSize = 4;

  this->DefaultColor = 1;
  this->CursorColor  = 2;
  this->CursorPos = -1;  
}

void ByteGrid::Clear(void){
  for( UINT byteinx=0; byteinx < this->Data.size(); byteinx++ ){
    this->Data.at(byteinx) = 0;
  }
}

int ByteGrid::getWidth(void){
  return this->Width;
}

void ByteGrid::setWidth(int aWidth){
  if( aWidth >= 0 ){
    this->Width = aWidth;  
  }else{
    this->Width = 0;
  }
}

int ByteGrid::getHeight(void){
  return this->Height;
}

void ByteGrid::setHeight(int aHeight){
  if( aHeight >= 0 ){
    this->Height = aHeight;
  }else{
    this->Height = 0;
  }
}

int ByteGrid::getLeft(void){
  return this->Left;
}

void ByteGrid::setLeft(int aLeft){
  if( aLeft >= 0){
    this->Left = aLeft;
  }else{
    this->Left = 0;
  }
}

int ByteGrid::getTop(void){
  return this->Top;
}

void ByteGrid::setTop(int aTop){
  if( aTop >= 0 ){
    this->Top = aTop;
  }else{
    this->Top = 0;
  }
}

void ByteGrid::setEnabled( bool aEnable ){
  this->Enabled = aEnable;
} 

bool ByteGrid::getEnabled(void){
  return this->Enabled;
}

void ByteGrid::setColor( int aColorPair ){
  this->DefaultColor = aColorPair;
}

int ByteGrid::getColor(void){
  return this->DefaultColor;
}

void ByteGrid::setCursorColor( int aColorPair ){
  this->CursorColor = aColorPair;
}

int ByteGrid::getCursorColor(void){
  return this->CursorColor;
}

void ByteGrid::setColumnSize( int aColumnSize ){
  this->ColSize = aColumnSize;
}

int ByteGrid::getColumnSize(void){
  return this->ColSize;
}

void ByteGrid::setByte(UINT aPos, BYTE aByte){
  if( aPos < this->Data.size() ){
    this->Data.at(aPos) = aByte;
  }
}

BYTE ByteGrid::getByte(UINT aPos){
  if( aPos < this->Data.size() ){
    return this->Data.at(aPos);
  }

  return 0;
}

void ByteGrid::setCursorPos( int aPos ){  
  if(aPos < -1){
    this->CursorPos = 0;
    return;
  }
  
  if( aPos >= (int)this->getByteCount() ){
    this->CursorPos = (int)this->getByteCount()-1;
    return;
  }

  this->CursorPos = aPos;
  
}

int ByteGrid::getCursorPos(void){
  return this->CursorPos;
}

void ByteGrid::setByteCount( UINT aCount ){
  this->Data.resize(aCount);
}

UINT ByteGrid::getByteCount(void){
  return this->Data.size();
}

UINT ByteGrid::getByteInRow(void){
  int ColumnWidth = (this->ColSize*2) + this->ColSize + 2;
  int ColumnCount = this->Width / ColumnWidth;

  return UINT(ColumnCount * this->ColSize);
}

void ByteGrid::setFillWidth(void){
  int ColumnWidth = (this->ColSize*2) + this->ColSize + 2;
  int ColumnCount = this->Width / ColumnWidth;

  this->Width = ColumnCount * ColumnWidth;
}


void ByteGrid::Paint(void) const{
  if( this->Enabled && this->Data.size() != 0 ){    
    UINT ColumnWidth = (UINT)(this->ColSize*2) + this->ColSize + 2;
    UINT ColumnCount = (UINT)this->Width / ColumnWidth;//кол-во отображаемых столбцов
    UINT RowCount = this->Data.size() / (ColumnCount * this->ColSize) + 1;
    UINT ActiveByte = 0;
    
    //не должно выходить за границы
    if(RowCount > (UINT)this->Height){
      RowCount = (UINT)this->Height;
    }

    attron(COLOR_PAIR(this->DefaultColor));

    //выводим данные 
    for( UINT rowinx=0; rowinx<RowCount; rowinx++ ){

      for( UINT colinx=0; colinx<ColumnCount; colinx++ ){    
        
        move(this->Top+rowinx,this->Left+(colinx*ColumnWidth));
        
        for( UINT byteinx=0; byteinx<(UINT)this->ColSize; byteinx++ ){
          printw(" ");
          
          if( ActiveByte == (UINT)this->CursorPos ){
             attron(COLOR_PAIR(this->CursorColor));
          }

          printw("%02X", this->Data.at(ActiveByte) );
          
          attron(COLOR_PAIR(this->DefaultColor));
          ActiveByte++;
          if( ActiveByte >= this->Data.size() ) break;
          
        }
        
        if( ActiveByte >= this->Data.size() ) break;
      }

      if( ActiveByte >= this->Data.size() ) break;
    }

    if(ColumnCount == 0){ return; }
    //рисуем ограничители столбцов
    for( UINT col=1; col <= ColumnCount-1; col++ ){
      if( this->Left + (int)(ColumnWidth*col) < this->Width ){
        move(this->Top,this->Left+(ColumnWidth*col)-1);
        vline(ACS_VLINE,this->Height);
      }
    }
  
  }
}