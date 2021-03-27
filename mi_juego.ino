/*
 * 
 * PROYECO DESARROLLADO POR MIGUEL MARTINEZ MATEOS
 * 
 */




#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
Adafruit_SSD1306 display(128, 64, &Wire, 4);

//enemies
int enemie1_x = 130; //el recorrido es de 130 a -30 es decir 160 entonces la otra deberia ir a 160+128 para ir equidistantes pero si lo altero un poco es más dificil y queda menos medido y mas natural
int enemie2_x = 240;
uint8_t duracionsalto = 11;
int8_t vel_enem = -5;
unsigned long tiempo_actual = 0;
unsigned long tiempo_aux = 0;
boolean lock = 0;
boolean lock2 = 0;
boolean locklives = 0;
boolean lockscore = 0;
unsigned int rando = 0;
unsigned int rando2 = 0;
int8_t estado = 0; //0 para normal, 1 para saltando y 2 para agachado
boolean muerto = 0;
uint8_t lives = 1;
int score = 0;

//sounds
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;



//mario
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


void setup() {

  pinMode(3, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
  display.setTextSize(2);
  display.setFont();
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.println("SUPERMARIO");
  display.display();
  delay(2000);
  display.clearDisplay();
  delay(500);
  Serial.begin(115200);
  display.display();

}

volatile int agachado = 0;
volatile int saltar = 0;
volatile boolean runn = 0;
int block_buttons = 0;

void loop() {
  if (muerto == 0) {
    display.clearDisplay();

    ////////dibujar fondo/////////////
    display.drawBitmap(20, 0, cloud, 32, 24, 1);//el primero es la dcha, el segundo el alto
    //display.drawBitmap(36, 0, cloud, 32, 24, 1);
    display.drawBitmap(95, 5, cloud, 32, 24, 1);
    //display.drawLine(0,63,128,63,1);

    //  display.setTextSize(1); //////////esto seria para abajo en el centro
    //  display.setCursor(40, 57);
    //    display.print("lives:");
    //    display.setCursor(75, 57);//la primera debe ser la del anterior +35
    //    display.print(lives);


    ///////////////////////////////////
    ////////dibujar marios/////////////

    if (block_buttons == 0) {
      if (digitalRead(11) == 0) {
        agachado = duracionsalto;                                    //duracion de agacharse
        block_buttons = 1;
      }
      if (digitalRead(3) == 0) {
        saltar = duracionsalto;                                      //duracion de salto
        block_buttons = 1;
      }
    }

    if (saltar > 0 && block_buttons) {
      if (saltar > (duracionsalto - 1)) {
        display.drawBitmap(0, 30, mario_jump, 16, 28, 1);
      }
      else if (saltar > 1) {
        display.drawBitmap(0, 18, mario_jump, 16, 28, 1);
      } else {
        display.drawBitmap(0, 30, mario_jump, 16, 28, 1);
      }
      saltar--;
      estado = 1;
    } else if (agachado > 0 && block_buttons) {
      display.drawBitmap(0, 44, mario_bend, 19, 20, 1);
      agachado--;
      estado = 2;
    } else {
      estado = 0;
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
      rando = random(0, 2); //con esto 50% 0 50% 1 xq el ultimo no se alcanza
      lock = 1;
    }
    if (rando == 0) {
      display.drawBitmap(enemie1_x, 30, misile, 19, 14, 1);

    } else {
      display.drawBitmap(enemie1_x, 47, enemie, 17, 17, 1);
    }
    if (enemie1_x <= -30) { //no muy bajo xq cuando la velocidad sea -5 por ejemplo igual no lo alcanza, ni muy alto para que se lleue e aver el cambio en pantalla
      lock = 0;
      enemie1_x = 200;
    }
    enemie1_x = enemie1_x + vel_enem;

    ////////////////segundo enemigo/////////////
    if (lock2 == 0) {
      rando2 = random(0, 13); //de 0 a 12 CAMBIAR POR 12 AL ACABAR
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
    if (enemie2_x <= -30) { //no muy bajo xq cuando la velocidad sea -5 por ejemplo igual no lo alcanza, ni muy alto para que se lleue e aver el cambio en pantalla
      lock2 = 0;
      enemie2_x = 200;
    }
    enemie2_x = enemie2_x + vel_enem;

    ////////////aumentar velocida enemigos con el tiempo/////////////
    tiempo_actual = millis();
    if (((tiempo_actual - tiempo_aux) > 30000)) { // Esta parte se ejecuta cada
      tiempo_aux = tiempo_actual;             // 35000ms es decir cada 50 segundos
      vel_enem--;
      duracionsalto--;//negativo xq vamos en direccion -x y asi se aumenta
    }

    ///////////comprobar colision/////////////
    if ((enemie2_x <= 12) && (enemie2_x > -23) && locklives == 0) { //con -22 con el misil va muy bien con el enemie con 25
      if (((estado == 2 || estado == 0) && rando2 > 9)) {
        lives++;
        locklives = 1; //bloqueo para que no se quiten muchas vidas de golpe

      } else if (lockscore == 0) {
        score++;
        lockscore = 1;
      }
    }
    if ((enemie1_x <= 12) && (enemie1_x > -23) && locklives == 0) { //con -22 con el misil va muy bien con el enemie con 25
      if (((estado == 2 || estado == 0) && rando == 1) || ((estado == 1 || estado == 0) && rando == 0)) {
        lives--;
        locklives = 1;
      } else if (lockscore == 0) {
        score++;
        lockscore = 1;
      }
    }
    if ((enemie2_x <= 12) && (enemie2_x > -23) && locklives == 0) {
      if (((estado == 2 || estado == 0) && rando2 > 4 && rando2 < 10) || ((estado == 1 || estado == 0) && rando2 < 5)) {
        lives--;
        locklives = 1;
      } else if (lockscore == 0) {
        score++;
        lockscore = 1;
      }
    }

    if (enemie1_x < -20 || enemie2_x < -20) {//desbloqueamos
      locklives = 0;
      lockscore = 0;
    }


    if (lives == 0) {//cambiar por musiquita super mario
      //tone(9, 200, 300);
      //delay(300);
      //tone(9, 250, 200);
      //delay(200);
      //tone(9, 300, 300);
      //delay(300);
      muerto = 1;
    }
    display.setTextSize(1);
    display.setCursor(50, 0);
    display.print("L:");
    display.setCursor(63, 0);//la primera debe ser la del anterior +35
    display.print(lives);
    display.setCursor(75, 0);
    display.print("S:");
    display.setCursor(88, 0);//la primera debe ser la del anterior +35
    display.print(score);
    display.display();
  }
  if (muerto == 1) {
    display.setTextSize(2);
    display.setFont();
    display.setTextColor(WHITE);
    display.setCursor(5, 20);
    display.println("GAME OVER");
    display.display();
    delay(2000);
    if (digitalRead(3) == 0)
    {
      //      tone(9, 280, 300);
      //      delay(300);
      //      tone(9, 250, 200);
      //      delay(200);
      //      tone(9, 370, 300);
      //      delay(300);
      reinicio();
    }
  }
}



void reinicio()
{
  muerto = 0;
  tiempo_actual = 0;
  lives = 1;
  score = 0;
  enemie1_x = 130;
  enemie2_x = 240;
  vel_enem = -5;
  tiempo_actual = 0;
  tiempo_aux = 0;
  lock = 0;
  lock2 = 0;
  block_buttons = 0;
  duracionsalto = 11;
  locklives = 0;
  rando = 0;
  rando2 = 0;
  estado = 0;
}

void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(9, note, duration);
  delay(duration);
  noTone(9);
  delay(50);

}
