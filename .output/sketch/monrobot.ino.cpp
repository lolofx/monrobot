#include <Arduino.h>
#line 1 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
#line 1 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
/*
 Name:		monrobot.ino
 Created:	01/07/2018 14:08:05
 Author:	Loic
*/

#include <NewPing.h>
#include <IRremote.h>
//#include <RobotIRremote.h>

//erreur de compile a cause de conflit entre newping et irremote : https://bitbucket.org/teckel12/arduino-new-ping/wiki/Multiple%20Definition%20of%20%22__vector_7%22%20Error

//voir le fichier excel pour les pin
#define ledVertePin       11  // LED vert droit
#define ledRougePin       12  // LED rouge gauche
#define ECHO_PIN      7   // echo sonar
#define TRIGGER_PIN   8   // declencheur sonar.
//#define buzzerPin     3   // Buzzer
#define IRpin     4   // Ir reciever
#define MOTOR_A_B     10   // Motor A pin 1, A-IB, DIR
#define MOTOR_A_A     6   // Motor A pin 2, A-IA, PWM
#define MOTOR_B_B     9  // Motor B pin 1, B-IB, DIR
#define MOTOR_B_A     5   // Motor B pin 2, B-IA, PWM

#define UP    0xFF629D
#define DOWN  0xFFA857
#define RIGHT 0xFFC23D
#define LEFT  0xFF22DD
#define OK    0xFF02FD
#define NUM_1 0xFF6897
#define NUM_2 0xFF9867
#define NUM_3 0xFFB04F
#define NUM_4 0xFF30CF
#define NUM_5 0xFF18E7
#define NUM_6 0xFF7A85
#define NUM_7 0xFF10EF
#define NUM_8 0xFF38C7
#define NUM_9 0xFF5AA5
#define NUM_0 0xFF4AB5
#define STAR  0xFF42BD
#define HASH  0xFF52AD

// Vitesse du motoeur (a régler)
#define PWM_SLOW    80     
#define PWM_FAST    150   

int modeAuto = 0; //mode automatique de la voiture ou manuel

// Sonar 
#define MAX_DISTANCE 200  // Distance max du ping du sonar en mm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int distActuelle = 0;        // distance de l'objet

//Zone pour le IR 
//int diff;
int touche = 0;
int nbreTouche = 21;// Nbre de touche prise en compte
int button[21][31] = {//  l aliste des signaux
  {1,1600,600,1600,600,1600,600,1600,650,500,650,1600,550,550,650,500,650,500,650,1600,600,500,650,500,650,1600,600,550,600,1600,600},
  {2,1650,600,1600,600,1650,550,550,600,1650,550,1650,600,550,550,550,650,550,600,1600,600,550,550,1650,600,550,600,550,600,1600,600},
  {3,1700,550,1700,500,1650,600,1650,500,1700,550,1650,550,650,500,650,500,650,500,1650,550,600,550,600,550,600,550,600,550,1650,550},
  {4,1600,600,1650,550,1650,600,500,600,550,600,1600,650,500,600,550,600,550,600,1600,600,600,550,1650,600,1600,600,550,600,1600,600},
  {5,1600,650,1550,600,1650,600,550,550,600,600,500,600,550,600,550,650,500,600,1600,650,500,650,1600,550,1650,600,1600,600,1600,650},
  {6,1600,650,1600,550,1650,600,1600,600,1600,600,550,650,550,550,550,600,550,600,1600,600,550,600,600,550,550,600,1600,600,1650,600},
  {7,1600,600,1600,650,1600,600,1600,600,1600,600,1600,650,500,650,500,600,550,600,550,600,550,600,550,600,550,600,550,600,1600,600},
  {8,1600,600,1600,650,1600,550,1650,600,550,600,1600,600,550,600,1600,600,550,600,550,600,550,600,550,600,1600,600,550,600,1600,650},
  {9,1650,600,1650,550,1650,600,1600,600,550,550,600,550,1650,550,600,600,550,550,600,600,550,550,600,550,1650,550,1650,600,550,550},
  {10,1600,650,1600,550,1650,600,550,600,1600,600,1650,600,500,600,1650,600,550,600,550,600,500,600,1650,600,550,600,550,600,1600,600},
  {11,1600,600,1600,650,1600,600,1600,600,550,600,550,600,1600,600,1600,600,550,600,550,600,550,600,550,600,1600,600,1600,650,500,650},
  {12,1650,600,1650,550,1650,600,1600,550,600,600,1600,600,1650,550,550,600,550,600,550,600,550,550,600,600,1600,600,550,600,550,600},
  {13,1600,650,1550,650,1600,600,550,600,550,600,1600,600,1600,600,550,600,550,600,550,600,550,600,1600,600,1600,600,550,600,550,600},
  {14,1600,650,1600,600,1600,600,550,600,550,600,550,600,1600,600,1600,600,550,600,550,650,500,600,1600,600,1600,650,1600,600,500,650},
  {15,1600,600,1600,600,1650,600,550,600,1600,600,1600,600,1600,650,1600,600,550,550,1650,600,550,600,1600,600,550,600,550,600,550,600},
  {16,1650,600,1600,600,1600,650,500,600,550,600,550,600,1600,600,550,600,550,600,550,600,550,600,1600,600,1600,650,1600,550,550,650},
  {17,1650,600,1600,600,1600,650,500,600,550,600,1600,600,1650,600,1600,600,550,600,550,600,550,600,1600,600,1600,600,550,600,550,600},
  {18,1600,650,1600,600,1600,600,550,600,1600,600,550,600,1600,600,1600,650,500,650,1600,600,550,600,1600,600,550,600,1600,600,550,600},
  {19,1600,600,1600,650,1600,600,550,600,1600,600,550,600,550,600,550,600,550,550,1650,600,550,600,1600,600,550,600,1600,600,1650,600},
  {20,1550,650,1600,600,1600,600,550,600,1600,600,550,600,550,600,1600,600,550,600,1600,650,500,600,1600,650,500,650,1600,600,1600,600},
  {21,1600,600,1600,650,1550,650,500,650,1600,600,500,650,1600,600,550,600,550,600,1600,600,550,600,1600,600,550,600,1600,600,550,600},
};

//config du IRRemote
IRrecv irrecv(IRpin);
decode_results results;

#line 86 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
void setup();
#line 103 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
void loop();
#line 132 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
void decodeIR();
#line 175 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
void phares(int touche);
#line 207 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
void avance(int speed);
#line 221 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
void droite(int speed);
#line 235 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
void gauche(int speed);
#line 248 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
void recule(int speed);
#line 262 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
void stop();
#line 275 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
int lectureDistance();
#line 292 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
int checkKey(int IRSignal, int i, int count, int *key, int line);
#line 309 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
int dump(decode_results *results);
#line 86 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(ledVertePin,OUTPUT);          // Led output
  pinMode(ledRougePin,OUTPUT);          // Led output
  pinMode( MOTOR_A_A, OUTPUT );
  pinMode( MOTOR_A_B, OUTPUT );
  pinMode( MOTOR_B_A, OUTPUT );
  pinMode( MOTOR_B_B, OUTPUT );
  
   digitalWrite(ledVertePin, LOW);    //verte
   digitalWrite(ledRougePin, LOW);    //rouge
   stop();
}

void loop()
{
   decodeIR();
   distActuelle = lectureDistance();
   if(modeAuto == 1) //mode automatique
   {
      if (distActuelle<20) {
        stop();
        delay(100);
        recule(PWM_SLOW);
        delay(1000);
        stop();
        delay(100);
        droite(PWM_SLOW);
        delay(1000);
        stop();
        delay(100);
      }else{
        avance(PWM_FAST);
      }
   }else //mode manuel
   {
      if (distActuelle<10) {
        stop();
      }
   }
}


void decodeIR(){
 if(irrecv.decode(&results) == 1){
    dump(&results);//Lecture du IR
    // ACTION EN FONCTION DE LA TOUCHE APPUYEE
    switch (touche)
    {
      case 1: // Touche 1  => bascule en mode auto ou eteint le mode auto
        if(modeAuto == 0)  
        {
          modeAuto =1; 
          //Serial.println("Mode auto actif");
        }else {
          modeAuto=0;
          stop();
          //Serial.println("Mode manuel");
        }
        delay(500);
        break;
    
      case 10:
      case 11:
      case 12: phares(touche);
        break;

      
        case 17: stop(); break;
        case 14: stop(); avance(PWM_FAST); break;
        case 16: stop(); gauche(PWM_SLOW); break;
        case 18: stop(); droite(PWM_SLOW); break;
        case 20: stop(); recule(PWM_FAST); break;

      default:
        break;
    }
     
    ////////////////////////////////////
    irrecv.resume();
  }
}

/**
 * Gère l'allumage des phares
 * **/
void phares(int touche){
  if(touche == 10){//  touche * allume ou eteind le phare gauche
       if(digitalRead(ledRougePin) == LOW)
        digitalWrite(ledRougePin, HIGH);
        else
          digitalWrite(ledRougePin, LOW);
        //Serial.println("LED Rouge");
        delay(500);
      }
      else if(touche == 12){// //  touche # allume ou eteind lephare droit
        
         if(digitalRead(ledVertePin) == LOW)
         digitalWrite(ledVertePin, HIGH);
         else
          digitalWrite(ledVertePin, LOW);
        //Serial.println("LED Verte");
        delay(500);
      }
      else if(touche == 11){// touche 0 allume ou eteind les 2 phares 
        bool isOff = digitalRead(ledRougePin) == LOW && digitalRead(ledVertePin) == LOW;
        if(isOff){
         digitalWrite(ledRougePin, HIGH);
         digitalWrite(ledVertePin, HIGH);
        }else{
          digitalWrite(ledRougePin, LOW);
         digitalWrite(ledVertePin, LOW);
        }
         //Serial.println("Les 2 LEDs");
         delay(500);
      }
}

void avance(int speed)
{
  digitalWrite(MOTOR_A_A,LOW);
  digitalWrite(MOTOR_B_A,LOW);
  analogWrite(MOTOR_A_B,speed+8); //moteur B plus rapide
  analogWrite(MOTOR_B_B,speed);

if(modeAuto == 1){
  digitalWrite(ledVertePin, HIGH);    
  digitalWrite(ledRougePin, HIGH);
  }
  //Serial.println("Avance ..."); 
}

void droite(int speed)
{
  analogWrite(MOTOR_A_A,speed);
  digitalWrite(MOTOR_B_A,LOW);
  digitalWrite(MOTOR_A_B,LOW);
  analogWrite(MOTOR_B_B,speed);

if(modeAuto == 1){
  digitalWrite(ledVertePin, HIGH);   
  digitalWrite(ledRougePin, LOW);  
  }
  //Serial.println("Tourne droite ...");  
}

void gauche(int speed)
{
  digitalWrite(MOTOR_A_A,LOW);
  analogWrite(MOTOR_B_A,speed);
  analogWrite(MOTOR_A_B,speed);
  digitalWrite(MOTOR_B_B,LOW);
if(modeAuto == 1){
  digitalWrite(ledRougePin, HIGH);
  digitalWrite(ledVertePin, LOW); 
  }
  //Serial.println("Tourne gauche ...");
}

void recule(int speed)
{
  analogWrite(MOTOR_A_A,speed);
  analogWrite(MOTOR_B_A,speed);
  digitalWrite(MOTOR_A_B,LOW);
  digitalWrite(MOTOR_B_B,LOW);

 if(modeAuto == 1){
    digitalWrite(ledVertePin, LOW);   
    digitalWrite(ledRougePin, LOW); 
  }
  //Serial.println("Recule ...");
}

void stop()
{
  digitalWrite(MOTOR_A_A,LOW);
  digitalWrite(MOTOR_B_A,LOW);
  digitalWrite(MOTOR_A_B,LOW);
  digitalWrite(MOTOR_B_B,LOW);
  if(modeAuto == 1){
    digitalWrite(ledVertePin, LOW);   
    digitalWrite(ledRougePin, LOW); 
  }
  //Serial.println("... STOP ...");
}

int lectureDistance() { // Envoi la distance mesurÃ©e par le capteur de distance
	delay(70);
	// unsigned int uS = sonar.ping(); // lance la function â€˜pingâ€™ de lâ€™objet â€˜sonarâ€™
	// cm = uS / US_ROUNDTRIP_CM; // converti la distance en
  int cm = sonar.ping_cm();
	if (cm == 0) {
		lectureDistance();
	}
	else {
		Serial.println("Distance objet :"+cm);
		return cm;
	}
}

/**
 * Verifie sur quelle touche de la telecommande on appuie et surtout on verifie qu'elle existe
 */
int checkKey(int IRSignal, int i, int count, int *key, int line){
//   Serial.print("KEY>");
//   Serial.print(key[i-30]);
//   Serial.print("IR>");
//   Serial.print(IRSignal);
  int diff = (short)(abs(key[i-29]) - IRSignal); // was key[i]
  if(i>0){
    if(diff < 0){diff = diff * -1;}
    if(diff > 150 ){return -3;}// -3 break
  }
  if (i==(count-10)){return key[0];}
  else{return -2;}; // go on
}

/**
 * Décrypte le signal de la telecommande
 * */
int dump(decode_results *results) {
  int count = results->rawlen;

 if(count == 4){
    return -1;
  }
  //Serial.println(count, DEC);
  for(int y = 0; y < (nbreTouche+1); y++){
    for (int i = 30; i < (count-4); i++) { // was i=0
      touche = checkKey(results->rawbuf[i]*USECPERTICK,i-0,count,button[y],y );
      if (touche == -3){
        //Serial.print("Touche non reconnue ! ");
        break;
      };
      if (touche > -2 ){
        Serial.println("Touche appuyée n°: ");
        Serial.print(touche, DEC);
        return touche;
      };
      if (y == nbreTouche){
        touche = 0;
        Serial.println("Touche introuvable !");
        return touche;
      }
    }
  }
  delay(10);
}

