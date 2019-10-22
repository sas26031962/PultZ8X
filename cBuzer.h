/*
 Класс работы с зуммером ПЗ
 */
#ifndef C_BUZER
#define C_BUZER
 //========================================================================
 //---------------------------- ПОДКЛЮЧАЕМЫЕ ФАЙЛЫ ------------------------
 //========================================================================
 
 //========================================================================
 //-------------------------------- КОНСТАНТЫ -----------------------------
 //========================================================================
  
 //========================================================================
 //--------------------------- ОБЪЯВЛЕНИЕ КЛАССОВ -------------------------
 //========================================================================
 
class cBuzer{
 
 //------------------------------------------------------------------------
 // Атрибуты
 //------------------------------------------------------------------------

 
 char Name;               // Имя объекта
 int Line;			      // Линия ввода данных
 
 bool Current;		      // Текущее состояние линии
 
 public:

 
 //------------------------------------------------------------------------
 // Методы
 //------------------------------------------------------------------------

 public:
 
 void beep();  // Реализация звукового пика
 void pic();  // Реализация звукового пика

 
 void install(char nameX, int line);
 
 //------------------------------------------------------------------------
 // Конструкторы
 //------------------------------------------------------------------------
 cBuzer();
 
};//End of class cBuzer

 //========================================================================
 //--------------------------- РЕАЛИЗАЦИЯ МЕТОДОВ -------------------------
 //========================================================================

//
// Конструктор
//
cBuzer::cBuzer(
    )
{
  //...
} 

//
// Начальная установка
//
void cBuzer::install(
    char nameX,
    int line
  )
{
  pinMode(line, OUTPUT);
  this->Name = nameX;
  this->Line = line;
  
  this->Current = HIGH;
}

//
// Реализация функциональности
//
void cBuzer::beep()
{
  tone(PIN_PIEZO, TONE_FREQUENCY, TONE_DWELL);
}

//
// Генерация события
//
 void cBuzer::pic()
 {
  this->Current = !this->Current;
  digitalWrite(PIN_PIEZO, this->Current);
 }

//--------------------------------------------------------------------------------
#endif
