#include <SPI.h>
#include <OLED_I2C.h>
OLED myOLED(SDA, SCL);
extern uint8_t SmallFont[];
#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 5;
char button;
char keys[ROWS][COLS] = {
  { '0', '1', '2', '3', 'h' },
  { '4', '5', '6', '7', 'x' },
  { '8', '9', 'A', 'B', 's' },
  { 'C', 'D', 'E', 'F', 'd' }
};
byte rowPins[ROWS] = { A0, A1, A2, A3 };  // подключение к строкам клавиатуры
byte colPins[COLS] = { 6, 5, 4, 3, 2 };   // подключение к столбцам клавиатуры
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
uint16_t cmd;
byte pack[2];
void setup() {
  //Serial.begin(9600);
  pinMode(SS, OUTPUT);  // настройка линии SS как выход
  SPI.begin();
  digitalWrite(SS, HIGH);
  myOLED.begin();
  myOLED.setFont(SmallFont);
  myOLED.clrScr();
  myOLED.update();
}

void loop() {
  myOLED.clrScr();
  button = customKeypad.getKey();  // определение нажатой кнопки
  if (button != NO_KEY)
    detectbuttons();
  //Serial.println(button);
  myOLED.print(String(cmd, HEX), CENTER, 25);  //выводим на экран вводимую команду
  myOLED.update();
}

void detectbuttons() {
  switch (button) {
    case '0':
      //    Serial.println("Button 0");
      if (cmd == 0) {
        cmd = 0x0000;
      } else {
        cmd = cmd << 4;
        cmd |= 0x0000;
      }
      break;

    case '1':
      //    Serial.println("Button 1");
      if (cmd == 0) {
        cmd = 0x0001;
      } else {
        cmd = cmd << 4;
        cmd |= 0x0001;
      }
      break;

    case '2':
      //    Serial.println("Button 2");
      if (cmd == 0) {
        cmd = 0x0002;
      } else {
        cmd = cmd << 4;
        cmd |= 0x0002;
      }
      break;

    case '3':
      //    Serial.println("Button 3");
      if (cmd == 0) {
        cmd = 0x0003;
      } else {
        cmd = cmd << 4;
        cmd |= 0x0003;
      }
      break;

    case '4':
      //    Serial.println("Button 4");
      if (cmd == 0) {
        cmd = 0x0004;
      } else {
        cmd = cmd << 4;
        cmd |= 0x0004;
      }
      break;

    case '5':
      //    Serial.println("Button 5");
      if (cmd == 0) {
        cmd = 0x0005;
      } else {
        cmd = cmd << 4;
        cmd |= 0x0005;
      }
      break;

    case '6':
      //    Serial.println("Button 6");
      if (cmd == 0) {
        cmd = 0x0006;
      } else {
        cmd = cmd << 4;
        cmd |= 0x0006;
      }
      break;

    case '7':
      //    Serial.println("Button 7");
      if (cmd == 0) {
        cmd = 0x0007;
      } else {
        cmd = cmd << 4;
        cmd |= 0x0007;
      }
      break;

    case '8':
      //    Serial.println("Button 8");
      if (cmd == 0) {
        cmd = 0x0008;
      } else {
        cmd = cmd << 4;
        cmd |= 0x0008;
      }
      break;

    case '9':
      //    Serial.println("Button 9");
      if (cmd == 0) {
        cmd = 0x0009;
      } else {
        cmd = cmd << 4;
        cmd |= 0x0009;
      }
      break;

    case 'A':
      //    Serial.println("Button A");
      if (cmd == 0) {
        cmd = 0x000A;
      } else {
        cmd = cmd << 4;
        cmd |= 0x000A;
      }
      break;

    case 'B':
      //    Serial.println("Button B");
      if (cmd == 0) {
        cmd = 0x000B;
      } else {
        cmd = cmd << 4;
        cmd |= 0x000B;
      }
      break;

    case 'C':
      //    Serial.println("Button C");
      if (cmd == 0) {
        cmd = 0x000C;
      } else {
        cmd = cmd << 4;
        cmd |= 0x000C;
      }
      break;

    case 'D':
      //    Serial.println("Button D");
      if (cmd == 0) {
        cmd = 0x000D;
      } else {
        cmd = cmd << 4;
        cmd |= 0x000D;
      }
      break;

    case 'E':
      //    Serial.println("Button E");
      if (cmd == 0) {
        cmd = 0x000E;
      } else {
        cmd = cmd << 4;
        cmd |= 0x000E;
      }
      break;

    case 'F':
      //    Serial.println("Button F");
      if (cmd == 0) {
        cmd = 0x000F;
      } else {
        cmd = cmd << 4;
        cmd |= 0x000F;
      }
      break;

    case 's':
      //    Serial.println("Button send");
      pack[0] = cmd;
      pack[1] = cmd >> 8;
      digitalWrite(SS, LOW);
      for (int i = 0; i < 2; i++)
        SPI.transfer(pack[i]);
      digitalWrite(SS, HIGH);
      delay(1000);
      break;

    case 'd':
      //    Serial.println("Button del");
      cmd = cmd >> 4;
      break;

    case 'h':  //help
      while (1) {
        myOLED.clrScr();
        myOLED.print("Help", CENTER, 0);
        myOLED.print("0 1 2 3 h", CENTER, 16);
        myOLED.print("4 5 6 7 x", CENTER, 26);
        myOLED.print("8 9 A B s", CENTER, 36);
        myOLED.print("C D E F d", CENTER, 46);
        myOLED.update();
        button = customKeypad.getKey();
        detectbuttons();
        if (button) {
          cmd = 0x00;
          break;
        }
      }
      break;
  }
}
