/*
 Класс работы с одноцветным светодиодом, включаемым логическим 0
 */
#ifndef C_LED
#define C_LED
 //========================================================================
 //---------------------------- ПОДКЛЮЧАЕМЫЕ ФАЙЛЫ ------------------------
 //========================================================================
 
 //========================================================================
 //-------------------------------- КОНСТАНТЫ -----------------------------
 //========================================================================

 //========================================================================
 //--------------------------- ОБЪЯВЛЕНИЕ КЛАССОВ -------------------------
 //========================================================================
 
class cLed{
 
 //------------------------------------------------------------------------
 // Атрибуты
 //------------------------------------------------------------------------
 
 int Line;	    //Линии сигналов
   
 char Name;     //Имя элемента
 bool State;    //Признак состояния
 
 public:
 //------------------------------------------------------------------------
 // Методы
 //------------------------------------------------------------------------
 
 void install(
    char nameX, 
    int line_red
  );     

 void lightness();
 void darkness();
 void setState(bool x);
 char getState();
 
 //------------------------------------------------------------------------
 // Конструкторы
 //------------------------------------------------------------------------
 cLed();
 
};//End of class cLed

 //========================================================================
 //--------------------------- РЕАЛИЗАЦИЯ МЕТОДОВ -------------------------
 //========================================================================

//
// Конструктор
//
cLed::cLed() 
{
  //...
} 

//
// Начальная установка
//
void cLed::install(
    char nameX,
    int line
    ) 
{
  this->Line = line;
  this->State = false;

  pinMode(this->Line, OUTPUT);

} 

//
// Установка состояния
//
void cLed::setState(bool x)
{
  this->State = x;
  if(this->State)
    this->lightness();
  else
    this->darkness();  
}

//
// Чтение состояния
//

char cLed::getState()
{
    if(this->State) return 1; else return 0;
}


//
// Реализация методов управления светом
//
 void cLed::lightness()
 {
    digitalWrite(this->Line, HIGH);  
 }

 void cLed::darkness()
 {
    digitalWrite(this->Line, LOW);  
 }

//--------------------------------------------------------------------------------
#endif