/*
 Программа стенда-имитатора пульта загружающего
 Для Arduino Mega в Ethernet shield задействованы выводы: 10, 4, 50, 52, 53, 51
 
 */

 //========================================================================
 //------------------------- АППАРАТНАЯ КОНФИГУРАЦИЯ ----------------------
 //========================================================================
  
  //========================================================================
 //--------------------------- ПОДКЛЮЧАЕМЫЕ МОДУЛИ ------------------------
 //========================================================================
 #include <Ethernet.h>
 #include <EthernetUdp.h>     

 #include "config.h"
 #include "cKey.h"
 #include "cLed.h"
 #include "cBuzer.h"
 #include "cEthernet.h"
 #include "cReady.h"
 #include "cKeyboard.h"
 #include "cDisplay.h"
 #include "cPult.h"
     
 //========================================================================
 //-------------------------------- КОНСТАНТЫ -----------------------------
 //========================================================================
  
 
 //========================================================================
 //-------------------------- ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ -----------------------
 //========================================================================

 // Пульт
 cPult Pult;
 
// ===================== ПРОГРАММА НАЧАЛЬНОЙ УСТАНОВКИ ==============
void setup() {
  
  Pult.install();

  // Кнопки
  cKeyboard::install();

  // Светодиоды
  cDisplay::install();
  
}//End of setup

// ============================= ГЛАВНАЯ ПРОГРАММА ==================
void loop() {
  // Опорная временная точка
  cKey::getCurrentTime();
  
  //----- Передача сообщения о готовности пульта после включения ----
  cReady::exec();
  //-----------------------------------------------------------------
  //-------------------------- Процесс чтения кнопок ----------------
  Pult.Kbd.exec();
  //-----------------------------------------------------------------
  //-------------------------- Разбор принятого пакета --------------
  Pult.exec();
  //-----------------------------------------------------------------

}//End of loop

