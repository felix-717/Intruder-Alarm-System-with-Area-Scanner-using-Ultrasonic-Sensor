 void write_EPPROM(unsigned int dat)
 void soundBuzzer()
 
         int i=0;
         
    //ilagay sa global/labas
    PORTC.F5 = 0;//set buzzer to off
     TRISC.F5=0;//output f5
     PORTC.F1 = 0;//pwm
     TRISC.F1=0;//
     Pwm1_Init(5000);
     Pwm1_start();
     Pwm1_Set_Duty(128);//50% not too slow not too fast
     I2C1_Init(80000); // initialize I2C communication
     
     


      //while loop for rotating servo
      //walang lib for servo sa mikroC so
      //based dito: https://deepbluembedded.com/servo-motor-control-with-pic-microcontroller-16bit-pwm-pt3/
      Servo_Init();
  while(1)
  {
     //rotate 180
    for(int i=0; i<180; i++)
    {
      Servo_MoveTo(PORTC.F1, i);
      delay_ms(5);
    }
    delay_ms(500);
    for(int i=180; i>0; i--)
    {
      Servo_MoveTo(PORTC.F1, i);
      delay_ms(5);
    }
    delay_ms(500);
  }

void write_EPPROM(unsigned int dat) {


I2C1_Start(); // issue I2C start signal
I2C1_Wr(dat); // send byte via I2C (device address + W)
I2C1_Stop(); // issue I2C stop signal
}

//function for turining on buzzer
void soundBuzzer(){
          PORTC.F5 = 1;//set buzzer to on
          delay_ms(2000);
           PORTC.F5 = 0;//set buzzer to off
}






}