#include <PS4Controller.h> 
#include <stdint.h>

void setup() 
{
  Serial.begin(115200); //速度
  PS4.begin(); 
  Serial.println("Ready."); 
}

void loop() 
{
  if (PS4.isConnected()) 
  { 
    if (PS4.LStickX()) 
    {
      int8_t coord1 = PS4.LStickX();
      String str1 = String(static_cast<int>(coord1));
      Serial.println(str1); //strに改行を付け加え、出力している
    }

    if (PS4.LStickY()) 
    {
    int8_t coord2 = PS4.LStickY();
    String str2 = String(static_cast<int>(coord2)+256);
    Serial.println(str2);
    }

    delay(1000); //1秒停止
}
