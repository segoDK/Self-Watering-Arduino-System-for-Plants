#ifndef Plant_h
#define Plant_h

#include "Arduino.h"

  class Plant {
    private:
      String plantName; // name of the plant
      int minMoist; // minimum moistlevel in percentage (whole numbers)
      int maxMoist; // maximum moistlevel in percentage (whole numbers)
      int prefDirLight; // prefered duration of direct sunlight per day (minutes)
      int prefIndLight; // prefered duration of indirect sunligt per day (minutes)
      
    public:
      Plant(String plantName, int minMoist, int maxMoist, int prefDirLight) {
        // 'this->' used to make the difference between the attributes of 
        // the class and the local variables created from the parameter.
        this->plantName = plantName;
        this->minMoist = minMoist;
        this->maxMoist = maxMoist;
        this->prefDirLight = prefDirLight;
      }

      void setName(String plantName);
      void setMinMoist(int minMoist);
      void setMaxMoist(int maxMoist);
      void setDirLight(int prefDirLight);
      void setIndLight(int prefIndLight);
      String getName();
      int getMinMoist();
      int getMaxMoist();
      int getDirLight();
      int getIndLight();

  }; // don't forget the semicolon at the end of the class

#endif
