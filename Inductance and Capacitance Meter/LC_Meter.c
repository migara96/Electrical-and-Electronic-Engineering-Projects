#define SWT1 PORTD.F0

sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D7 at RB0_bit;
sbit LCD_D6 at RB1_bit;
sbit LCD_D5 at RB2_bit;
sbit LCD_D4 at RB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D7_Direction at TRISB0_bit;
sbit LCD_D6_Direction at TRISB1_bit;
sbit LCD_D5_Direction at TRISB2_bit;
sbit LCD_D4_Direction at TRISB3_bit;

float iref = 0.0001;
float cref = 0.00000001;
float fref = 214000;

float calc_cap(unsigned long int f);
float calc_ind(unsigned long int f);
char cap_result[11],ind_result[11];
unsigned long cap_value,ind_value;

void main() {
unsigned long fl=0,fh=0;
unsigned long f=0;

float cap_value,ind_value;

char txt[5],txt1[5],*res;
lcd_init();
lcd_cmd(_LCD_CLEAR);
lcd_cmd(_LCD_CURSOR_OFF);

lcd_cmd(_LCD_CLEAR);
TRISC= 0b11111111;
PORTC= 0b00000000;
TRISB=0;
TRISD = 0b11111111;
PORTD = 0b00000000;
TMR1L=0;
TMR1H=0;

lcd_out(1,1,"WORKING..");
delay_ms(100);
lcd_out(1,1,"WORKING….");
delay_ms(1000);

T1CON= 0B00000011;
delay_ms(100);
T1CON= 0B00000010;
fl = TMR1L;
fh = TMR1H * 256;
f= ((fl+fh)*10);

    if(SWT1==1)
          {
            cap_value = calc_cap(f+10);
            FloatToStr(cap_value, cap_result);
            LCD_CMD(_LCD_CLEAR);
            LCD_OUT(1,1,"Capacitance:");
            LCD_OUT(2,1,cap_result);
            LCD_OUT(2,14,"F");
          }
          else
          {
            ind_value = calc_ind(f+10);
            FloatToStr(ind_value, ind_result);
            LCD_CMD(_LCD_CLEAR);
            LCD_OUT(1,1,"Inductance:");
            LCD_OUT(2,1,ind_result);
            LCD_OUT(2,14,"H");
          }
}

 float calc_cap(unsigned long int f)
  {
        float result = 0;
        result = ((pow(fref,2)/pow(f,2))-1)*cref;
        return result;
  }
float calc_ind(unsigned long int f)
  {
        float result = 0;
        result = ((pow(fref,2)/pow(f,2))-1)*iref;
        return result;
  }

