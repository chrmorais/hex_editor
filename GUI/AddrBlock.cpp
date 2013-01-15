#include "AddrBlock.hpp"

AddrBlock::AddrBlock( int aLeft, int aTop, int aWidth, int aHeight ){
  this->setLeft(aLeft);
  this->setTop(aTop);
  this->setWidth(aWidth);
  this->setHeight(aHeight);
}

int AddrBlock::getWidth(void){
  return this->Width;
}

void AddrBlock::setWidth(int aWidth){
  int MinWidth = 9;//минимально допустимая длина

  if( aWidth < MinWidth ){
    this->Width = MinWidth;
  }else{
    this->Width = aWidth;
  }
}

int AddrBlock::getHeight(void){
  return this->Height;
}

void AddrBlock::setHeight(int aHeight){
  if( aHeight < 1 ){
    this->Height = 1;
  }else{
    this->Height = aHeight;
  }
}

int AddrBlock::getLeft(void){
  return this->Left;
}

void AddrBlock::setLeft(int aLeft){
  if(aLeft < 0){
    this->Left = 0;
  }else{
    this->Left = aLeft;
  }
}

// int AddrBlock::getTop(void);
// void AddrBlock::setTop(int aTop);

// void AddrBlock::setEnabled( bool aEnable );
// bool AddrBlock::getEnabled(void);

// void AddrBlock::setBeginAddress( unsigned int aAddress );
// unsigned int AddrBlock::getBeginAddress(void);