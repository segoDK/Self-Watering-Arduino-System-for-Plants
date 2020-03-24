#include "Arduino.h"
#include "Plant.h"
  

void Plant::setName(String plantName) {
  this->plantName = plantName;
}
void Plant::setMinMoist(int minMoist) {
  this->minMoist = minMoist;
}
void Plant::setMaxMoist(int maxMoist) {
  this->maxMoist = maxMoist;
}
void Plant::setDirLight(int prefDirLight) {
  this->prefDirLight = prefDirLight;
}
void Plant::setIndLight(int prefIndLight) {
  this->prefIndLight = prefIndLight;
}

String Plant::getName() {
  return(this->plantName);
}
int Plant::getMinMoist() {
  return(this->minMoist);
}
int Plant::getMaxMoist() {
  return(this->maxMoist);
}
int Plant::getDirLight() {
  return(this->prefDirLight);
}
int Plant::getIndLight() {
  return(this->prefIndLight);
}
