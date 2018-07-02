# 1 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
# 1 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
/*

 Name:		monrobot.ino

 Created:	01/07/2018 14:08:05

 Author:	Loic

*/
# 7 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
# 8 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino" 2
# 9 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino" 2
//#include <RobotIRremote.h>

//erreur de compile a cause de conflit entre newping et irremote : https://bitbucket.org/teckel12/arduino-new-ping/wiki/Multiple%20Definition%20of%20%22__vector_7%22%20Error

//voir le fichier excel pour les pin




//#define buzzerPin     3   // Buzzer
# 43 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
// Vitesse du motoeur (a régler)



int modeAuto = 0; //mode automatique de la voiture ou manuel

// Sonar 

NewPing sonar(8 /* declencheur sonar.*/, 7 /* echo sonar*/, 200 /* Distance max du ping du sonar en mm.*/); // NewPing setup of pins and maximum distance.
int distActuelle = 0; // distance de l'objet

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
IRrecv irrecv(4 /* Ir reciever*/);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(11 /* LED vert droit*/,0x1); // Led output
  pinMode(12 /* LED rouge gauche*/,0x1); // Led output
  pinMode( 6 /* Motor A pin 2, A-IA, PWM*/, 0x1 );
  pinMode( 10 /* Motor A pin 1, A-IB, DIR*/, 0x1 );
  pinMode( 5 /* Motor B pin 2, B-IA, PWM*/, 0x1 );
  pinMode( 9 /* Motor B pin 1, B-IB, DIR*/, 0x1 );

   digitalWrite(11 /* LED vert droit*/, 0x0); //verte
   digitalWrite(12 /* LED rouge gauche*/, 0x0); //rouge
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
        recule(80);
        delay(500);
        stop();
        delay(100);
        droite(80);
        delay(500);
        stop();
        delay(100);
      }else{
        avance(150);
      }
   }else //mode manuel
   {
      if (distActuelle<20) {
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
        case 14: stop(); avance(150); break;
        case 16: stop(); gauche(80); break;
        case 18: stop(); droite(80); break;
        case 20: stop(); recule(150); break;

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
# 175 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
void phares(int touche){
  if(touche == 10){//  touche * allume ou eteind le phare gauche
       if(digitalRead(12 /* LED rouge gauche*/) == 0x0)
        digitalWrite(12 /* LED rouge gauche*/, 0x1);
        else
          digitalWrite(12 /* LED rouge gauche*/, 0x0);
        //Serial.println("LED Rouge");
        delay(500);
      }
      else if(touche == 12){// //  touche # allume ou eteind lephare droit

         if(digitalRead(11 /* LED vert droit*/) == 0x0)
         digitalWrite(11 /* LED vert droit*/, 0x1);
         else
          digitalWrite(11 /* LED vert droit*/, 0x0);
        //Serial.println("LED Verte");
        delay(500);
      }
      else if(touche == 11){// touche 0 allume ou eteind les 2 phares 
        bool isOff = digitalRead(12 /* LED rouge gauche*/) == 0x0 && digitalRead(11 /* LED vert droit*/) == 0x0;
        if(isOff){
         digitalWrite(12 /* LED rouge gauche*/, 0x1);
         digitalWrite(11 /* LED vert droit*/, 0x1);
        }else{
          digitalWrite(12 /* LED rouge gauche*/, 0x0);
         digitalWrite(11 /* LED vert droit*/, 0x0);
        }
         //Serial.println("Les 2 LEDs");
         delay(500);
      }
}

void avance(int speed)
{
  digitalWrite(6 /* Motor A pin 2, A-IA, PWM*/,0x0);
  digitalWrite(5 /* Motor B pin 2, B-IA, PWM*/,0x0);
  analogWrite(10 /* Motor A pin 1, A-IB, DIR*/,speed+6); //moteur B plus rapide
  analogWrite(9 /* Motor B pin 1, B-IB, DIR*/,speed);

if(modeAuto == 1){
  digitalWrite(11 /* LED vert droit*/, 0x1);
  digitalWrite(12 /* LED rouge gauche*/, 0x1);
  }
  //Serial.println("Avance ..."); 
}

void droite(int speed)
{
  analogWrite(6 /* Motor A pin 2, A-IA, PWM*/,speed);
  digitalWrite(5 /* Motor B pin 2, B-IA, PWM*/,0x0);
  digitalWrite(10 /* Motor A pin 1, A-IB, DIR*/,0x0);
  analogWrite(9 /* Motor B pin 1, B-IB, DIR*/,speed);

if(modeAuto == 1){
  digitalWrite(11 /* LED vert droit*/, 0x1);
  digitalWrite(12 /* LED rouge gauche*/, 0x0);
  }
  //Serial.println("Tourne droite ...");  
}

void gauche(int speed)
{
  digitalWrite(6 /* Motor A pin 2, A-IA, PWM*/,0x0);
  analogWrite(5 /* Motor B pin 2, B-IA, PWM*/,speed);
  analogWrite(10 /* Motor A pin 1, A-IB, DIR*/,speed);
  digitalWrite(9 /* Motor B pin 1, B-IB, DIR*/,0x0);
if(modeAuto == 1){
  digitalWrite(12 /* LED rouge gauche*/, 0x1);
  digitalWrite(11 /* LED vert droit*/, 0x0);
  }
  //Serial.println("Tourne gauche ...");
}

void recule(int speed)
{
  analogWrite(6 /* Motor A pin 2, A-IA, PWM*/,speed);
  analogWrite(5 /* Motor B pin 2, B-IA, PWM*/,speed);
  digitalWrite(10 /* Motor A pin 1, A-IB, DIR*/,0x0);
  digitalWrite(9 /* Motor B pin 1, B-IB, DIR*/,0x0);

 if(modeAuto == 1){
    digitalWrite(11 /* LED vert droit*/, 0x0);
    digitalWrite(12 /* LED rouge gauche*/, 0x0);
  }
  //Serial.println("Recule ...");
}

void stop()
{
  digitalWrite(6 /* Motor A pin 2, A-IA, PWM*/,0x0);
  digitalWrite(5 /* Motor B pin 2, B-IA, PWM*/,0x0);
  digitalWrite(10 /* Motor A pin 1, A-IB, DIR*/,0x0);
  digitalWrite(9 /* Motor B pin 1, B-IB, DIR*/,0x0);
  if(modeAuto == 1){
    digitalWrite(11 /* LED vert droit*/, 0x0);
    digitalWrite(12 /* LED rouge gauche*/, 0x0);
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
# 292 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
int checkKey(int IRSignal, int i, int count, int *key, int line){
//   Serial.print("KEY>");
//   Serial.print(key[i-30]);
//   Serial.print("IR>");
//   Serial.print(IRSignal);
  int diff = (short)(((key[i-29])>0?(key[i-29]):-(key[i-29])) - IRSignal); // was key[i]
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
# 309 "c:\\Users\\lolof.DESKTOP-J21SAV6\\Github\\MonRobot\\monrobot\\monrobot.ino"
int dump(decode_results *results) {
  int count = results->rawlen;

 if(count == 4){
    return -1;
  }
  //Serial.println(count, DEC);
  for(int y = 0; y < (nbreTouche+1); y++){
    for (int i = 30; i < (count-4); i++) { // was i=0
      touche = checkKey(results->rawbuf[i]*50,i-0,count,button[y],y );
      if (touche == -3){
        //Serial.print("Touche non reconnue ! ");
        break;
      };
      if (touche > -2 ){
        Serial.println("Touche appuyée n°: ");
        Serial.print(touche, 10);
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
