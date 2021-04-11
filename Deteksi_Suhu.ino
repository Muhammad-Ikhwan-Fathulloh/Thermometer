//HADID-TECHNOLOGY
//Creator = Muhammad Ikhwan Fathulloh
//Version 1.0

//Library
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Adafruit_MLX90614.h>

//Sensor Jarak
#define trigPin 13
#define echoPin 12

//Sensor Suhu
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

//LCD Display
LiquidCrystal_I2C lcd(0x27,16,3); 

//Servo
Servo palang;

//Buzzer
const int buzzer = 6;

//IR Sensor
int sensor = 7;

void setup()
{
  //Sensor Suhu
  mlx.begin();

  //LCD
  lcd.clear();
  lcd.init();                      
  lcd.backlight();

  //Servo
  palang.attach(5);
  
  //Buzzer
  pinMode(buzzer, OUTPUT);

  //IR Sensor
  pinMode(sensor, INPUT);

  //Sensor Jarak
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}


void loop()
{   
  long durasi, jarak;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durasi = pulseIn(echoPin, HIGH);
  jarak = (durasi/2) / 29.1;

  if(jarak < 15){
    delay(1000);
    lcd.clear();
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
    lcd.setCursor(2,1);
    lcd.print("Suhu Anda: ");
    lcd.print(mlx.readObjectTempC());
    lcd.print("C    ");
    delay(500);      

    if(mlx.readObjectTempC()>37){
      delay(1000);
      lcd.setCursor(2,2);
      lcd.print(" Anda Tidak Sehat ");
      digitalWrite(buzzer, HIGH);
      delay(3000);
      digitalWrite(buzzer, LOW);
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      delay(1000);
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      delay(1000);
    }
    else{
      lcd.setCursor(2,2);   
      lcd.print("  Anda Sehat  ");
      palang.write(170);
      delay(5000);
    }
    delay(500);
  }
  else{
    delay(1000);
    lcd.clear();
    lcd.print("  Selamat Datang di ");
    lcd.setCursor(2,1);
    lcd.print(" SMKN 8 Bandung ");
    lcd.setCursor(2,2);
    lcd.print(" Jurusan TEI ");
    lcd.setCursor(2,3);
    lcd.print("Silahkan Cek Suhu");
    palang.write(75);
  }
  delay(500);
}
