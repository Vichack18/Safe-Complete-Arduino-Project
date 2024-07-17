#include <Keypad.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

const byte FILAS=4; // PQ vamos a usar 4 filas del pad //
const byte COLUMNAS=3; // " " columnas //
char keys[FILAS][COLUMNAS]{
  {'1','2','3'}, 
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
}; // QUE ES LO QUE el arduino tiene que leer cada vez q apretemos botones, esta expresado de manera
// textual //

// En donde estan conectadas las filas y columnas //
byte pinesFilas[FILAS]={8,7,6,5};
byte pinesColumnas[COLUMNAS]={4,3,2};

Keypad teclado=Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS); 
// Funcion de la libreria //
char TECLA; // Almacenara la tecla que presionemos del pad
int ledr=10,leda=11,ledv=12,ledb=13;

// variables de estado Ej: si el led esta apagado y apretamos el numero 1 se va a prender //
int estador=0;
int estadoa=0,estadov=0,estadob=0;

Servo servo; // creamos objeto //
LiquidCrystal_I2C lcd(0x27, 19, 4); // en caso de no funcionar cambiar 0x27 por 0x3f // 

void setup() {
  // put your setup code here, to run once:
 Serial.begin (9600);
 pinMode (ledr, OUTPUT);
 pinMode (leda, OUTPUT);
 pinMode (ledv, OUTPUT);
 pinMode (ledb, OUTPUT);
 servo.attach(9);
 servo.write(0); // para que se ponga a 0 grados cuando se inicie el arduino //

 lcd.init(); // inicializamos el lcd //
 lcd.backlight();

 lcd.setCursor(0,0); // En que posicion del lcd se tiene que imprimir el mensaje // El primer numero representa 
 // el numero de la columna y el segundo el numero de filas //
 lcd.print("Hola, sea bienvenido");
 delay(2000);
 lcd.clear(); // limpiar por completo el lcd


}

void loop() {
  // put your main code here, to run repeatedly:
  TECLA=teclado.getKey(); // tecla = a lo que lea de mi teclado // A lo que presione se guarda en TECLA
  if (TECLA){
    Serial.println(TECLA); // Imprimir que teclas estamos apretando
  }

  if (TECLA=='1'){  // Si se presiona 1, si esta en 0 se prende y cambia estado a 1, y sino, si esta en 1 se apaga y cambia estado a 0 //
    if (estador==0){
      digitalWrite(ledr,HIGH);
      estador=1;
      lcd.setCursor(0,0);
      lcd.print("Led rojo on");
      delay(2000);
      lcd.clear();
    }
    else{
      digitalWrite(ledr,LOW);
      estador=0;
      lcd.setCursor(0,0);
      lcd.print("Led rojo off");
      delay(2000);
      lcd.clear();
    }
  }

  if (TECLA=='2'){  // Si se presiona 1, si esta en 0 se prende y cambia estado a 1, y sino, si esta en 1 se apaga y cambia estado a 0 //
    if (estadoa==0){
      digitalWrite(leda,HIGH);
      estadoa=1;
      lcd.setCursor(0,0);
      lcd.print("Led amarillo on"); // se pone "on" ya que sino excede las 20 columnas del display
      delay(2000);
      lcd.clear();
    }
    else{
      digitalWrite(leda,LOW);
      estadoa=0;
      lcd.setCursor(0,0);
      lcd.print("Led amarillo off");
      delay(2000);
      lcd.clear();
    }
  }

  if (TECLA=='3'){  // Si se presiona 1, si esta en 0 se prende y cambia estado a 1, y sino, si esta en 1 se apaga y cambia estado a 0 //
    if (estadov==0){
      digitalWrite(ledv,HIGH);
      estadov=1;
      lcd.setCursor(0,0);
      lcd.print("Led verde on");
      delay(2000);
      lcd.clear();
    }
    else{
      digitalWrite(ledv,LOW);
      estadov=0;
      lcd.setCursor(0,0);
      lcd.print("Led verde off");
      delay(2000);
      lcd.clear();
    }
  }

  if (TECLA=='4'){  // Si se presiona 1, si esta en 0 se prende y cambia estado a 1, y sino, si esta en 1 se apaga y cambia estado a 0 //
    if (estadob==0){
      digitalWrite(ledb,HIGH);
      estadob=1;
      lcd.setCursor(0,0);
      lcd.print("Led blanco on");
      delay(2000);
      lcd.clear();
    }
    else{
      digitalWrite(ledb,LOW);
      estadob=0;
      lcd.setCursor(0,0);
      lcd.print("Led blanco off");
      delay(2000);
      lcd.clear();
    }
  }

  if (TECLA=='5'){
    servo.write(180);
    lcd.setCursor(0,0);
      lcd.print("Servo a 180g");
      delay(2000);
      lcd.clear();
  }
  if (TECLA=='6'){
    servo.write(90);
    lcd.setCursor(0,0);
      lcd.print("Servo a 90g");
      delay(2000);
      lcd.clear();
  }
  if (TECLA=='7'){
    servo.write(0);
    lcd.setCursor(0,0);
      lcd.print("Servo a 0g");
      delay(2000);
      lcd.clear();
  }

}