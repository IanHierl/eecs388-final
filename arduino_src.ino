const int MOVEALEFT = 97;
const int MOVEARIGHT = 98;
const int MOVEBLEFT = 99;
const int MOVEBRIGHT = 100;
const int READPOTA = 101;
const int READPOTB = 102;
const int READDIST = 103;

const int MOTORA1 = 7;
const int MOTORA2 = 6;
const int MOTORAPWM = 5;
const int SLIDEPOTA = A0;
const int STANDBYPIN = 8;
const int MOTORB1 = 9;
const int MOTORB2 = 10;
const int MOTORBPWM = 11;
const int SLIDEPOTB = A1;
const int DISTPIN = A2;
const int DELAY = 25;     // in milliseconds
const int DUTY = 127;

void setup() {
  pinMode( MOTORA1, OUTPUT );
  pinMode( MOTORA2, OUTPUT );
  pinMode( MOTORAPWM, OUTPUT );
  pinMode( SLIDEPOTA, INPUT );
  pinMode( STANDBYPIN, OUTPUT );
  pinMode( MOTORB1, OUTPUT );
  pinMode( MOTORB2, OUTPUT );
  pinMode( MOTORBPWM, OUTPUT );
  pinMode( SLIDEPOTB, INPUT );
  pinMode( DISTPIN, INPUT );
  Serial.begin(9600);
}

void loop() {
  int len = Serial.available();
  while( len > 0 ) {
    int action = Serial.read();
    if( action == 10 ) { break; }
    
    handleAction( action );
    
    len = Serial.available();
  }
  digitalWrite( STANDBYPIN, LOW );
}

void handleAction( int act ) {
  switch( act ) {
    case MOVEALEFT:
    while( readPotA() > 100 ) {
      moveALeft( 50 );
      delay( 50 );
    }
    break;
    
    case MOVEARIGHT:
    while( readPotA() < 950 ) {
      moveARight( 50 );
      delay( 50 );
    }
    break;
    
    case MOVEBLEFT:
    moveBLeft( 50 );
    break;
    
    case MOVEBRIGHT:
    moveBRight( 50 );
    break;
    
    case READPOTA:
    readPotA();
    break;
    
    case READPOTB:
    readPotB();
    break;
    
    case READDIST:
    readDist();
    break;
    
    default:
    delay( 100 );
    break;
  }
}

void moveALeft( int del ) {
  digitalWrite( MOTORA1, HIGH );
  digitalWrite( MOTORA2, LOW );
  analogWrite( MOTORAPWM, DUTY );
  digitalWrite( STANDBYPIN, HIGH );
  
  delay( del );
  
  analogWrite( MOTORAPWM, 0 );
  digitalWrite( STANDBYPIN, LOW );
}

void moveARight( int del ) {
  digitalWrite( MOTORA1, LOW );
  digitalWrite( MOTORA2, HIGH );
  analogWrite( MOTORAPWM, DUTY );
  digitalWrite( STANDBYPIN, HIGH );
  
  delay( del );
  
  analogWrite( MOTORAPWM, 0 );
  digitalWrite( STANDBYPIN, LOW );
}

void moveBLeft( int del ) {
  digitalWrite( MOTORB1, HIGH );
  digitalWrite( MOTORB2, LOW );
  analogWrite( MOTORBPWM, DUTY );
  digitalWrite( STANDBYPIN, HIGH );
  
  delay( del );
  
  analogWrite( MOTORBPWM, 0 );
  digitalWrite( STANDBYPIN, LOW );
}

void moveBRight( int del ) {
  digitalWrite( MOTORB1, LOW );
  digitalWrite( MOTORB2, HIGH );
  analogWrite( MOTORBPWM, DUTY );
  digitalWrite( STANDBYPIN, HIGH );
  
  delay( del );
  
  analogWrite( MOTORBPWM, 0 );
  digitalWrite( STANDBYPIN, LOW );
}

int readPotA() {
  int val = analogRead( SLIDEPOTA );
  Serial.println( val );
  return val;
}

int readPotB() {
  int val = analogRead( SLIDEPOTB );
  Serial.println( val );
  return val;
}

void readDist() {
  Serial.println( analogRead( DISTPIN ) );
}
