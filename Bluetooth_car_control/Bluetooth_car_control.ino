// Author: Jose Marco de la Rosa
// Description: Small program for basic Brozabot_mk1 bluetooth control

// Not using the sw serial because it interferes with the servo library
//#include <SoftwareSerial.h>
#include <Servo.h> 

Servo speed_servo;
Servo steer_servo;
// If using software serial here you attach RX and TX pins for the Bluetooth module.
// SoftwareSerial BT(8,9); // Tx:9 Rx:8 8 RX (connect to TX of HC-06), 9 TX (connect to RX of HC-06).

// When using the hw serial (default), connect the bluetooth module to pins 0,1 (Crossed TX to RX, RX to TX)

float new_speed;
float new_steer;
float prev_steer;
//String str;
char input_buffer[50];
int index = 0;
boolean line_read;
 
#define ESC_center 95
#define ESC_backward_threshold 100
#define ESC_toggle_delay 20
 
void setAndSend( int deg, int delay_val=0 ){
  //Serial.println( "Sent:"+String(deg) );
  speed_servo.write( deg );
  delay( delay_val );
}  
 
void setESC_by_position( int esc_position ){
  static int current_position = ESC_center;
  if ( current_position == esc_position ){
    //Serial.println( "No speed change!" );
    return;
  }
  //Serial.println( "Setting speed:"+String(esc_position) );
  // Position logic
  // When changing from forward to backwards, need to send two positions
  if ( current_position < 98 && esc_position >= 98 ){
    //Serial.println( "Changing from forward to backwards!" );
    setAndSend( ESC_center, ESC_toggle_delay );
    setAndSend( ESC_backward_threshold, ESC_toggle_delay );
    setAndSend( ESC_center, ESC_toggle_delay );
  }
  current_position = esc_position;
  setAndSend( esc_position );
} 

void setESC_speed( float esc_speed ){
  int pos = map( esc_speed*100, 100, -100, 15, 175 );
  //Serial.println( "Mapped position: "+String(pos) );
  setESC_by_position( pos );
}

void setup()
{
  //BT.begin(9600); // Parameter is the serial speed for the bluetooth (when using sw serial!)
  Serial.begin(9600); // Open hw serial connection with the bluetooth module and stablish speed
  delay(10);
  index = 0;
  Serial.println( "Attaching ESC" );
  speed_servo.attach(11);
  Serial.println( "Attached" );
  delay(10);
  setESC_speed( 0 );
  steer_servo.attach(10);
  prev_steer = 90;
  steer_servo.write(prev_steer);
}

void loop()
{
  //while(BT.available())
  while(Serial.available())
  { 
    // Input messages comming from the serial connection consist in
      // "<x>,<y>\n" strings where:
      //    <x> is the steering with a value from 0 to 100 with 50 meaning "straight", x<50 = left, x>50 = right
      //    <y> is speed with a value from 0 to 100 with 50 meaning "stopped", y>50 = forward, y<50 = backwards
      
    //input_buffer[index] = BT.read();
    input_buffer[index] = Serial.read();
     if (input_buffer[index] == '\n') {
       input_buffer[index] = '\0';
       //Serial.print( "Read:" );
       
       index = 0;
       
       char* separator = strchr(input_buffer, ',');
       *separator = 0;
       new_speed = atoi( input_buffer );
       new_steer = atoi( ++separator );
       
       //Serial.print( "Speed: " );
       //Serial.print( new_speed );
       //Serial.print( " / Steer:" );
       //Serial.println( new_steer );
       
       setESC_speed( (new_speed-50)/50. );
       new_steer = 1.8 * (100-new_steer); // Invert and scale to degrees
       if ( abs( new_steer - prev_steer ) > 1 ){
         prev_steer = new_steer;
         steer_servo.write( prev_steer );
       }
     }else{
       index++;
     }
  }
  delay(5);
 
}
