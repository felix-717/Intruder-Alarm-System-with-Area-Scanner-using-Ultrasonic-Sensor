// LCD module connections
// Connections are in PORTD
sbit LCD_RS at RE0_bit;
sbit LCD_EN at RE1_bit;
sbit LCD_D0 at RD0_bit;
sbit LCD_D1 at RD1_bit;
sbit LCD_D2 at RD2_bit;
sbit LCD_D3 at RD3_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISE0_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D0_Direction at TRISD0_bit;
sbit LCD_D1_Direction at TRISD1_bit;
sbit LCD_D2_Direction at TRISD2_bit;
sbit LCD_D3_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
// End LCD module connections

//servo motor library based on the web: https://deepbluembedded.com/servo-motor-control-with-pic-microcontroller-16bit-pwm-pt3/
void main() {
   int i;
   float angle, dist;
   char strDist[4], strAngle[4];
   ADCON1 = 0x00;
   TRISA = 0b00000001; // set PORTA.F1 to be an input signal
   PORTA = 0b00000000;
   TRISC = 0;
   PORTC = 0;
   TRISD = 0; // set LCD to be an output signal
   PORTD = 0;
   
   Lcd_Init();
   ADC_Init();
   Servo_Init();
   
   do{
      Lcd_Out(1, 1, "Scanning");
      Lcd_Out(2, 1, "Object");
      delay_ms(3000);
      
      PWM1_Init(5000);
      PWM1_Start();
      PWM1_Set_Duty(127); // 50% duty cycle
      
      dist = ADC_Read(0);
      PORTD = dist;
      for (i=0; i < 180; i++){
         // condition: object is near the infrared sensor
         if(dist > 300){
            // change from 50% duty cycle to no duty cycle
            PWM1_Set_Duty(0);
            
            // write distance value to EEPROM
            I2C1_Start(); // issue I2C start signal
            I2C1_Wr(dist); // send byte via I2C (device address + W)
            I2C1_Stop(); // issue I2C stop signal

            // print values to the LCD
            angle = i;
            FloatToStr(dist, strDist);
            FloatToStr(angle, strAngle);
            Lcd_Out(1, 1, "Dist: ");
            Lcd_Out(1, 6, strDist);
            Lcd_Out(2, 1, "Angle: ");
            Lcd_Out(1, 7, strAngle);

            // enable the sound of the buzzer
            PORTC.F5 = 1;//set buzzer to on
            delay_ms(2000);
            PORTC.F5 = 0;//set buzzer to off
            
            // change back from 0% to 50% duty cycle
            PWM1_Set_Duty(127);
         }
         else {
            Servo_MoveTo(PORTC.F1, i);
            delay_ms(5);
         }
      }
      delay_ms(2000);
      for (i=180; i < 0; i--){
         // condition: object is near the infrared sensor
         if(dist > 300){
            // change from 50% duty cycle to no duty cycle
            PWM1_Set_Duty(0);
            
            // write distance value to EEPROM
            I2C1_Start(); // issue I2C start signal
            I2C1_Wr(dist); // send byte via I2C (device address + W)
            I2C1_Stop(); // issue I2C stop signal
         
            // print values to the LCD
            angle = i;
            FloatToStr(dist, strDist);
            FloatToStr(angle, strAngle);
            Lcd_Out(1,1, "Dist: ");
            Lcd_Out(1, 6, strDist);
            Lcd_Out(2,1, "Angle: ");
            Lcd_Out(1, 7, strAngle);

            // enable the sound of the buzzer
            PORTC.F5 = 1;//set buzzer to on
            delay_ms(2000);
            PORTC.F5 = 0;//set buzzer to off
            
            // change back from 0% to 50% duty cycle
            PWM1_Set_Duty(127);
         }
         else {
            Servo_MoveTo(PORTC.F1, i);
            delay_ms(5);
         }
      }
      delay_ms(2000);
   } while(1);
}