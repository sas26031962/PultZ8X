/*
 Класс описания поведения светодиодов (дисплея)
 */
#ifndef C_DISPLAY
#define C_DISPLAY
 //========================================================================
 //---------------------------- ПОДКЛЮЧАЕМЫЕ ФАЙЛЫ ------------------------
 //========================================================================
#include "cLED.h"

 //========================================================================
 //-------------------------------- КОНСТАНТЫ -----------------------------
 //========================================================================
 

 
 //========================================================================
 //--------------------------- ОБЪЯВЛЕНИЕ КЛАССОВ -------------------------
 //========================================================================
 
class cDisplay{
 
 //------------------------------------------------------------------------
 // Атрибуты
 //------------------------------------------------------------------------
 public:
 static cLed Led1;  //
 static cLed Led2;  //
 static cLed Led3;  //
 static cLed Led4;  //
 static cLed Led5;  //
 static cLed Led6;  //
 static cLed Led7;  //
 static cLed Led8;  //
 static cLed Led9;  //
 static cLed Led10;  //
 static cLed Led11;  //

 //------------------------------------------------------------------------
 // Методы
 //------------------------------------------------------------------------
 protected:

 public:
 static void install();
 static void parseKeyCodeField( char c, bool state );

 void exec(); 
  
 //------------------------------------------------------------------------
 // Конструкторы
 //------------------------------------------------------------------------
 cDisplay();
 
};//End of class cDisplay
 //========================================================================
 //--------------------------- РЕАЛИЗАЦИЯ МЕТОДОВ -------------------------
 //========================================================================

//
// Конструктор
//
cDisplay::cDisplay(
    )
{
  //...
} 
//------------------------------------------------------------------
void cDisplay::install()
{
  Led1.install('A', LED1);
  Led2.install('B', LED2);
  Led3.install('C', LED3);
  Led4.install('D', LED4);
  Led5.install('E', LED5);
  Led6.install('F', LED6);
  Led7.install('G', LED7);
  Led8.install('H', LED8);
  Led9.install('I', LED9);
  Led10.install('J', LED10);
  Led11.install('K', LED11);

  // Задержка
  delay(300);
  
  // Погасить светодиоды
  Led1.darkness();
  Led2.darkness();
  Led3.darkness();
  Led4.darkness();
  Led5.darkness();
  Led6.darkness();
  Led7.darkness();
  Led8.darkness();
  Led9.darkness();
  Led10.darkness();
  Led11.darkness();
  
}//End of void cDisplay::install()
//------------------------------------------------------------------
void cDisplay::exec()
{

}//End of void cDisplay::exec()

//
// Функция разбора принятых данных
//

void cDisplay::parseKeyCodeField( char c, bool state )
{
      switch(c)
      {
        case 1:
        Led1.setState(state);
         break;
        
        case 2:
        Led2.setState(state);
        break;
        
        case 3:
        Led3.setState(state);
         break;
        
        case 4:
        Led4.setState(state);
        break;
        
        case 5:
        Led5.setState(state);
        break;
        
        case 6:
        Led6.setState(state);
        break;
        
        case 10:
        Led7.setState(state);
         break;
        
        case 11:
        Led8.setState(state);
         break;
        
        case 12:
        Led9.setState(state);
        break;
        
        case 13:
        Led10.setState(state);
        break;
        
        case 14:
        Led11.setState(state);
        break;
        
      }

}//End of void parseKeyCodeField( char c, bool state )

//--------------------------------------------------------------------------------
//----------------------------------ОБЪЯВЛЕНИЕ СТАТИЧЕСКИХ ПЕРЕМЕННЫХ-------------
//--------------------------------------------------------------------------------

cLed cDisplay::Led1;  //
cLed cDisplay::Led2;  //
cLed cDisplay::Led3;  //
cLed cDisplay::Led4;  //
cLed cDisplay::Led5;  //
cLed cDisplay::Led6;  //
cLed cDisplay::Led7;  //
cLed cDisplay::Led8;  //
cLed cDisplay::Led9;  //
cLed cDisplay::Led10;  //
cLed cDisplay::Led11;  //

//--------------------------------------------------------------------------------
#endif
