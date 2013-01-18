#include "ByteGrid.hpp"

ByteGrid::ByteGrid( int aLeft, int aTop, int aWidth, int aHeight ){
  this->setLeft(aLeft);
  this->setTop(aTop);
  this->setWidth(aWidth);
  this->setHeight(aHeight);

  this->Enabled = true;

  this->ColSize = 4;

  this->DefaultColor = 1;
  this->SelectColor  = 2;
  this->SelectCellPos = -1;  
}

void ByteGrid::Clear(void){
  for( int byteinx=0; byteinx < this->Data.size(); byteinx++ ){
    this->Data.at(byteinx) = (char)0;
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

void ByteGrid::setSelectColor( int aColorPair ){
  this->SelectColor = aColorPair;
}

int ByteGrid::getSelectColor(void){
  return this->SelectColor;
}

void ByteGrid::setColumnSize( int aColumnSize ){
  this->ColSize = aColumnSize;
}

int ByteGrid::getColumnSize(void){
  return this->ColSize;
}

void ByteGrid::setByte(int aPos, char aByte){
  if( aPos < this->Data.size() && aPos > -1 ){
    this->Data.at(aPos) = aByte;
  }
}

char ByteGrid::getByte(int aPos){
  if( aPos < this->Data.size() && aPos > -1 ){
    return this->Data.at(aPos);
  }
}

void ByteGrid::setActiveCell( int aPos ){  
  this->SelectCellPos = aPos;
}

int ByteGrid::getActiveCell(void){
  return this->SelectCellPos;
}

void ByteGrid::Paint(void) const{
  if( this->Enabled ){

  }
}