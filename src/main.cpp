#include "mbed.h"
#include <iostream>
#include <cmath>
BufferedSerial pc(USBTX, USBRX, 115200); // 通信

int16_t pwm[4] = {0, 0, 0, 0}; // pwm配列

int main()
{
  // CAN通信
  CAN can(PA_11, PA_12, (int)1e6); // canを出力するピンを指定
  CANMessage msg;
  
  float X = 0;
  float Y = 0;
  char buf[64];
  while (1)
  {    
    // もしpcから通信が来たら
    if (pc.readable())
    {
      int n = pc.read(buf, sizeof(buf) - 1); // 末端のためのサイズ空け
      if (n > 0) 
      {
        buf[n] = '\0'; // ヌル文字(末端文字)
        if (buf[n - 1] == '\n' || buf[n - 1] == '\r')
        {
          buf[n - 1] = '\0';
          int number = atoi(buf); // 受信した文字列を整数に変換
        }
        float x_in = 0, y_in = 0;           // 受信した数値から
        sscanf(buf, "%f %f", &x_in, &y_in); // 受信した文字列を2つの浮動小数点数に変換
        X = x_in;
        Y = y_in;
      }
    }
    ThisThread::sleep_for(chrono::milliseconds(10));

    /*オムニホイール*/

    float rad = atan2(Y, X);
    float value = hypot(X, Y);

    // オムニホイールの出力
    pwm[0] = sin((rad - M_PI / 4) * value);
    pwm[1] = sin((rad - 3 * M_PI / 4) * value);
    pwm[2] = sin((rad + 3 * M_PI / 4) * value);
    pwm[3] = sin((rad + M_PI / 4) * value);

    // CAN通信
    CANMessage msg(2, (const uint8_t *)pwm, 8); // 特に理由がない限りwhile直下
    can.write(msg);                             // 特に理由がない限りwhile直下
  }
}

