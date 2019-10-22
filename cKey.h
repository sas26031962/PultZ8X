/*
 Класс работы с кнопками ПОУ
 */
#ifndef C_KEY
#define C_KEY
 //========================================================================
 //---------------------------- ПОДКЛЮЧАЕМЫЕ ФАЙЛЫ ------------------------
 //========================================================================
 //#include <SPI.h>         
 //#include <Ethernet.h>
 //#include <EthernetUdp.h>     
 
 //========================================================================
 //-------------------------------- КОНСТАНТЫ -----------------------------
 //========================================================================
 #define DELAY_KEYBOARD 50


 
 //========================================================================
 //--------------------------- ОБЪЯВЛЕНИЕ КЛАССОВ -------------------------
 //========================================================================
 
class cKey{
 
 //------------------------------------------------------------------------
 // Атрибуты
 //------------------------------------------------------------------------

 
 char Name;               // Имя объекта
 int Line;			          // Линия ввода данных
 
 bool Current;		        // Текущее состояние кнопки
 bool Previous;		        // Предыдущее состояние кнопки
 
 long PreviousTime;       // Предыдущее значение миллисекундного таймера
 bool IsDebounce;         // Флаг процесса подавления дребезга
 
 bool IsEvent;            // Событие изменения состояния кнопки
 
 public:

 static int Dwell;         //Время ожидания для подавления дребезга
 static long CurrentTime;  //Текущее значение миллисекундного таймера
 
 char AnswerBuffer[UDP_BUFFER_SIZE]; // буфер для передачи в ответ
 int AnswerLength = 0;                      // длина исходящего пакета
 
 //------------------------------------------------------------------------
 // Методы
 //------------------------------------------------------------------------

 protected: 
 
 void eventGeneration();  // Генерация события
  
 public:
 
 static void getCurrentTime(); // Чтение текущего времени
 
 void operate();  // Реализация функциональности джойстика

 char getValue(); // Чтение текущего значения в символьном виде
 
 void install(char nameX, int line);

 bool checkEvent(); // Проверка события клавиатуры
 
 //------------------------------------------------------------------------
 // Конструкторы
 //------------------------------------------------------------------------
 cKey();
 
};//End of class cKey

 //========================================================================
 //--------------------------- РЕАЛИЗАЦИЯ МЕТОДОВ -------------------------
 //========================================================================

//
// Конструктор
//
cKey::cKey(
    )
{
  //...
} 

//
// Начальная установка
//
void cKey::install(
    char nameX,
    int line
  )
{
  this->Name = nameX;
  this->Line = line;

  pinMode(this->Line, INPUT_PULLUP);  

  this->Current = digitalRead(this->Line);
  this->Previous = this->Current;

  this->PreviousTime = millis();
  this->IsDebounce = false;
}

//
// Реализация функциональности
//
void cKey::operate()
{
  this->Current = digitalRead(this->Line);
  // Фиксация момента изменения состояния кнопки
  if((this->Current != this->Previous) && !this->IsDebounce)
  {
    this->Previous = this->Current;
    this->IsDebounce = true;
    this->PreviousTime = cKey::CurrentTime;
  }
  
  // Фиксация момента окончания процесса подавления дребезга
  if((cKey::CurrentTime - this->PreviousTime > cKey::Dwell) && this->IsDebounce && (this->Current == this->Previous))
  {
    this->IsDebounce = false;
    this->eventGeneration();
  }
}

//
// Генерация события
//
 void cKey::eventGeneration()
 {
    this->IsEvent = true;
    // отправка в последовательный порт
    Serial.print("Key ");
    Serial.print(this->Name);
    if(this->Current) Serial.println(" released"); else  Serial.println(" pressed"); 
    /*
    //--- Отправка сообщения об изменении состояния клавиши ---
    // Дескриптор исходящего пакета
    if(this->Previous)
      AnswerBuffer[0] = 102;                
    else
      AnswerBuffer[0] = 103;
    // Код клавиши 
    AnswerBuffer[1] = 1;                   
    // Длина исходящего пакета
    AnswerLength = 2;                      
    // Передача ответа: в качестве адреса и номера порта берутся данные 
    Udp.beginPacket(remote_ip, destinationPort);// Инициализация UDP на передачу
    Udp.write( AnswerBuffer, AnswerLength);// Передача ответа
    Udp.endPacket();// Закрытие UDP канала на передачу
    */
 }

//
// Чтение события клавиатуры
//
 bool cKey::checkEvent()
 {
    bool x = this->IsEvent;
    this->IsEvent = false;
    return x;
 }

//
// Чтение текущего значения
//

 char cKey::getValue()
 {
    if(this->Previous) return 0; else return 1;
 }

 //
 // Чтение текущего времени
 //
 void cKey::getCurrentTime()
 {
    cKey::CurrentTime = millis();
 }
//--------------------------------------------------------------------------------
//----------------------------------ОБЪЯВЛЕНИЕ СТАТИЧЕСКИХ ПЕРЕМЕННЫХ-------------
//--------------------------------------------------------------------------------
 long cKey::CurrentTime;
 int cKey::Dwell = DELAY_KEYBOARD;


//--------------------------------------------------------------------------------
#endif
