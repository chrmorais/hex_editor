#include "AddrBlock.hpp"

AddrBlock::AddrBlock( int aLeft, int aTop, int aWidth, int aHeight ){
  this->setLeft(aLeft);
  this->setTop(aTop);
  this->setWidth(aWidth);
  this->setHeight(aHeight);

  this->BeginAddress = 0;
  this->Step = 4;

  this->Enabled = true;

};

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

int AddrBlock::getTop(void){
  return this->Top;
}

void AddrBlock::setTop(int aTop){
  if( aTop < 0 ){
    this->Top = 0;
  }else{
    this->Top = aTop;
  }
}

void AddrBlock::setEnabled( bool aEnable ){
  this->Enabled = aEnable;
}

bool AddrBlock::getEnabled(void){
  return this->Enabled;
}

void AddrBlock::setBeginAddress( unsigned int aAddress ){
  this->BeginAddress = aAddress;
}

unsigned int AddrBlock::getBeginAddress(void){
  return this->BeginAddress;
}

int AddrBlock::getStep(void){
  return this->Step;
}

void AddrBlock::setStep( int aStep ){
  this->Step = aStep;
}

void AddrBlock::Paint(void) const{
  if(this->Enabled){    

    unsigned int CurAddress = this->BeginAddress;

    for( int row = 0; row < this->Height; row++ ){
      move( this->Top + row, this->Left );
      printw("%08X", CurAddress );
      CurAddress += this->Step;
    }
  }
}