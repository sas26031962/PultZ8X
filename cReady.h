/*
 Класс подготовки пульта к работе
 */
#ifndef C_READY
#define C_READY
 //========================================================================
 //---------------------------- ПОДКЛЮЧАЕМЫЕ ФАЙЛЫ ------------------------
 //========================================================================
 
 //========================================================================
 //-------------------------------- КОНСТАНТЫ -----------------------------
 //========================================================================
  #define READY_DELAY 500      // Задержка перед подачей сообщения о готовности пульта


 
 //========================================================================
 //--------------------------- ОБЪЯВЛЕНИЕ КЛАССОВ -------------------------
 //========================================================================
 
class cReady{
 
 //------------------------------------------------------------------------
 // Атрибуты
 //------------------------------------------------------------------------

 public:
 
 static long MillisReady;          //Значение локального миллисекундного таймера
 static bool IsReady;// = false;   //Флаг готовности
 static int  CounterReady;// = 0;  //Фаза готовности

 //------------------------------------------------------------------------
 // Методы
 //------------------------------------------------------------------------
 static void exec();
  
 //------------------------------------------------------------------------
 // Конструкторы
 //------------------------------------------------------------------------
 cReady();
 
};//End of class cReady

 //========================================================================
 //--------------------------- РЕАЛИЗАЦИЯ МЕТОДОВ -------------------------
 //========================================================================

//
// Конструктор
//
cReady::cReady(
    )
{
  //...
} 

void cReady::exec()
{
  if(!cReady::IsReady && (cKey::CurrentTime - cReady::MillisReady) > READY_DELAY)
  {
      // Сброс счётчика задержки
      cReady::MillisReady = cKey::CurrentTime;
      cReady::CounterReady ++;
      
      // Отправка сообщения ПУЛЬТ ГОТОВ К РАБОТЕ
      cEthernet::releaseBaseProtocol(100);      // реализация базового протокола
      cEthernet::AnswerLength = 1 + BASE_HEADER_LENGTH;    // длина исходящего пакета
       
    
      // Передача ответа 
      cEthernet::sendAnswer();

      // Установка флага готовности
      if(cReady::CounterReady  == 2) cReady::IsReady = true;
  }
}//End of void cReady::exec()
//--------------------------------------------------------------------------------
//----------------------------------ОБЪЯВЛЕНИЕ СТАТИЧЕСКИХ ПЕРЕМЕННЫХ-------------
//--------------------------------------------------------------------------------

 long cReady::MillisReady = millis();
 bool cReady::IsReady = false;
 int  cReady::CounterReady = 0;

//--------------------------------------------------------------------------------
#endif