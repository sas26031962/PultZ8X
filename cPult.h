/*
 Класс описания поведения пульта
 */
#ifndef C_PULT
#define C_PULT
 //========================================================================
 //---------------------------- ПОДКЛЮЧАЕМЫЕ ФАЙЛЫ ------------------------
 //========================================================================

 //========================================================================
 //-------------------------------- КОНСТАНТЫ -----------------------------
 //========================================================================
 
 #define TITLE "MisslileLoader Pult v1.0.0"
 #define SERIAL_SPEED 115200         // Скорость обмена последовательного порта

 //========================================================================
 //--------------------------- ОБЪЯВЛЕНИЕ КЛАССОВ -------------------------
 //========================================================================
 
class cPult{
 
 //------------------------------------------------------------------------
 // Атрибуты
 //------------------------------------------------------------------------
 public:
 //
 // Параметры пульта
 //
 static char ParameterDebounce;// = 200;              // Параметр для подавления дребезга
 static char ErrorCode;// = 0;                        // Значение параметра ошибки
 static char Version[3];// = {1, 0, 0};               // Версия

 // Звуковой сигнал 
 cBuzer Buzer;
 
 // Светодиоды
 cDisplay Dis;
 
 // Кнопки
 cKeyboard Kbd;
 
 
 //------------------------------------------------------------------------
 // Методы
 //------------------------------------------------------------------------
 protected:

 public:
 void install();

 void exec(); 

 void view();

 //------------------------------------------------------------------------
 // Конструкторы
 //------------------------------------------------------------------------
 cPult();
 
};//End of class cPult
 //========================================================================
 //--------------------------- РЕАЛИЗАЦИЯ МЕТОДОВ -------------------------
 //========================================================================

//
// Конструктор
//
cPult::cPult(
    )
{
  //...
} 
//------------------------------------------------------------------
void cPult::install()
{

  //
  // Запуск последовательного порта для мониторинга
  //
  Serial.begin(SERIAL_SPEED);
  Serial.println(TITLE);

  //
  // Инициализация сети Ethernet
  //
  cEthernet::installEthernet();

  // Инициализация звукового сигнала
  Buzer.install('L', PIN_PIEZO);
  Buzer.beep();

}//End of void cPult::install()
//------------------------------------------------------------------
void cPult::exec()
{
  // 
  // Разбор принятого пакета
  //
  cEthernet::packetSize = cEthernet::Udp.parsePacket();
  
  if (cEthernet::packetSize > 0) {
    
    cEthernet::Udp.read(cEthernet::packetBuffer,32);

    view();
 
    //
    //Декодирование принятого сообщения
    //
    //---Включить индикатор с заданным номером
    if(cEthernet::packetBuffer[0] == 1)
    {
      // Действие
      cDisplay::parseKeyCodeField( cEthernet::packetBuffer[1 + BASE_HEADER_LENGTH], HIGH);
      
      cEthernet::releaseBaseProtocol(105);                        // Реализация базового протокола
      cEthernet::AnswerBuffer[1 + BASE_HEADER_LENGTH] = 
      cEthernet::packetBuffer[1+ BASE_HEADER_LENGTH];                      // Код элемента индикации
      cEthernet::AnswerLength = 2 + BASE_HEADER_LENGTH;           // длина исходящего пакета
    
      // Передача ответа: в качестве адреса и номера порта берутся данные 
      cEthernet::sendAnswer();

    }

    //---Выключить индикатор с заданным номером
    if(cEthernet::packetBuffer[0] == 2)
    {
      cDisplay::parseKeyCodeField( cEthernet::packetBuffer[1 + BASE_HEADER_LENGTH], LOW);
      
      cEthernet::releaseBaseProtocol(106);                        // Реализация базового протокола
      cEthernet::AnswerBuffer[1  + BASE_HEADER_LENGTH] = 
        cEthernet::packetBuffer[1+ BASE_HEADER_LENGTH];                      // Код элемента индикации
      cEthernet::AnswerLength = 2 + BASE_HEADER_LENGTH;           // длина исходящего пакета
    
      // Передача ответа: в качестве адреса и номера порта берутся данные 
      cEthernet::sendAnswer();

    }

    //---Установить значение параметра пульта
    if(cEthernet::packetBuffer[0] == 3)
    {
      cPult::ParameterDebounce = cEthernet::packetBuffer[1 + BASE_HEADER_LENGTH]; //Установка значения параметра пульта
                                                                                  //
      cEthernet::releaseBaseProtocol(103);                                        // реализация базового протокола
      cEthernet::AnswerBuffer[1 + BASE_HEADER_LENGTH] = cPult::ParameterDebounce; // Значение параметра
      cEthernet::AnswerLength = 2  + BASE_HEADER_LENGTH;                          // длина исходящего пакета
    
      // Передача ответа: в качестве адреса и номера порта берутся данные 
      cEthernet::sendAnswer();

    }
 
    //---Запросить значение параметра пульта
    if(cEthernet::packetBuffer[0] == 4)
    {
      cEthernet::releaseBaseProtocol(103);                        // реализация базового протокола
      cEthernet::AnswerBuffer[1 + BASE_HEADER_LENGTH] = cPult::ParameterDebounce;   // Значение параметра
      cEthernet::AnswerLength = 2 + BASE_HEADER_LENGTH;           // длина исходящего пакета
    
      // Передача ответа: в качестве адреса и номера порта берутся данные 
      cEthernet::sendAnswer();

    }
 

    //---Передать состояние пульта
    if(cEthernet::packetBuffer[0] == 5)
    {
      cEthernet::releaseBaseProtocol(100);                        // реализация базового протокола

      cEthernet::AnswerBuffer[1 + BASE_HEADER_LENGTH]  = !cKeyboard::Key1.getValue();    // Состояние тумблера "ВКЛ ПЗ"
      cEthernet::AnswerBuffer[2 + BASE_HEADER_LENGTH]  = cKeyboard::Key2.getValue();     // Состояние кнопки "МФС"
      cEthernet::AnswerBuffer[3 + BASE_HEADER_LENGTH]  = cKeyboard::Key3.getValue();     // Состояние кнопки "УАС"
      cEthernet::AnswerBuffer[4 + BASE_HEADER_LENGTH]  = cKeyboard::Key4.getValue();     // Состояние кнопки "БПС"
      cEthernet::AnswerBuffer[5 + BASE_HEADER_LENGTH]  = cKeyboard::Key5.getValue();     // Состояние кнопки "ОФС"
      cEthernet::AnswerBuffer[6 + BASE_HEADER_LENGTH]  = cKeyboard::Key6.getValue();     // Состояние кнопки "БР"
      cEthernet::AnswerBuffer[7 + BASE_HEADER_LENGTH]  = 0;                              // Резерв для состояния кнопки 1
      cEthernet::AnswerBuffer[8 + BASE_HEADER_LENGTH]  = 0;                              // Резерв для состояния кнопки 2
      cEthernet::AnswerBuffer[9 + BASE_HEADER_LENGTH]  = cKeyboard::Key7.getValue();     // Состояние кнопки "АВАРИЯ СТОП"
      cEthernet::AnswerBuffer[10 + BASE_HEADER_LENGTH] = cKeyboard::Key8.getValue();     // Состояние кнопки "ХОД / ЗАПИСЬ"
      cEthernet::AnswerBuffer[11 + BASE_HEADER_LENGTH] = cKeyboard::Key9.getValue();     // Состояние тумблера "РЕЖИМ"
      cEthernet::AnswerBuffer[12 + BASE_HEADER_LENGTH] = cKeyboard::Key10.getValue();    // Состояние кнопки "КОНТРОЛЬ ИНД"
      cEthernet::AnswerBuffer[13 + BASE_HEADER_LENGTH] = cDisplay::Led1.getState();      // Состояние элемента индикации "ВКЛ ПЗ"
      cEthernet::AnswerBuffer[14 + BASE_HEADER_LENGTH] = cDisplay::Led2.getState();      // Состояние элемента индикации "МФС"
      cEthernet::AnswerBuffer[15 + BASE_HEADER_LENGTH] = cDisplay::Led3.getState();      // Состояние элемента индикации "УАС"
      cEthernet::AnswerBuffer[16 + BASE_HEADER_LENGTH] = cDisplay::Led4.getState();      // Состояние элемента индикации "БПС"
      cEthernet::AnswerBuffer[17 + BASE_HEADER_LENGTH] = cDisplay::Led5.getState();      // Состояние элемента индикации "ОФС"
      cEthernet::AnswerBuffer[18 + BASE_HEADER_LENGTH] = cDisplay::Led6.getState();      // Состояние элемента индикации "БР"
      cEthernet::AnswerBuffer[19 + BASE_HEADER_LENGTH] = 5;                              // Резерв для элемента индикации 1
      cEthernet::AnswerBuffer[20 + BASE_HEADER_LENGTH] = 5;                              // Резерв для элемента индикации 2
      cEthernet::AnswerBuffer[21 + BASE_HEADER_LENGTH] = cDisplay::Led7.getState();      // Состояние элемента индикации "ХОД / ЗАПИСЬ"
      cEthernet::AnswerBuffer[22 + BASE_HEADER_LENGTH] = cDisplay::Led8.getState();      // Состояние элемента индикации "ОТКАЗ"
      cEthernet::AnswerBuffer[23 + BASE_HEADER_LENGTH] = cDisplay::Led9.getState();      // Состояние элемента индикации "ЗАГРУЗКА БП"
      cEthernet::AnswerBuffer[24 + BASE_HEADER_LENGTH] = cDisplay::Led10.getState();     // Состояние элемента индикации "РАЗГРУЗКА БП"
      cEthernet::AnswerBuffer[25 + BASE_HEADER_LENGTH] = cDisplay::Led11.getState();     // Состояние элемента индикации "РАБОТА ПЗ"
      cEthernet::AnswerBuffer[26 + BASE_HEADER_LENGTH] = cPult::ParameterDebounce;       // Значение параметра подавления дребезга
      cEthernet::AnswerBuffer[27 + BASE_HEADER_LENGTH] = cPult::ErrorCode;               // Значение кода ошибки
      cEthernet::AnswerBuffer[28 + BASE_HEADER_LENGTH] = 4;                              // Резерв для служебной информации 1
      cEthernet::AnswerBuffer[29 + BASE_HEADER_LENGTH] = 4;                              // Резерв для служебной информации 2
      cEthernet::AnswerBuffer[30 + BASE_HEADER_LENGTH] = 4;                              // Резерв для служебной информации 3
      cEthernet::AnswerBuffer[31 + BASE_HEADER_LENGTH] = 4;                              // Резерв для служебной информации 4
      cEthernet::AnswerBuffer[32 + BASE_HEADER_LENGTH] = cPult::Version[0];              // Версия ПО пульта цифра 1
      cEthernet::AnswerBuffer[33 + BASE_HEADER_LENGTH] = cPult::Version[1];              // Версия ПО пульта цифра 2
      cEthernet::AnswerBuffer[34 + BASE_HEADER_LENGTH] = cPult::Version[2];              // Версия ПО пульта цифра 3
      cEthernet::AnswerLength = 35 + BASE_HEADER_LENGTH;                                 // длина исходящего пакета
    
      // Передача ответа: в качестве адреса и номера порта берутся данные 
      cEthernet::sendAnswer();

    }
 
     //--- Команда диагностики пульта
    if(cEthernet::packetBuffer[0] == 6)
    {
      char x = cEthernet::packetBuffer[1 + BASE_HEADER_LENGTH];              // Чтение номера команды диагностики
      char Result[3] = {0, 0, 0};                                 // Результат выполнения команды
      //
      //... здесь должен помещаться анализ команды диагностики
      //
      cEthernet::releaseBaseProtocol(104);                        // реализация базового протокола
      cEthernet::AnswerBuffer[1 + BASE_HEADER_LENGTH] = x;        // Номер выполненной команды диагностики
      cEthernet::AnswerBuffer[2 + BASE_HEADER_LENGTH] = Result[0];// Параметр 1 результата
      cEthernet::AnswerBuffer[3 + BASE_HEADER_LENGTH] = Result[1];// Параметр 2 результата
      cEthernet::AnswerBuffer[4 + BASE_HEADER_LENGTH] = Result[2];// Параметр 3 результата
      
      cEthernet::AnswerLength = 5 + BASE_HEADER_LENGTH;           // длина исходящего пакета
    
      // Передача ответа
      cEthernet::sendAnswer();

      }
 
     //--- Команда ОСТАНОВ ПУЛЬТА
    if(cEthernet::packetBuffer[0] == 99)
    {
      cEthernet::releaseBaseProtocol(108);                        // реализация базового протокола
      cEthernet::AnswerLength = 1 + BASE_HEADER_LENGTH;           // длина исходящего пакета
    
      // Передача ответа: в качестве адреса и номера порта берутся данные 
      cEthernet::sendAnswer();

      }
 /*
     //--- Команда СТАРТ ПУЛЬТА
    if(cEthernet::packetBuffer[0] == 0)
    {
      cEthernet::releaseBaseProtocol(100);                      // реализация базового протокола
      cEthernet::AnswerLength = 1 + BASE_HEADER_LENGTH;         // длина исходящего пакета
    
   
      // Передача ответа: в качестве адреса и номера порта берутся данные 
      cEthernet::sendAnswer();

    }
 */
   // Очистка буфера входящих пакетов
    for(int i = 0; i < 8; i++) cEthernet::packetBuffer[i] = ' ';
  }
}//End of void cPult::exec()
//--------------------------------------------------------------------------------
void cPult::view()
{
    // Визуализация принятых данных
    Serial.print("Contents: ");
    // Дескриптор 
    String s0 = String((cEthernet::packetBuffer[0] + cEthernet::packetBuffer[1] * 256), DEC);
    // Номер пакета
    String s1 = String((cEthernet::packetBuffer[2] + cEthernet::packetBuffer[3] * 256), DEC);
    // Параметр 1
    String s2 = String(cEthernet::packetBuffer[12], DEC);
    Serial.print(s0);
    Serial.print(" ");
    Serial.print(s1);
    Serial.print(" ");
    Serial.println(s2);

}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
//----------------------------------ОБЪЯВЛЕНИЕ СТАТИЧЕСКИХ ПЕРЕМЕННЫХ-------------
//--------------------------------------------------------------------------------
//
// Параметры пульта
//
char cPult::ParameterDebounce = 200;              // Параметр для подавления дребезга
char cPult::ErrorCode = 0;                        // Значение параметра ошибки
char cPult::Version[3] = {1, 0, 0};               // Версия


//--------------------------------------------------------------------------------
#endif
