#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include "Plant.h"

  class Display {  
  private: 
  
  public:
    // variables for lcd display
    String topTxt; int topTxtLenght; int topPlantNum; 
    String botTxt; int botTxtLenght; int botPlantNum;
    int cursorLocation;
    String cursorIcon;
    Plant plants[];
    
    Display() {
      this->topTxt = "";
      this->topTxtLenght = 0;
      this->topPlantNum = 0;
      this->botTxt = "";
      this->botTxtLenght = 0;
      this->botPlantNum = 0;
      this->cursorLocation = 0;
      this->cursorIcon = "<--";
      // this->plants[] = plants[];
      /*
      for(int i = 0; i < (5); i++){
        this->plants[i] = plants[i];
      }
      */
      /*
      plants[0] = new Plant("Mint", 20, 40, 2*60);
      plants[1] = new Plant("Ginger", 20, 40, 2*60);
      plants[2] = new Plant("Sunflower", 20, 40, 4*60);
      plants[3] = new Plant("Cactus", 0, 20, 5*60);
      plants[4] = new Plant("Rosemary", 20, 40, 2*60);
      */
    }


    void updatePlants(int topPlant, int botPlant);
    void updateTxt(String topText, String botText);
    void updateCursor(int line);
    
    void scrollDown();
    void scrollUp();
    
    String getTopTxt();
    String getBotTxt();

    void addPlant(Plant plant);
    
  }; // don't forget the semicolon at the end of the class

#endif
