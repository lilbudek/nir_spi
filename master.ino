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
  pinMode(SS, OUTPUT); // настройка линии SS как выход
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
  if (button == '0') {
    //    Serial.println("Button 0");
    if (cmd == 0)
      cmd = 0x0000;
    else
      cmd = cmd << 4;  //Pressed twice
      cmd |= 0x0000;
  }

  if (button == '1') {
    //    Serial.println("Button 1");
    if (cmd == 0)
      cmd = 0x0001;
    else
      cmd = cmd << 4;  //Pressed twice
      cmd |= 0x0001;
  }

  if (button == '2') {
    //    Serial.println("Button 2");
    if (cmd == 0)
      cmd = 0x0002;
    else
      cmd = cmd << 4;  //Pressed twice
      cmd |= 0x0002;
  }

  if (button == '3') {
    //    Serial.println("Button 3");
    if (cmd == 0)
      cmd = 0x0003;
    else
      cmd = cmd << 4;  //Pressed twice
      cmd |= 0x0003;
  }

  if (button == '4') {
    //    Serial.println("Button 4");
    if (cmd == 0)
      cmd = 0x0004;
    else
      cmd = cmd << 4;  //Pressed twice
      cmd |= 0x0004;
  }

  if (button == '5') {
    //    Serial.println("Button 5");
    if (cmd == 0)
      cmd = 0x0005;
    else
      cmd = cmd << 4;  //Pressed twice
      cmd |= 0x0005;
  }

  if (button == '6') {
    //    Serial.println("Button 6");
    if (cmd == 0)
      cmd = 0x0006;
    else
      cmd = cmd << 4;  //Pressed twice
      cmd |= 0x0006;
  }

  if (button == '7') {
    //    Serial.println("Button 7");
    if (cmd == 0)
      cmd = 0x0007;
    else
      cmd = cmd << 4;  //Pressed twice
      cmd |= 0x0007;
  }

  if (button == '8') {
    //    Serial.println("Button 8");
    if (cmd == 0)
      cmd = 0x0008;
    else
      cmd = cmd << 4;  //Pressed twice
      cmd |= 0x0008;
  }

  if (button == '9') {
    //    Serial.println("Button 9");
    if (cmd == 0)
      cmd = 0x0009;
    else
      cmd = cmd << 4;  //Pressed twice
      cmd |= 0x0009;
  }

  if (button == 'A') {
    //    Serial.println("Button A");
    if (cmd == 0)
      cmd = 0x000A;
    else
      cmd = cmd << 4;  //Pressed twice
      cmd |= 0x000A;
  }

  if (button == 'B') {
    //    Serial.println("Button B");
    if (cmd == 0)
      cmd = 0x000B;
    else
      cmd = cmd << 4;  //Pressed twice
      cmd |= 0x000B;
  }

  if (button == 'C') {
    //    Serial.println("Button C");
    if (cmd == 0)
      cmd = 0x000C;
    else
      cmd = cmd << 4;  //Pressed twice
      cmd |= 0x000C;
  }

  if (button == 'D') {
    //    Serial.println("Button D");
    if (cmd == 0)
      cmd = 0x000D;
    else
      cmd = (cmd << 4);  //Pressed twice
      cmd |= 0x000D;
  }

  if (button == 'E') {
    //    Serial.println("Button E");
    if (cmd == 0)
      cmd = 0x000E;
    else
      cmd = cmd << 4;  //Pressed twice
      cmd |= 0x000E;
  }

  if (button == 'F') {
    //    Serial.println("Button F");
    if (cmd == 0)
      cmd = 0x000F;
    else
      cmd = cmd << 4;  //Pressed twice
      cmd |= 0x000F;
  }

  if (button == 's') {
    //    Serial.println("Button send");
      pack[0] = cmd;
      pack[1] = cmd >> 8;
      digitalWrite(SS, LOW);
      for (int i = 0; i < 2; i++) {
        SPI.transfer(pack[i]);
      }
      digitalWrite(SS, HIGH);
      delay(1000);
   }

  if (button == 'd') {
    //    Serial.println("Button del");
    cmd = cmd >> 4;
  }

  if (button == 'h') {  //хелпа
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
  }
}
