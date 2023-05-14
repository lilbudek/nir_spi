#include <SPI.h>
#define MISO 12
#define MOSI 11
#define SCK 13
#define SS 10
volatile bool received;
uint16_t res = 0x0000;
volatile uint16_t pack[2];
#include <OLED_I2C.h>
OLED myOLED(SDA, SCL);
extern uint8_t SmallFont[];

void setup() {
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);
  SPCR |= _BV(SPE);       //переводим SPI в Slave Mode (режим ведомого)
  received = false;
  SPI.attachInterrupt();  //включаем прерывание 
  myOLED.begin();
  myOLED.setFont(SmallFont);
  myOLED.clrScr();
  myOLED.update();
}
ISR(SPI_STC_vect)  //функция обработки прерывания
{
  for (int i = 0; i < 2; i++) {
    while (!(SPSR & (1 << SPIF)));
    pack[i] = SPDR;
  }
  pack[0] = pack[0] << 8;
  received = true; 
}
void loop() {

  myOLED.clrScr();
  if (received) {
    res = pack[1] | pack[0];
    //myOLED.print(String(pack[0], HEX), 50, 15);
    //myOLED.print(String(pack[1], HEX), 50, 30);
    myOLED.print(String(res, HEX), 50, 25);
    myOLED.update();
  }
  delay(1000);
}
