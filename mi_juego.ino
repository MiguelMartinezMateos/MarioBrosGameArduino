/*

   PROYECO DESARROLLADO POR MIGUEL MARTINEZ MATEOS

*/
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
Adafruit_SSD1306 display(128, 64, &Wire, 4);


#define crashsound1 1100
#define crashsound2 1500
#define jumpsound 1200
#define bendsound 1500


//enemies
int enemie1_x = 130; //el recorrido es de 130 a -30 es decir 160 entonces la otra deberia ir a 160+128 para ir equidistantes pero si lo altero un poco es más dificil y queda menos medido y mas natural
int enemie2_x = 240;
uint8_t jumpduration = 11;
int8_t enem_vel = -5;
unsigned long current_time = 0;
unsigned long aux_time = 0;
boolean lock = 0;
boolean lock2 = 0;
boolean locklives = 0;
boolean lockscore = 0;
unsigned int rando = 0;
unsigned int rando2 = 0;
int8_t state = 0; //0 para normal, 1 para saltando y 2 para agachado
boolean dead = 0;
uint8_t lives = 1;
int score = 0;

//sounds
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951

#define melodyPin 9


//sounds
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 0, NOTE_C7, NOTE_E7, 0, NOTE_G7, 0, 0,  0, NOTE_G6, 0, 0, 0, NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0, 0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0, NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0, NOTE_C7, NOTE_D7, NOTE_B6, 0, 0
};
int tempo[] = {
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12
};

//graphics
const unsigned char PROGMEM mario[] = {
  0x1, 0xE0, 0x6, 0x10, 0x8, 0x10, 0x10, 0xDC, 0x23, 0xFE, 0x26, 0x2C, 0x7C, 0x58, 0x4C, 0x5C, 0x4C, 0x2, 0x4E, 0x2, 0x44, 0x82, 0x21, 0xC7, 0x18, 0x5C, 0x3C, 0x30, 0x47, 0xC0, 0x47, 0x34, 0x88, 0xBA, 0x90, 0x4A, 0x90, 0x4C, 0xC8, 0x94, 0x7F, 0x34, 0x7F, 0xFE, 0x3F, 0xFD, 0x5F, 0xF9, 0x5F, 0x71, 0x4E, 0x11, 0x21, 0x12, 0x1F, 0xC
};
const unsigned char PROGMEM mario2[] = {
  0x1, 0xE0, 0x6, 0x10, 0x8, 0x10, 0x10, 0xDC, 0x23, 0xFE, 0x26, 0x2C, 0x7C, 0x58, 0x4C, 0x5C, 0x4C, 0x2, 0x4E, 0x2, 0x44, 0x82, 0x21, 0xC7, 0x18, 0x5C, 0x3C, 0x30, 0x47, 0xC6, 0x5F, 0x39, 0x91, 0x39, 0xA0, 0x89, 0xA0, 0x8E, 0xD1, 0x14, 0x7F, 0x34, 0x7F, 0xFC, 0xBF, 0xFC, 0x9F, 0xF8, 0x9F, 0x74, 0x8E, 0xC2, 0x90, 0x82, 0x60, 0x7C
};
const unsigned char PROGMEM mario_bend[] = {
  0x0, 0x1E, 0x0, 0x0, 0x61, 0x0, 0x0, 0x81, 0x0, 0x1, 0xD, 0xC0, 0x2, 0x3F, 0xE0, 0x2, 0x60, 0xC0, 0x7, 0xC5, 0x0, 0x4, 0xC5, 0xC0, 0x34, 0xC0, 0x20, 0x4C, 0xE0, 0x20, 0x84, 0x48, 0x20, 0x87, 0x1C, 0x60, 0x88, 0x8B, 0x80, 0x90, 0x4E, 0x0, 0xF0, 0x5C, 0x0, 0x78, 0xFC, 0x0, 0x7F, 0xFC, 0x0, 0x11, 0xFF, 0x0, 0x20, 0xF8, 0x80, 0x3F, 0x9F, 0x80,
};
const unsigned char PROGMEM mario_jump[] = {
  0x1, 0xE0, 0x6, 0x10, 0x8, 0x10, 0x10, 0xDC, 0x23, 0xFE, 0x26, 0x2C, 0x7C, 0x58, 0x4C, 0x5C, 0x4C, 0x2, 0x4E, 0x2, 0x44, 0x82, 0x21, 0xC7, 0x18, 0x5C, 0x3C, 0x32, 0x47, 0xC2, 0x47, 0x32, 0xB8, 0x3C, 0xC4, 0x8, 0x82, 0xF, 0x82, 0x15, 0x44, 0x35, 0xFF, 0xFD, 0xBF, 0xFD, 0x9F, 0xFE, 0x9F, 0x70, 0x6E, 0x0, 0x0, 0x0, 0x0, 0x0
};
const unsigned char PROGMEM misile[] = {
  0x3, 0xF3, 0x20, 0xE, 0xC, 0x60, 0x3D, 0xFB, 0xA0, 0x77, 0xFF, 0x40, 0x67, 0xFF, 0x80, 0xA7, 0xFF, 0x40, 0x87, 0x9F, 0x20, 0xCF, 0x8F, 0xC0, 0xFC, 0x8F, 0x0, 0x78, 0x1F, 0x60, 0x78, 0x7F, 0x80, 0x3F, 0xFF, 0xA0, 0xF, 0xFF, 0x40, 0x3, 0xF3, 0x20,
};
const unsigned char PROGMEM enemie[] = {
  0x3, 0xE0, 0x0, 0x4, 0x10, 0x0, 0x28, 0xA, 0x0, 0x10, 0x4, 0x0, 0x28, 0xA, 0x0, 0x4C, 0x19, 0x0, 0x4A, 0x29, 0x0, 0x8F, 0x78, 0x80, 0x86, 0x30, 0x80, 0x80, 0x0, 0x80, 0xC0, 0x1, 0x80, 0x7F, 0xFF, 0x0, 0x8, 0x8, 0x0, 0x38, 0xE, 0x0, 0x7C, 0x1F, 0x0, 0x7F, 0xFF, 0x0, 0x3E, 0x3E, 0x0,
};
const unsigned char PROGMEM cloud[] = {
  0x0, 0x3, 0xC0, 00000000, 0x0, 0x4, 0x20, 00000000, 0x0, 0x18, 0x10, 00000000, 0x0, 0x20, 0x14, 00000000, 0x0, 0x20, 0xA, 00000000, 0x0, 0x20, 0x21, 00000000, 0x0, 0x46, 0x11, 00000000, 0x0, 0x88, 0x1, 00000000, 0x7, 0x0, 0x0, 10010000, 0x8, 0x0, 0x0, 10101000, 0x10, 0x0, 0x0, 01001000, 0x0, 0x0, 0x0, 00001010, 0x60, 0x0, 0x0, 00000101, 0x80, 0x0, 0x0, 00000001, 0x80, 0x0, 0x0, 00000001, 0x40, 0x0, 0x0, 00000010, 0x24, 0x0, 0x20, 00000100, 0x12, 0x20, 0x40, 00000010, 0x9, 0xF1, 0xE1, 00000001, 0x8, 0xF, 0xBE, 00000000, 0x7, 0x8C, 0x1C, 00000110, 0x0, 0x41, 0x0, 10011000, 0x0, 0x32, 0xC3, 01100000, 0x0, 0xC, 0x3C, 00000000,
};
const unsigned char PROGMEM mushroom[] = {
  0x7, 0xF0, 0x0, 0x1F, 0xCC, 0x0, 0x27, 0xC2, 0x0, 0x4F, 0xE1, 0x0, 0x58, 0x31, 0x0, 0xF0, 0x1F, 0x80, 0xF0, 0x19, 0x80, 0xB0, 0x10, 0x80, 0x98, 0x30, 0x80, 0x9F, 0xF9, 0x80, 0xBF, 0xFF, 0x80, 0x72, 0x27, 0x0, 0x22, 0x22, 0x0, 0x20, 0x2, 0x0, 0x10, 0x4, 0x0, 0xF, 0xF8, 0x0,
};
const unsigned char PROGMEM mariowallpaper[] = {  //size 64X64
  0x0, 0x0, 0x0, 0x0, 0x40, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x3F, 0x88, 0x0, 0x80, 0x0, 0x7, 0x0, 0x1, 0xFF, 0x19, 0x80, 0x40, 0x0, 0x8, 0x80, 0xF, 0xFE, 0x2A, 0x80, 0x40, 0x0, 0x8, 0x40, 0x3F, 0xFC, 0x2A, 0x80, 0x20, 0x0, 0x8, 0x40, 0x7F, 0xFC, 0x44, 0x80, 0x20, 0x0, 0x8, 0x20, 0xFF, 0xFC, 0x41, 0x0, 0x30, 0x0, 0x4, 0x21, 0xFE, 0x3, 0x1, 0x0, 0x18, 0x0, 0x4, 0x13, 0xF8, 0x0, 0xC2, 0x0, 0x1C, 0x0, 0x2, 0x1F, 0xF0, 0x10, 0x30, 0x0, 0x1E, 0x0, 0x2, 0xF, 0xF0, 0x8, 0x8, 0x0, 0xF, 0x0, 0x1, 0xF, 0xE0, 0x6, 0x4, 0x0, 0xF, 0x0, 0x1, 0x7, 0xE0, 0x1, 0x82, 0x0, 0xF, 0x80, 0x6, 0x87, 0xE0, 0x0, 0x41, 0x0, 0xF, 0x80, 0x8, 0x83, 0xE0, 0x0, 0x20, 0x80, 0xF, 0xC0, 0x3B, 0xE3, 0xF0, 0xF8, 0x1E, 0x40, 0x7, 0xC0, 0x4C, 0x11, 0xF1, 0xFF, 0xFF, 0x20, 0x7, 0xE0, 0x48, 0x9, 0xF9, 0x84, 0x65, 0xA0, 0x7, 0xE0, 0x48, 0x0, 0xFD, 0x0, 0x42, 0x90, 0x7, 0xF0, 0x28, 0x0, 0xFF, 0x30, 0x1, 0x10, 0x7, 0xF0, 0x64, 0x0, 0xFF, 0x48, 0x31, 0x8, 0x7, 0xF0, 0x93, 0xC0, 0xFE, 0x84, 0x48, 0x88, 0x7, 0xF8, 0x89, 0x20, 0xFE, 0x9C, 0x84, 0x84, 0x7, 0xF8, 0x86, 0x21, 0x3E, 0x9C, 0x84, 0x44, 0x3, 0xF8, 0x41, 0x10, 0x3F, 0x9C, 0x84, 0x3E, 0x3, 0xFC, 0x32, 0x0, 0x78, 0x68, 0x9C, 0x2, 0x2, 0x7C, 0x2C, 0x0, 0xA0, 0x10, 0x9C, 0x1, 0x2, 0x7C, 0x20, 0x1, 0x20, 0x8, 0x58, 0x3, 0x2, 0x3E, 0x10, 0x1, 0x40, 0x0, 0x30, 0x7, 0x80, 0x3E, 0x10, 0x2, 0x40, 0x0, 0x0, 0x3F, 0x80, 0x3E, 0x38, 0xC, 0x40, 0x8, 0xE, 0x7F, 0xC0, 0x3E, 0x38, 0x30, 0xE0, 0x8, 0xFE, 0x7F, 0xDC, 0x3E, 0x3F, 0xC0, 0xE0, 0x1F, 0xFC, 0x3F, 0xE2, 0x3F, 0x3F, 0x80, 0x78, 0x7F, 0xF0, 0x7F, 0x81, 0x7F, 0x3F, 0x80, 0x7F, 0xFF, 0xE0, 0xFE, 0x1, 0xFF, 0x3F, 0xC0, 0x5F, 0xFF, 0x80, 0xFC, 0x19, 0xFF, 0x1F, 0xC0, 0x4D, 0xB0, 0x0, 0x70, 0x21, 0xFF, 0x1F, 0xE0, 0x40, 0x1, 0xE0, 0x0, 0x51, 0xFF, 0x1F, 0xE0, 0x23, 0xFE, 0x20, 0x0, 0x63, 0xFF, 0x1F, 0xF0, 0x10, 0x80, 0x20, 0x0, 0x43, 0xFF, 0x1F, 0xF0, 0x10, 0xFF, 0xE0, 0x0, 0x27, 0xFF, 0x1F, 0xF8, 0x8, 0xFF, 0xC0, 0x2, 0x7, 0xFF, 0x1F, 0xF8, 0x8, 0xC0, 0x80, 0x7, 0xF, 0xFE, 0xF, 0xFC, 0x8, 0x40, 0x80, 0xF, 0xFF, 0xFE, 0xF, 0xFE, 0x4, 0x7F, 0x0, 0xFF, 0xFF, 0xFE, 0xF, 0xFF, 0x4, 0x0, 0x3, 0x1F, 0xFF, 0xFE, 0x7, 0xFF, 0x8B, 0x0, 0xC, 0x27, 0xFF, 0xFE, 0x7, 0xFF, 0xD0, 0x80, 0x70, 0xC1, 0xFF, 0xFC, 0x7, 0xFF, 0xE1, 0x7F, 0x81, 0x0, 0x7F, 0xFC, 0x3, 0xFF, 0xE2, 0x0, 0x81, 0x0, 0x1F, 0xF8, 0x3, 0xFF, 0xCC, 0x1, 0x2, 0x0, 0xF, 0xF8, 0x1, 0xFF, 0xC8, 0x7E, 0x3, 0x80, 0x7, 0xF0, 0x1, 0xFF, 0x88, 0x87, 0xC6, 0x40, 0x3, 0xF0, 0x0, 0xFF, 0x91, 0x0, 0x3C, 0x7C, 0x3, 0xE0, 0x0, 0xFF, 0x16, 0x0, 0x44, 0x43, 0x1, 0xC0, 0x0, 0x7F, 0x98, 0x0, 0x22, 0x20, 0x81, 0x80, 0x0, 0x7E, 0x5B, 0x0, 0x0, 0x20, 0x0, 0x80, 0x0, 0x3C, 0x3C, 0x3, 0x80, 0x20, 0x0, 0x80, 0x0, 0x3C, 0x38, 0x0, 0x0, 0x20, 0x0, 0x80, 0x0, 0x1C, 0x30, 0x0, 0x0, 0x20, 0x0, 0x80, 0x0, 0xC, 0x31, 0x3, 0x80, 0x20, 0x0, 0x80, 0x0, 0x2, 0x51, 0x0, 0x2, 0x40, 0x1, 0x0, 0x0, 0x1, 0x88, 0x80, 0x2, 0x40, 0x2, 0x0,
};



void setup() {
  pinMode(3, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
  display.drawBitmap(0, 0, mariowallpaper, 64, 64, 1);
  display.setTextSize(0);
  display.setFont();
  display.setTextColor(WHITE);
  display.setCursor(70, 0);
  display.println("ARDUGAME");
  display.setFont(&FreeSans9pt7b);

  display.setCursor(64, 20);
  display.println("MARIO");
  display.display();

  display.setFont();
  display.setCursor(85, 23);
  display.println("by");
  display.display();

  display.setFont();
  display.setCursor(70, 33);
  display.println("MMMateos");
  display.display();

  display.setCursor(70, 48);
  display.println("A = Jump");
  display.setCursor(70, 57);
  display.println("B = Bend");

  display.display();

  music(0);
  delay(1000);
}

volatile int agachado = 0;
volatile int saltar = 0;
volatile boolean runn = 0;
int block_buttons = 0;

void loop() {
  if (dead == 0) {
    display.clearDisplay();

    ////////dibujar fondo/////////////
    display.drawBitmap(17, 0, cloud, 32, 24, 1);//el primero es la dcha, el segundo el alto
    //display.drawBitmap(36, 0, cloud, 32, 24, 1);
    display.drawBitmap(95, 5, cloud, 32, 24, 1);
    ///////////////////////////////////
    ////////dibujar marios/////////////

    if (block_buttons == 0) {
      if (digitalRead(11) == 0) {
        agachado = jumpduration;                                    //duracion de agacharse
        block_buttons = 1;
      }
      if (digitalRead(3) == 0) {
        saltar = jumpduration;                                      //duracion de salto
        block_buttons = 1;
      }
    }

    if (saltar > 0 && block_buttons) {
      if (saltar > (jumpduration - 1)) {
        display.drawBitmap(0, 30, mario_jump, 16, 28, 1);

        tone(9, jumpsound, 10);
      }
      else if (saltar > 1) {
        display.drawBitmap(0, 18, mario_jump, 16, 28, 1);

        state = 1;
      } else {
        display.drawBitmap(0, 30, mario_jump, 16, 28, 1);
      }
      saltar--;
    } else if (agachado > 0 && block_buttons) {
      display.drawBitmap(0, 44, mario_bend, 19, 20, 1);
      if (agachado > jumpduration - 1) {
        tone(9, bendsound, 10);
      }
      agachado--;
      state = 2;
    } else {
      state = 0;
      if (runn == 0) {
        display.drawBitmap(0, 36, mario2, 16, 28, 1);
        runn = 1;
      } else {
        display.drawBitmap(0, 36, mario, 16, 28, 1);
        runn = 0;
        block_buttons = 0;
      }
    }
    ///////////////////////////////////////
    ///////////dibujar enemigos/////////////

    if (lock == 0) {
      rando = random(0, 2); // 50% 0, 50% 1
      lock = 1;
    }
    if (rando == 0) {
      display.drawBitmap(enemie1_x, 30, misile, 19, 14, 1);

    } else {
      display.drawBitmap(enemie1_x, 47, enemie, 17, 17, 1);
    }
    if (enemie1_x <= -30) { //not so big to be displayed the change, and not so small because is not changing 1 by 1 and could not be raised.
      lock = 0;
      enemie1_x = 200;
    }
    enemie1_x = enemie1_x + enem_vel;

    ////////////////segundo enemigo/////////////
    if (lock2 == 0) {
      rando2 = random(0, 13); //from 0 to 12
      lock2 = 1;
    }
    if (rando2 > 9) {
      display.drawBitmap(enemie2_x, 48, mushroom, 19, 16, 1);
    } else if (rando2 < 5) {
      display.drawBitmap(enemie2_x, 30, misile, 19, 14, 1);
    }
    else {
      display.drawBitmap(enemie2_x, 47, enemie, 17, 17, 1);
    }
    if (enemie2_x <= -30) {
      lock2 = 0;
      enemie2_x = 200;
    }
    enemie2_x = enemie2_x + enem_vel;

    ////////////increase speed over time/////////////
    current_time = millis();
    if (((current_time - aux_time) > 30000)) { // next lines happens every 30000ms = 30 seconds
      aux_time = current_time;
      enem_vel--;
      jumpduration--;//negative bc we are going in the direction -x so is not raimusic
    }

    ///////////check collision/////////////
    if ((enemie2_x < 10) && (enemie2_x > -23) && locklives == 0) { //at -23 is out of the screen
      if (((state == 2 || state == 0) && rando2 > 9)) {
        if (lives < 5) {
          lives++;
          locklives = 1; //blocked to add just one live
          tone(9, crashsound2, 100);
          delay(100);
          tone(9, crashsound1, 300);
        }
      } else if (lockscore == 0) {
        score++;
        lockscore = 1;
      }
    }
    if ((enemie1_x < 10) && (enemie1_x > -23) && locklives == 0) {
      if (((state == 2 || state == 0) && rando == 1) || ((state == 1 || state == 0) && rando == 0)) {
        lives--;
        locklives = 1;
        tone(9, crashsound1, 100);
        delay(100);
        tone(9, crashsound2, 300);
      } else if (lockscore == 0) {
        score++;
        lockscore = 1;
      }
    }
    if ((enemie2_x < 10) && (enemie2_x > -23) && locklives == 0) {
      if (((state == 2 || state == 0) && rando2 > 4 && rando2 < 10) || ((state == 1 || state == 0) && rando2 < 5)) {
        lives--;
        locklives = 1;
        tone(9, crashsound1, 100);
        delay(100);
        tone(9, crashsound2, 300);
      } else if (lockscore == 0) {
        score++;
        lockscore = 1;
      }
    }

    if (enemie1_x < -20 || enemie2_x < -20) {//unlock
      locklives = 0;
      lockscore = 0;
    }

    display.setTextSize(1);
    display.setCursor(50, 0);
    display.print("L:");
    display.setCursor(63, 0);
    display.print(lives);
    display.setCursor(75, 0);
    display.print("S:");
    display.setCursor(88, 0);
    display.print(score);
    display.display();


    if (lives == 0) {
      delay(500);
      music(1);
      dead = 1;
    }
  }
  if (dead == 1) {
    display.clearDisplay();
    display.setTextSize(0);
    display.setFont(&FreeSans9pt7b);
    display.setCursor(7, 25);
    display.println("GAME OVER");

    display.setFont();
    display.setCursor(37, 36);
    display.print("Score: ");
    display.setCursor(73, 36);
    display.print(score);

    display.setCursor(0, 54);
    display.print("Press C to play again");


    display.display();
    if (digitalRead(12) == 0)
    {
      reinicio();
    }
  }
}



void reinicio()
{
  dead = 0;
  current_time = 0;
  lives = 1;
  score = 0;
  enemie1_x = 130;
  enemie2_x = 240;
  enem_vel = -5;
  current_time = 0;
  aux_time = 0;
  lock = 0;
  lock2 = 0;
  block_buttons = 0;
  jumpduration = 11;
  locklives = 0;
  rando = 0;
  rando2 = 0;
  state = 0;
}

void music(int song) {
  if (song == 0) {
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
      int noteDuration = 1000 / tempo[thisNote];
      buzzer(melodyPin, melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      buzzer(melodyPin, 0, noteDuration);
    }
  } else if (song == 1) {
    int size = 13;
    for (int thisNote = 0; thisNote < size; thisNote++) {
      int noteDuration = 1000 / tempo[thisNote];
      buzzer(melodyPin, melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      buzzer(melodyPin, 0, noteDuration);
    }
  }
}

void buzzer(int targetPin, long frequency, long length) {
  digitalWrite(13, HIGH);
  long delayValue = 1000000 / frequency / 2;
  long numCycles = frequency * length / 1000;
  for (long i = 0; i < numCycles; i++) {
    digitalWrite(targetPin, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(targetPin, LOW);
    delayMicroseconds(delayValue);
  }
}
