const int MOVEALEFT = 97;
const int MOVEARIGHT = 98;
const int MOVEBLEFT = 99;
const int MOVEBRIGHT = 100;
const int READPOTA = 101;
const int READPOTB = 102;
const int READDIST = 103;
const int SCANCOM = 104;

const int MOTORA1 = 7;
const int MOTORA2 = 6;
const int MOTORAPWM = 5;
const int SLIDEPOTA = A0;
const int STANDBYPIN = 8;
const int MOTORB1 = 10;
const int MOTORB2 = 9;
const int MOTORBPWM = 11;
const int SLIDEPOTB = A1;
const int DISTPIN = A5;
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

void pushALeft() {
  while( readPotA() > 64 ) {
    moveALeft( 50 );
    delay( 25 );
  }
}

void pushBLeft() {
  while( readPotB() > 64 ) {
    moveBLeft( 50 );
    delay( 25 );
  }
}

void handleAction( int act ) {
  switch( act ) {
    case MOVEALEFT:
    while( readPotA() > 64 ) {
      moveALeft( 50 );
      delay( 50 );
    }
    break;
    
    case MOVEARIGHT:
    while( readPotA() < 960 ) {
      moveARight( 50 );
      delay( 50 );
    }
    break;
    
    case MOVEBLEFT:
    while( readPotB() > 64 ) {
      moveBLeft( 50 );
      delay( 50 );
    }
    break;
    
    case MOVEBRIGHT:
    while( readPotB() < 960 ) {
      moveBRight( 50 );
      delay( 50 );
    }
    break;
    
    case READPOTA:
    Serial.println( readPotA() );
    break;
    
    case READPOTB:
    readPotB();
    break;
    
    case READDIST:
    Serial.println( readDist() );
    break;
    
    case SCANCOM:
    Serial.println( "BEGIN SCAN" );
    Serial.println( "x\ty\tz");
    while( readPotB() < 960 ) {
      while( readPotA() < 960 ) {
        moveARight( 50 );
        delay( 150 );
        Serial.print( readPotA() );
        Serial.print( "\t" );
        Serial.print( readPotB() );
        Serial.print( "\t" );
        Serial.print( readDist() );
        Serial.println();
        delay( 150 );
      }
      moveBRight( 50 );
      delay( 150 );
      Serial.print( readPotA() );
      Serial.print( "\t" );
      Serial.print( readPotB() );
      Serial.print( "\t" );
      Serial.print( readDist() );
      Serial.println();
      delay( 150 );
      
      while( readPotA() > 64 ) {
        moveALeft( 50 );
        delay( 150 );
        Serial.print( readPotA() );
        Serial.print( "\t" );
        Serial.print( readPotB() );
        Serial.print( "\t" );
        Serial.print( readDist() );
        Serial.println();
        delay( 150 );
      }
      moveBRight( 50 );
      delay( 150 );
      Serial.print( readPotA() );
      Serial.print( "\t" );
      Serial.print( readPotB() );
      Serial.print( "\t" );
      Serial.print( readDist() );
      Serial.println();
      delay( 150 );
    }
    Serial.println( "END" );
    pushALeft
    pushBLeft();
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
  return analogRead( SLIDEPOTA );
}

int readPotB() {
  return analogRead( SLIDEPOTB );
}

int readDist() {
  return analogRead( DISTPIN );
}
