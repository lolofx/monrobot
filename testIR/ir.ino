#include <IRremote.h>

int IRpin = 2;
int pinLed = 13;
int diff;
int touche = 0;
int nbreTouche = 21;// Nbre de touche prise en compte
int button[21][31] = {// 30 à 60
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

int checkKey(int IRSignal, int i, int count, int *key, int line){
//   Serial.print("KEY>");
//   Serial.print(key[i-30]);
//   Serial.print("IR>");
//   Serial.print(IRSignal);
  diff = (short)(abs(key[i-29]) - IRSignal); // was key[i]
  if(i>0){
    if(diff < 0){diff = diff * -1;}
    if(diff > 150 ){return -3;}// -3 break
  }
  if (i==(count-10)){return key[0];}
  else{return -2;}; // go on
}

IRrecv irrecv(IRpin);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(pinLed, OUTPUT);
}

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
        Serial.print("Touche appuyée n°: ");
        Serial.println(touche, DEC);
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

void loop(){
  if(irrecv.decode(&results) == 1){
    dump(&results);
    // ACTION EN FONCTION DE LA TOUCHE APPUYEE
      if(touche == 1){// Allumage de la LED
        digitalWrite(pinLed, HIGH);
      }
      else if(touche == 3){// Extection de la LED
        digitalWrite(pinLed, LOW);
      }
      else{}
    ////////////////////////////////////
    irrecv.resume();
  }
}