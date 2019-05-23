
#define SensorSol 13
#define SensorOrta 12
#define SensorSag 11

#define echoPin 30
#define trigPin 41
#define buzzerPin 33


#define MotorR1 6
#define MotorR2 7 // Sensör ve Motorların Arduino'ya bağladığımız pinlerini tanımlıyoruz.
#define MotorRE 9

#define MotorL1 5
#define MotorL2 4
#define MotorLE 3

#define LedSol 22
#define LedSag 24



//
boolean cizgi=false;
boolean kontrol=false;
boolean surec = false;

//
char veri;
char veri2;



void setup() {
  Serial.begin(9600);  

  pinMode(SensorSol, INPUT);
  pinMode(SensorOrta, INPUT);
  pinMode(SensorSag, INPUT);

  pinMode(MotorR1, OUTPUT); // Sensör ve Motorların Giriş-Çıkış bilgilerini belirtiyoruz.
  pinMode(MotorR2, OUTPUT);

  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);

  //mesafe sensör için
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  //buzzer
  pinMode(buzzerPin, OUTPUT);


  pinMode(LedSol, OUTPUT);
  pinMode(LedSag, OUTPUT);





}

void loop() { 

    if(!surec){ //Sürec baslamamıssa 
          if(Serial.available()>0){
                  veri = Serial.read(); 
        
                  if(veri == 'c'){ 
                    cizgi = false;                   
                    kontrol = true;
                    surec = true;                   
                  }
                  
                   if(veri == 'o'){              
                    cizgi = true;                  
                    kontrol = false;
                    surec = true;                   
            
                    baslangic();
                  }
           
                   if(veri == 's'){
                     kontrol = true;
                     cizgi = false;
                     surec = true;                   
                  }
          }     
     }
    
      if(surec){                          
            if(cizgi){
                 cizgiIzleyen();
            }
            
            if(kontrol){
                kontrolleYonet();
            }
       }
}




void kontrolleYonet(){
       if(Serial.available() > 0){
                veri2 = Serial.read();
                Serial.print(veri2);  

                if(veri2 == 'i'){
                  Serial.print("ileri aktif");
                  ledSondur(); 
                    ileri();
                }
                if(veri2 == 'g'){
                   Serial.print("geri aktif");
                   ledSondur(); 
                    geri();
                }
                if(veri2 == 'l'){
                   Serial.print("sol aktif");
                   ledSondur(); 
              digitalWrite(LedSol,HIGH);
                  sol();
                }
                if(veri2 == 'r'){
                   Serial.print("sağ aktif");
                   ledSondur(); 
              digitalWrite(LedSag,HIGH);
                  sag();
                }
                if(veri2 == 'd'){
                  ledSondur(); 
                  dur();
                }
                if(veri2 == 'b'){
                    surec = false;
                    kontrol=false;
                    cizgi=false;
                    veri='r';
                    dur();
                }
        }
        
}

void cizgiIzleyen(){


  if(mesafe() == 1){
        dur();
        digitalWrite(buzzerPin, HIGH); 
  }else{
      digitalWrite(buzzerPin, LOW); 
      if(digitalRead(SensorSol) == 0 && digitalRead(SensorOrta) == 1 && digitalRead(SensorSag) == 0){  // Orta sensör çizgiyi gördüğünde robot ileri gitsin.
              Serial.print("ileri");
              ledSondur();
              ileri();
            }
          
            if(digitalRead(SensorSol) == 0 && digitalRead(SensorOrta) == 0 && digitalRead(SensorSag) == 1){  // Sağ sensör çizgiyi gördüğünde robot sağa dönsün.
              ledSondur(); 
              digitalWrite(LedSag,HIGH);
              sag();
          
            }
            if(digitalRead(SensorSol) == 0 && digitalRead(SensorOrta) == 1 && digitalRead(SensorSag) == 1){  // Sağ sensör çizgiyi gördüğünde robot sağa dönsün.
              ledSondur() ;        
              sag();
          
            }
          
            if(digitalRead(SensorSol) == 1 && digitalRead(SensorOrta) == 0 && digitalRead(SensorSag) == 0){  // Sol sensör çizgiyi gördüğünde robot sola dönsün.
              ledSondur();
              digitalWrite(LedSol,HIGH);
              sol();
            }
            
             if(digitalRead(SensorSol) == 1 && digitalRead(SensorOrta) == 1 && digitalRead(SensorSag) == 0){  // Sol sensör çizgiyi gördüğünde robot sola dönsün.
              ledSondur();
              sol();
            }
    
            if((digitalRead(SensorSol) == 1 && digitalRead(SensorOrta) == 1 && digitalRead(SensorSag) == 1)){
              ledSondur();
              ileri();
            }
    
            if(Serial.available() > 0){
               if(Serial.read()=='b'){
                    surec = false;
                    kontrol = false;
                    cizgi=false;
                    veri='r';
                    dur();
               }
            }
  }
}


void ledSondur(){
  digitalWrite(LedSol,LOW);
  digitalWrite(LedSag,LOW);
}


void ileri(){  
  digitalWrite(MotorR1, HIGH); 
  digitalWrite(MotorR2, LOW); 
  analogWrite(MotorRE, 102); 

  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW); 
  analogWrite(MotorLE, 110); 
}

void sag(){ // Robotun sağa dönme hareketi için fonksiyon tanımlıyoruz.
  digitalWrite(MotorR1, HIGH); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, LOW); // Sağ motoun geri hareketi pasif
  analogWrite(MotorRE, 0); 
  
  digitalWrite(MotorL1, HIGH); // Sol motorun ileri hareketi aktif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi pasif
  analogWrite(MotorLE, 96); 
}

void sagYavas(){ // Robotun sağa dönme hareketi için fonksiyon tanımlıyoruz.
  digitalWrite(MotorR1, HIGH); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, LOW); // Sağ motorun geri hareketi pasif
  analogWrite(MotorRE, 0); // Sağ motorun hızı 0 (Motor duruyor)

  digitalWrite(MotorL1, HIGH); // Sol motorun ileri hareketi aktif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi pasif
  analogWrite(MotorLE, 45); 
}

void sol(){ // Robotun sola dönme hareketi için fonksiyon tanımlıyoruz. 
  digitalWrite(MotorR1, HIGH); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, LOW); // Sağ motorun geri hareketi pasif
  analogWrite(MotorRE, 92); 

  digitalWrite(MotorL1, HIGH); // Sol motorun ileri hareketi aktif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi pasif
  analogWrite(MotorLE, 0); 
}

void solYavas(){ // Robotun sola dönme hareketi için fonksiyon tanımlıyoruz.
  digitalWrite(MotorR1, HIGH); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, LOW); // Sağ motorun geri hareketi pasif
  analogWrite(MotorRE, 45); 

  digitalWrite(MotorL1, HIGH); 
  digitalWrite(MotorL2, LOW); 
  analogWrite(MotorLE, 0); 
  
}

void geri(){  
  digitalWrite(MotorR1, LOW); 
  digitalWrite(MotorR2, HIGH); 
  analogWrite(MotorRE, 100); 

  digitalWrite(MotorL1, LOW); 
  digitalWrite(MotorL2, HIGH); 
  analogWrite(MotorLE, 100); 
}

void dur(){ 
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  digitalWrite(MotorRE, LOW);

  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
  digitalWrite(MotorLE, LOW);
}

int mesafe(){
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
  delay(50);
  if(distance > 15){
    return 50;
  }
  return 1;
}

 void baslangic(){
      for(int i=0 ; i < 5 ; i++){
            if(i==4){
                digitalWrite(buzzerPin,HIGH);
                delay(1000);
                digitalWrite(buzzerPin,LOW);
            }else{
                digitalWrite(buzzerPin,HIGH);
                delay(500);
                digitalWrite(buzzerPin,LOW);
                delay(500);
            }
        }
}
