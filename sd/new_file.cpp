/*
	For generating a new file whenever a new logging session starts
*/
#include<SPI.h>
#include<SD.h>

String getFileName()
{
  File counter;
  counter = SD.open("counter.txt", FILE_WRITE);
  counter.seek(0);
  uint32_t num = 0;
  if(counter.size()>0) num = counter.read();
  counter.seek(0);
  counter.write(num+1);
  counter.close();

  String str = String(num);
  return "GPS"+str+".txt";
}
void setup() {
  Serial.begin(115200);
  while(!Serial);
  if(!SD.begin(4))
    return;
  Serial.println("Card ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(getFileName());
}