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
byte pinesFilas[FILAS]={2,3,4,5};
byte pinesColumnas[COLUMNAS]={6,7,8}; // cambiamos  filas y columnas en este programa

Keypad teclado=Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS); 
// Funcion de la libreria //
char TECLA; // Almacenara la tecla que presionemos del pad
char CLAVE [5];
char CLAVE_CORRECTA[5]="0000"; // Clave para comparar con la ingresada //
int INIDCE=0;
int ledr=11, ledv=12, buzzer=9, estado=0;


Servo servo; // creamos objeto //
LiquidCrystal_I2C lcd(0x27, 19, 4); // en caso de no funcionar cambiar 0x27 por 0x3f // 

void setup() {
  // put your setup code here, to run once:
 Serial.begin (9600);
 pinMode (ledr, OUTPUT);
 pinMode (ledv, OUTPUT);
 pinMode (buzzer, OUTPUT);
 pinMode (A3, INPUT); // Para el boton que nos va a permitir cambiar la contraseña de la caja //

 servo.attach(10);
 servo.write(0); // para que se ponga a 0 grados cuando se inicie el arduino //

 lcd.init(); // inicializamos el lcd //
 lcd.backlight();

 lcd.setCursor(0,0); // En que posicion del lcd se tiene que imprimir el mensaje // El primer numero representa 
 // el numero de la columna y el segundo el numero de filas //
 lcd.print("Hola, sea bienvenido");
 delay(2000);
 inicio();

}

void loop() {
  // put your main code here, to run repeatedly:
  TECLA=teclado.getKey(); // tecla = a lo que lea de mi teclado // A lo que presione se guarda en TECLA
 if (TECLA){
  CLAVE[INDICE]= TECLA;
  INDICE++;
  lcd.print(TECLA); // Lo que hace esto es ir guardando los numeros presionados en el array, aumentamos el indicie para usar 
  // todos las posiciones del arreglo, y cada tecla presionada se va a ir mostrando en el display // 
 }
 if (INDICE ==4){
  if (!strcmp (CLAVE, CLAVE_CORRECTA)){ // COMPARAR EL VALOR DE CLAVE CON CLAVE_CORRECTA, es lo que hace la funcion strcmp
      abierto();
  }
  else {
    error();
  }
  INDICE=0; // Nuestro contador de nuestro indice vuelve a esperar que presionemos mas teclas del pad //
  // para seguir comparandolos con la Clave maestra //
 }

  id(estado==1 && (digitalRead(A3)==0)){ // si estado 1 la caja esta abierta, y sino ( en 0) esta cerrada //
      nueva_clave();
  }

}

// funcion error //
void error (){
    lcd.setCursor(0,1);
    lcd.print("CLAVE ERROR ");

    for(int i=0;i<3;i++){
      digitalWrite(buzzer, HIGH);
      digitalWrite(ledr, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      digitalWrite(ledr, LOW);
      delay(200);
    }
    inicio();
}

// funcion abierto //
void abierto(){
  if (estado==0){
    estado=1;
    lcd.setCursor(0,1);
    lcd.print("Abierto ");
    servo.write(90);
    digitalWrite (buzzer, HIGH);
    digitalWrite (ledv, HIGH);
    delay(300);
    digitalWrite (buzzer, LOW);
    digitalWrite (ledv, LOW);
  }
  else {
    estado=0;
    lcd.setCursor(0,1);
    lcd.print ("Cerrado ");
    servo.write(0);
    digitalWrite (buzzer, HIGH);
    digitalWrite (ledv, HIGH);
    delay(300);
    digitalWrite (buzzer, LOW);
    digitalWrite (ledv, LOW);
  }
  inicio();
}

// funcion nueva clave //
void nueva_clave(){
  lcd.setCursor(0,0);
  lcd.print("Nueva Clave:   ");
  lcd.setCursor(12,0);
  INDICE=0;
  while(INDICE<=3){
    TECLA= teclado.getKey();
    if(TECLA){
      CLAVE_CORRECTA[INDICE]=TECLA;
      CLAVE[INDICE]=TECLA;
      INDICE++;
      lcd.print(TECLA); // Guardamos la tecla ingresada en ambos array de claves, la aumentamos y la mostramos //
    }
  }
  estado=0;
  lcd.setCursor(0,1);
  lcd.print("CLAVE CAMBIADA");
  delay(2000);
  inicio();
}

// funcion inicio // Espera medio segundo antes de limpiar el lcd, y pone Clave desde un comienzo, dando la ilusion //
// de que esta esperando a que nosotros apretemos la clave de nuestro teclado para acceder a la caja fuerte //
void inicio (){
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Clave:        ");
  lcd.setCursor(9,0);
}