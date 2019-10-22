/*
 Класс описания поведения клавиатуры
 */
#ifndef C_KEYBOARD
#define C_KEYBOARD
 //========================================================================
 //---------------------------- ПОДКЛЮЧАЕМЫЕ ФАЙЛЫ ------------------------
 //========================================================================
#include "cKey.h"

 //========================================================================
 //-------------------------------- КОНСТАНТЫ -----------------------------
 //========================================================================
 

 
 //========================================================================
 //--------------------------- ОБЪЯВЛЕНИЕ КЛАССОВ -------------------------
 //========================================================================
 
class cKeyboard{
 
 //------------------------------------------------------------------------
 // Атрибуты
 //------------------------------------------------------------------------
 public:
 static cKey Key1; //Тумблер "ВКЛ ПЗ"
 static cKey Key2; //Кнопка "МФС"
 static cKey Key3; //Кнопка "УАС"  
 static cKey Key4; //Кнопка "БПС"
 static cKey Key5; //Кнопка "ОФС"  
 static cKey Key6; //Кнопка "БР" 
 static cKey Key7; //"АВАРИЯ СТОП" 
 static cKey Key8; //"ХОД / ЗАПИСЬ" 
 static cKey Key9; //"РАЗГРУЗКА БП"
 static cKey Key10;//"РАБОТА ПЗ" 

 //------------------------------------------------------------------------
 // Методы
 //------------------------------------------------------------------------
 protected:
 static void execKey1();
 static void execKey2();
 static void execKey3();
 static void execKey4();
 static void execKey5();
 static void execKey6();
 static void execKey7();
 static void execKey8();
 static void execKey9();
 static void execKey10();

 public:
 static void install();

 void exec(); 
  
 //------------------------------------------------------------------------
 // Конструкторы
 //------------------------------------------------------------------------
 cKeyboard();
 
};//End of class cKeyboard

 //========================================================================
 //--------------------------- РЕАЛИЗАЦИЯ МЕТОДОВ -------------------------
 //========================================================================

//
// Конструктор
//
cKeyboard::cKeyboard(
    )
{
  //...
} 

void cKeyboard::install()
{
  Key1.install('a', KEY_1);
  pinMode(KEY_1, INPUT_PULLUP);
    
  Key2.install('b', KEY_2);
  pinMode(KEY_2, INPUT_PULLUP); 
   
  Key3.install('c', KEY_3);
  pinMode(KEY_3, INPUT_PULLUP); 
   
  Key4.install('d', KEY_4);
  pinMode(KEY_4, INPUT_PULLUP); 
   
  Key5.install('e', KEY_5);
  pinMode(KEY_5, INPUT_PULLUP);  
  
  Key6.install('f', KEY_6);
  pinMode(KEY_6, INPUT_PULLUP);  
  
  Key7.install('g', KEY_7);
  pinMode(KEY_7, INPUT_PULLUP);  

  Key8.install('h', KEY_8);
  pinMode(KEY_8, INPUT_PULLUP);  

  Key9.install('i', KEY_9);
  pinMode(KEY_9, INPUT_PULLUP);  

  Key10.install('j', KEY_10);
  pinMode(KEY_10, INPUT_PULLUP);  
  
}//End of void cKeyboard::install()
//------------------------------------------------------------------
void cKeyboard::execKey1()
{
  if(cKeyboard::Key1.checkEvent())
  {
    //--- Отправка сообщения об изменении состояния клавиши ---
    // Дескриптор исходящего пакета
    if(!cKeyboard::Key1.getValue() == 0)
       cEthernet::releaseBaseProtocol(101);
    else
       cEthernet::releaseBaseProtocol(102);
    // Код клавиши   
    cEthernet::AnswerBuffer[ 1 + BASE_HEADER_LENGTH ] = 1;//Код клавиши                   
    // длина исходящего пакета  
    cEthernet::AnswerLength = 2 + BASE_HEADER_LENGTH;                      
    
    // Передача 
      cEthernet::sendAnswer();

  }
}//End of void cKeyboard::execKey1()
//------------------------------------------------------------------
void cKeyboard::execKey2()
{
  if(Key2.checkEvent())
  {
    //--- Отправка сообщения об изменении состояния клавиши ---
    // Дескриптор исходящего пакета
    if(Key2.getValue() == 0)
       cEthernet::releaseBaseProtocol(102);
    else
       cEthernet::releaseBaseProtocol(103);
    // Код клавиши   
    cEthernet::AnswerBuffer[1 + BASE_HEADER_LENGTH ] = 2;                   
    // длина исходящего пакета  
    cEthernet::AnswerLength = 2 + BASE_HEADER_LENGTH;                      
    
    // Передача 
      cEthernet::sendAnswer();

  }
}//End of void cKeyboard::execKey2()
//------------------------------------------------------------------
void cKeyboard::execKey3()
{
  if(Key3.checkEvent())
  {
    //--- Отправка сообщения об изменении состояния клавиши ---
    // Дескриптор исходящего пакета
    if(Key3.getValue() == 0)
       cEthernet::releaseBaseProtocol(102);
    else
       cEthernet::releaseBaseProtocol(103);
    // Код клавиши   
    cEthernet::AnswerBuffer[1 + BASE_HEADER_LENGTH ] = 3;                   
    // длина исходящего пакета  
    cEthernet::AnswerLength = 2 + BASE_HEADER_LENGTH;                      
    
    // Передача 
      cEthernet::sendAnswer();

  }
}//End of void cKeyboard::execKey3()
//------------------------------------------------------------------
void cKeyboard::execKey4()
{
  if(Key4.checkEvent())
  {
    //--- Отправка сообщения об изменении состояния клавиши ---
    // Дескриптор исходящего пакета
    if(Key4.getValue() == 0)
       cEthernet::releaseBaseProtocol(102);
    else
       cEthernet::releaseBaseProtocol(103);
    // Код клавиши   
    cEthernet::AnswerBuffer[1 + BASE_HEADER_LENGTH ] = 4;                   
    // длина исходящего пакета  
    cEthernet::AnswerLength = 2 + BASE_HEADER_LENGTH;                      
    
    // Передача 
      cEthernet::sendAnswer();

  }
}//End of void cKeyboard::execKey4()
//------------------------------------------------------------------
void cKeyboard::execKey5()
{
  if(Key5.checkEvent())
  {
    //--- Отправка сообщения об изменении состояния клавиши ---
    // Дескриптор исходящего пакета
    if(Key5.getValue() == 0)
       cEthernet::releaseBaseProtocol(102);
    else
       cEthernet::releaseBaseProtocol(103);
    // Код клавиши   
    cEthernet::AnswerBuffer[1 + BASE_HEADER_LENGTH ] = 5;                   
    // длина исходящего пакета  
    cEthernet::AnswerLength = 2 + BASE_HEADER_LENGTH;                      
    
    // Передача 
      cEthernet::sendAnswer();
  }
}//End of void cKeyboard::execKey5()

//------------------------------------------------------------------
void cKeyboard::execKey6()
{
  if(Key6.checkEvent())
  {
    //--- Отправка сообщения об изменении состояния клавиши ---
    // Дескриптор исходящего пакета
    if(Key6.getValue() == 0)
       cEthernet::releaseBaseProtocol(102);
    else
       cEthernet::releaseBaseProtocol(103);
    // Код клавиши   
    cEthernet::AnswerBuffer[1 + BASE_HEADER_LENGTH ] = 14;                   
    // длина исходящего пакета  
    cEthernet::AnswerLength = 2 + BASE_HEADER_LENGTH;                      
    
    // Передача 
      cEthernet::sendAnswer();

  }
}//End of void cKeyboard::execKey6()

//------------------------------------------------------------------
void cKeyboard::execKey7()
{
  if(Key7.checkEvent())
  {
    //--- Отправка сообщения об изменении состояния клавиши ---
    // Дескриптор исходящего пакета
    if(Key7.getValue() == 0)
       cEthernet::releaseBaseProtocol(102);
    else
       cEthernet::releaseBaseProtocol(103);
    // Код клавиши   
    cEthernet::AnswerBuffer[1 + BASE_HEADER_LENGTH ] = 13;                   
    // длина исходящего пакета  
    cEthernet::AnswerLength = 2 + BASE_HEADER_LENGTH;                      
    
    // Передача 
      cEthernet::sendAnswer();

  }
}//End of void cKeyboard::execKey7()

//------------------------------------------------------------------
void cKeyboard::execKey8()
{
  if(Key8.checkEvent())
  {
    //--- Отправка сообщения об изменении состояния клавиши ---
    // Дескриптор исходящего пакета
    if(Key8.getValue() == 0)
       cEthernet::releaseBaseProtocol(102);
    else
       cEthernet::releaseBaseProtocol(103);
    // Код клавиши   
    cEthernet::AnswerBuffer[1 + BASE_HEADER_LENGTH ] = 12;// Код кнопки БПС                   
    // длина исходящего пакета  
    cEthernet::AnswerLength = 2 + BASE_HEADER_LENGTH;                      
    
    // Передача 
      cEthernet::sendAnswer();

  }
}//End of void cKeyboard::execKey8()

//------------------------------------------------------------------
void cKeyboard::execKey9()
{
  if(Key9.checkEvent())
  {
    //--- Отправка сообщения об изменении состояния клавиши ---
    // Дескриптор исходящего пакета
    if(Key9.getValue() == 0)
       cEthernet::releaseBaseProtocol(102);
    else
       cEthernet::releaseBaseProtocol(103);
    // Код клавиши   
    cEthernet::AnswerBuffer[1 + BASE_HEADER_LENGTH ] = 11;// Код кнопки УАС                   
    // длина исходящего пакета  
    cEthernet::AnswerLength = 2 + BASE_HEADER_LENGTH;                      
    
    // Передача 
      cEthernet::sendAnswer();

  }
}//End of void cKeyboard::execKey9()

//------------------------------------------------------------------
void cKeyboard::execKey10()
{
  if(Key10.checkEvent())
  {
    //--- Отправка сообщения об изменении состояния клавиши ---
    // Дескриптор исходящего пакета
    if(Key10.getValue() == 0)
       cEthernet::releaseBaseProtocol(102);
    else
       cEthernet::releaseBaseProtocol(103);
    // Код клавиши   
    cEthernet::AnswerBuffer[1 + BASE_HEADER_LENGTH ] = 10;// Код кнопки МФС                   
    // длина исходящего пакета  
    cEthernet::AnswerLength = 2 + BASE_HEADER_LENGTH;                      
    
    // Передача 
      cEthernet::sendAnswer();

  }
}//End of void cKeyboard::execKey10()

//------------------------------------------------------------------
void cKeyboard::exec()
{
  // - 1 -
  
  cKeyboard::Key1.operate();
  cKeyboard::execKey1();

  // - 2 -
  
  cKeyboard::Key2.operate();
  cKeyboard::execKey2();

  // - 3 -
  
  cKeyboard::Key3.operate();
  cKeyboard::execKey3();

  // - 4 -
  
  cKeyboard::Key4.operate();
  cKeyboard::execKey4();

  // - 5 -
  
  cKeyboard::Key5.operate();
  cKeyboard::execKey5();

  // - 6 -
  
  cKeyboard::Key6.operate();
  cKeyboard::execKey6();
  
  // - 7 -
  
  cKeyboard::Key7.operate();
  cKeyboard::execKey7();

  // - 8 -
  
  cKeyboard::Key8.operate();
  cKeyboard::execKey8();

  // - 9 -
  
  cKeyboard::Key9.operate();
  cKeyboard::execKey9();

  // - 10 -
  
  cKeyboard::Key10.operate();
  cKeyboard::execKey10();
}//End of void cKeyboard::exec()


//--------------------------------------------------------------------------------
//----------------------------------ОБЪЯВЛЕНИЕ СТАТИЧЕСКИХ ПЕРЕМЕННЫХ-------------
//--------------------------------------------------------------------------------
cKey cKeyboard::Key1; 
cKey cKeyboard::Key2; 
cKey cKeyboard::Key3; 
cKey cKeyboard::Key4; 
cKey cKeyboard::Key5; 
cKey cKeyboard::Key6; 
cKey cKeyboard::Key7; 
cKey cKeyboard::Key8; 
cKey cKeyboard::Key9; 
cKey cKeyboard::Key10; 


//--------------------------------------------------------------------------------
#endif
