 /*
 端口直接驱动4位共阴数码管，一般情况无需外接限流电阻，
 因为端口的输出电流有限，一般不超过20mA，长期使用建议加限流电阻。

 */
int ledCount=8;
int segCount=4;
unsigned int num;//定义一个数据
unsigned  long lastTime=0;
unsigned int i=0;

const unsigned char dofly_DuanMa[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

int ledPins[] = { 
  2,3,4,5,6,7,8,9 };   // a,b,c,d,e,f,g,dp引脚
int segPins[] = {
 10,11,12,13 };  // left->right
 
unsigned char displayTemp[4];//显示缓冲区

void setup() {
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT); }
  for (int thisSeg = 0; thisSeg < segCount; thisSeg++) {
    pinMode(segPins[thisSeg], OUTPUT); 
  }
}

void deal(unsigned char value){
 for(int i=0;i<8;i++)
   digitalWrite(ledPins[i],bitRead(value,i));//使用了bitWrite函数，非常简单
}

void loop() 
{
    if (millis() - lastTime >= 1000) {
    lastTime = millis();
    num++;
  }
  displayTemp[0]=dofly_DuanMa[num/1000];       //动态显示
  displayTemp[1]=dofly_DuanMa[(num%1000)/100];
  displayTemp[2]=dofly_DuanMa[((num%1000)%100)/10];
  displayTemp[3]=dofly_DuanMa[((num%1000)%100)%10];  
  
  deal(0);// 清除“鬼影” turn off leds
  for(int a=0;a<4;a++) //循环写位码，任何时刻只有1位数码管选通，之前全部关闭，然后再选通需要的那位数码管
    {digitalWrite(segPins[a],1);}
  digitalWrite(segPins[i],0);
  deal(displayTemp[i]);//读取对应的段码值
  i++;
  if(i==4) //4位结束后重新循环
    {i=0;}
}
