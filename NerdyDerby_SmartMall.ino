

#define startButton 12
#define lane1Sensor 6
#define lane2Sensor 7
#define lane3Sensor 8

#include <SerialDisplay.h>
#include <Servo.h>
#include <LedControl.h>

Servo servo;

//Conexoes do modulo Max7219
//DataIn = Pino 4
//CLK = Pino 2
//CS = Pino 3
LedControl lc = LedControl(4, 2, 3, 3);

// (data, clock, number of modules
SerialDisplay displays(9, 11, 3);

bool started = false;
unsigned long timer;
//int brilho = 15;
int positions[3] = {0, 0, 0};
int carsFinished = 0;
bool car1Done, car2Done, car3Done;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello NerdyDerby!!!");

  pinMode(startButton, INPUT);
  pinMode(lane1Sensor, INPUT);
  pinMode(lane2Sensor, INPUT);
  pinMode(lane3Sensor, INPUT);

  servo.attach(5);
  servo.write(10);

  lc.shutdown(0, false);
  lc.shutdown(1, false);
  lc.shutdown(2, false);

  lc.setIntensity(0, 1);
  lc.setIntensity(1, 1);
  lc.setIntensity(2, 1);

  lc.clearDisplay(0);
  lc.clearDisplay(1);
  lc.clearDisplay(2);

  writeOnMatrix(0, 0);
  writeOnMatrix(0, 1);
  writeOnMatrix(0, 2);


  //mdisplays.On(1);

  displays.Print(0, 1);
  displays.Print(0, 2);
  displays.Print(0, 3);

  //displays.On(1);
  //displays.On(2);
  //displays.On(3);
  //displays.Info(&Serial);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(startButton) && timer < millis()) {
    started = true;
    Serial.println("START");
    Start();
    timer = millis() + 10000;
    servo.write(180);

  }
  if (started == true && timer < millis()) {

    //ShowPosition();
    Serial.println("RESET");
    started = false;
    servo.write(10);
    Flag();
    writeOnMatrix(0, 0);
    writeOnMatrix(0, 1);
    writeOnMatrix(0, 2);
    carsFinished = 0;

    positions[0] = 0;
    positions[1] = 0;
    positions[2] = 0;

    displays.Print(0, 1);
    displays.Print(0, 2);
    displays.Print(0, 3);

    car1Done = false;
    car2Done = false;
    car3Done = false;
  }
  if (started) {
    if (digitalRead(lane1Sensor) && !car1Done) {
      positions[carsFinished] = 1;
      carsFinished++;
      car1Done = true;
      displays.Print(carsFinished, 1);
      Serial.println("1");
    }
    if (digitalRead(lane2Sensor) && !car2Done) {
      positions[carsFinished] = 2;
      carsFinished++;
      car2Done = true;
      displays.Print(carsFinished, 2);
      Serial.println("2");

    }
    if (digitalRead(lane3Sensor) && !car3Done) {
      positions[carsFinished] = 3;
      carsFinished++;
      car3Done = true;
      displays.Print(carsFinished, 3);
      Serial.println("3");
    }
    if (positions[2] != 0) {
      timer = millis();
    }
  }
}

void Start() {
  writeOnMatrix(3, 0);
  writeOnMatrix(3, 1);
  writeOnMatrix(3, 2);
  displays.Print(3, 1);
  displays.Print(3, 2);
  displays.Print(3, 3);
  delay(1000);
  writeOnMatrix(2, 0);
  writeOnMatrix(2, 1);
  writeOnMatrix(2, 2);
  displays.Print(2, 1);
  displays.Print(2, 2);
  displays.Print(2, 3);
  delay(1000);
  writeOnMatrix(1, 0);
  writeOnMatrix(1, 1);
  writeOnMatrix(1, 2);
  displays.Print(1, 1);
  displays.Print(1, 2);
  displays.Print(1, 3);
  delay(1000);
  writeOnMatrix(0, 0);
  writeOnMatrix(0, 1);
  writeOnMatrix(0, 2);
  displays.Print(0, 1);
  displays.Print(0, 2);
  displays.Print(0, 3);
}

void Flag() {
  for (int j = 0; j < 5; j++) {
    for (int i = 4; i < 12; i++) {
      writeOnMatrix(i, 0);
      writeOnMatrix(i, 1);
      writeOnMatrix(i, 2);
      delay(300);
    }
  }
}

void writeOnMatrix(int numero, int tela)
{
  //O array abaixo forma o numero 0
  byte N0[8] = {
    B00111100,
    B01111110,
    B01100110,
    B01100110,
    B01100110,
    B01100110,
    B01111110,
    B00111100
  };
  //numero 1
  byte N1[8] = {
    B00111000,
    B01111000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B01111110,
    B01111110
  };
  //numero 2
  byte N2[8] = {
    B00111100,
    B01111110,
    B01100110,
    B00001110,
    B00011100,
    B00111000,
    B01111110,
    B01111110
  };
  //numero 3
  byte N3[8] = {
    B00111100,
    B01111110,
    B01100110,
    B00011110,
    B00011110,
    B01100110,
    B01111110,
    B00111100
  };

  byte Bandeira1[8] = {
    B11110000,
    B11110000,
    B11110000,
    B11110000,
    B00001111,
    B00001111,
    B00001111,
    B00001111
  };
  byte Bandeira2[8] = {
    B01111000,
    B01111000,
    B01111000,
    B01111000,
    B10000111,
    B10000111,
    B10000111,
    B10000111
  };
  byte Bandeira3[8] = {
    B00111100,
    B00111100,
    B00111100,
    B00111100,
    B11000011,
    B11000011,
    B11000011,
    B11000011
  };
  byte Bandeira4[8] = {
    B00011110,
    B00011110,
    B00011110,
    B00011110,
    B11100001,
    B11100001,
    B11100001,
    B11100001
  };
  byte Bandeira5[8] = {
    B00001111,
    B00001111,
    B00001111,
    B00001111,
    B11110001,
    B11110001,
    B11110001,
    B11110001
  };
  byte Bandeira6[8] = {
    B10000111,
    B10000111,
    B10000111,
    B10000111,
    B01111000,
    B01111000,
    B01111000,
    B01111000
  };
  byte Bandeira7[8] = {
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B00111100,
    B00111100,
    B00111100,
    B00111100
  };
  byte Bandeira8[8] = {
    B11100001,
    B11100001,
    B11100001,
    B11100001,
    B00011110,
    B00011110,
    B00011110,
    B00011110
  };

  //Mostra no display selecionado o numero correspondente
  switch (numero)
  {
    case 0:
      lc.setRow(tela, 0, N0[0]);
      lc.setRow(tela, 1, N0[1]);
      lc.setRow(tela, 2, N0[2]);
      lc.setRow(tela, 3, N0[3]);
      lc.setRow(tela, 4, N0[4]);
      lc.setRow(tela, 5, N0[5]);
      lc.setRow(tela, 6, N0[6]);
      lc.setRow(tela, 7, N0[7]);
      break;
    case 1:
      lc.setRow(tela, 0, N1[0]);
      lc.setRow(tela, 1, N1[1]);
      lc.setRow(tela, 2, N1[2]);
      lc.setRow(tela, 3, N1[3]);
      lc.setRow(tela, 4, N1[4]);
      lc.setRow(tela, 5, N1[5]);
      lc.setRow(tela, 6, N1[6]);
      lc.setRow(tela, 7, N1[7]);
      break;
    case 2:
      lc.setRow(tela, 0, N2[0]);
      lc.setRow(tela, 1, N2[1]);
      lc.setRow(tela, 2, N2[2]);
      lc.setRow(tela, 3, N2[3]);
      lc.setRow(tela, 4, N2[4]);
      lc.setRow(tela, 5, N2[5]);
      lc.setRow(tela, 6, N2[6]);
      lc.setRow(tela, 7, N2[7]);
      break;
    case 3:
      lc.setRow(tela, 0, N3[0]);
      lc.setRow(tela, 1, N3[1]);
      lc.setRow(tela, 2, N3[2]);
      lc.setRow(tela, 3, N3[3]);
      lc.setRow(tela, 4, N3[4]);
      lc.setRow(tela, 5, N3[5]);
      lc.setRow(tela, 6, N3[6]);
      lc.setRow(tela, 7, N3[7]);
      break;
    case 4:
      lc.setRow(tela, 0, Bandeira1[0]);
      lc.setRow(tela, 1, Bandeira1[1]);
      lc.setRow(tela, 2, Bandeira1[2]);
      lc.setRow(tela, 3, Bandeira1[3]);
      lc.setRow(tela, 4, Bandeira1[4]);
      lc.setRow(tela, 5, Bandeira1[5]);
      lc.setRow(tela, 6, Bandeira1[6]);
      lc.setRow(tela, 7, Bandeira1[7]);
      break;
    case 5:
      lc.setRow(tela, 0, Bandeira2[0]);
      lc.setRow(tela, 1, Bandeira2[1]);
      lc.setRow(tela, 2, Bandeira2[2]);
      lc.setRow(tela, 3, Bandeira2[3]);
      lc.setRow(tela, 4, Bandeira2[4]);
      lc.setRow(tela, 5, Bandeira2[5]);
      lc.setRow(tela, 6, Bandeira2[6]);
      lc.setRow(tela, 7, Bandeira2[7]);
      break;
    case 6:
      lc.setRow(tela, 0, Bandeira3[0]);
      lc.setRow(tela, 1, Bandeira3[1]);
      lc.setRow(tela, 2, Bandeira3[2]);
      lc.setRow(tela, 3, Bandeira3[3]);
      lc.setRow(tela, 4, Bandeira3[4]);
      lc.setRow(tela, 5, Bandeira3[5]);
      lc.setRow(tela, 6, Bandeira3[6]);
      lc.setRow(tela, 7, Bandeira3[7]);
      break;
    case 7:
      lc.setRow(tela, 0, Bandeira4[0]);
      lc.setRow(tela, 1, Bandeira4[1]);
      lc.setRow(tela, 2, Bandeira4[2]);
      lc.setRow(tela, 3, Bandeira4[3]);
      lc.setRow(tela, 4, Bandeira4[4]);
      lc.setRow(tela, 5, Bandeira4[5]);
      lc.setRow(tela, 6, Bandeira4[6]);
      lc.setRow(tela, 7, Bandeira4[7]);
      break;
    case 8:
      lc.setRow(tela, 0, Bandeira5[0]);
      lc.setRow(tela, 1, Bandeira5[1]);
      lc.setRow(tela, 2, Bandeira5[2]);
      lc.setRow(tela, 3, Bandeira5[3]);
      lc.setRow(tela, 4, Bandeira5[4]);
      lc.setRow(tela, 5, Bandeira5[5]);
      lc.setRow(tela, 6, Bandeira5[6]);
      lc.setRow(tela, 7, Bandeira5[7]);
      break;
    case 9:
      lc.setRow(tela, 0, Bandeira6[0]);
      lc.setRow(tela, 1, Bandeira6[1]);
      lc.setRow(tela, 2, Bandeira6[2]);
      lc.setRow(tela, 3, Bandeira6[3]);
      lc.setRow(tela, 4, Bandeira6[4]);
      lc.setRow(tela, 5, Bandeira6[5]);
      lc.setRow(tela, 6, Bandeira6[6]);
      lc.setRow(tela, 7, Bandeira6[7]);
      break;
    case 10:
      lc.setRow(tela, 0, Bandeira7[0]);
      lc.setRow(tela, 1, Bandeira7[1]);
      lc.setRow(tela, 2, Bandeira7[2]);
      lc.setRow(tela, 3, Bandeira7[3]);
      lc.setRow(tela, 4, Bandeira7[4]);
      lc.setRow(tela, 5, Bandeira7[5]);
      lc.setRow(tela, 6, Bandeira7[6]);
      lc.setRow(tela, 7, Bandeira7[7]);
      break;
    case 11:
      lc.setRow(tela, 0, Bandeira8[0]);
      lc.setRow(tela, 1, Bandeira8[1]);
      lc.setRow(tela, 2, Bandeira8[2]);
      lc.setRow(tela, 3, Bandeira8[3]);
      lc.setRow(tela, 4, Bandeira8[4]);
      lc.setRow(tela, 5, Bandeira8[5]);
      lc.setRow(tela, 6, Bandeira8[6]);
      lc.setRow(tela, 7, Bandeira8[7]);
      break;
  }
}
