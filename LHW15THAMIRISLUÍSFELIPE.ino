#include <Adafruit_LiquidCrystal.h>

// Definição de pinos
int ledPinVerde = 13;
int ledPinVermelho = 11;
int ledPinAzul = 10;

int buttonPin1 = 7;

int buttonPin2 = 6;


int buzzerPin = 8;

int ldrPin = A0; 


int LM35 = A1; 


int pwmPin = A2;



Adafruit_LiquidCrystal lcd(0);

void setup() {
  pinMode(ledPinVerde, OUTPUT);
  pinMode(ledPinVermelho, OUTPUT);
  pinMode(ledPinAzul, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2); 
  lcd.print("PT:    L1:  L2: "); 
  lcd.setCursor(0, 1);
  lcd.print("TP:      LD:"); 

  Serial.begin(9600);
}

float temp(){ 
  float temperatura;
  temperatura = (float(((((analogRead(LM35) * 5.0) / 1023) * 1000) - 500) / 10));
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  return temperatura;
}

void escreveTemperaturaLCD(float temperatura) {
 
  lcd.setCursor(3, 1); 
  lcd.print(temperatura, 2); 
  lcd.print(" "); 
}

int botao1() {
  int buttonState1=0;
  buttonState1 = digitalRead(buttonPin1);
  Serial.print("Botao 1: ");
  Serial.println(buttonState1);
  return buttonState1;
}

void ledVerde(int buttonState1) {
  if (buttonState1== HIGH) {
    digitalWrite(ledPinVerde, LOW);
  } else {
    digitalWrite(ledPinVerde, HIGH);
  }
}

void escreveLedVerdeLCD(int buttonState1) {
  lcd.setCursor(10, 0); 
  lcd.print(buttonState1 == HIGH ? "D" : "L");
}

int ldrVlr() {
  int ldrValor;
  
  ldrValor = analogRead(ldrPin);
  Serial.print("LDR: ");
  Serial.println(ldrValor);
  return ldrValor;
}

void toneControl(int ldrValor) {
  if (ldrValor >= 900) {
    noTone(buzzerPin);
  } else {
    tone(buzzerPin, 2000);
  }
}

void escreveLDRLCD(int ldrValor) {
  lcd.setCursor(12, 1); 
  lcd.print(ldrValor);
  lcd.print(" "); 
}

int botao2() {
  int buttonState2 = 0;
  buttonState2 = digitalRead(buttonPin2);
  Serial.print("Botao 2: ");
  Serial.println(buttonState2);
  return buttonState2;
}

void ledVermelho(int buttonState2) {
  if (buttonState2 == HIGH) {
    digitalWrite(ledPinVermelho, LOW);
  } else {
    digitalWrite(ledPinVermelho, HIGH);
  }
}

void escreveLedVermelhoLCD(int buttonState2) {
  lcd.setCursor(15, 0); 
  lcd.print(buttonState2 == HIGH ? "D" : "L");
}

int potenciometro(int valorLido = 0) {
  valorLido = analogRead(pwmPin);
  Serial.print("Potenciometro: ");
  Serial.println(valorLido);
  return valorLido;
}

int calculo(int valorLido) {
  int pwm=0;
  pwm = map(valorLido, 0, 1023, 0, 255);
  return pwm;
}

void escrevePotenciometroLCD(int pwm) {
  lcd.setCursor(3, 0); 
  lcd.print(pwm);
  lcd.print(" "); 
}

void ledAzul(int pwm) {
  analogWrite(ledPinAzul, pwm);
}

void loop() {
  
  // Lê e calcula a temperatura
  float temperatura = temp();
  escreveTemperaturaLCD(temperatura);

  // Lê o botão 1 e controla o LED verde
  int buttonState1 = botao1();
  ledVerde(buttonState1);
  escreveLedVerdeLCD(buttonState1);

  // Lê o valor do LDR e controla o buzzer
  int ldrValor = ldrVlr();
  toneControl(ldrValor);
  escreveLDRLCD(ldrValor);

  // Lê o botão 2 e controla o LED vermelho
  int buttonState2 = botao2();
  ledVermelho(buttonState2);
  escreveLedVermelhoLCD(buttonState2);

  // Lê o potenciômetro e calcula o PWM
  int valorLido = potenciometro();
  int pwm = calculo(valorLido);
  escrevePotenciometroLCD(pwm);

  // Controla o LED azul
  ledAzul(pwm);
}