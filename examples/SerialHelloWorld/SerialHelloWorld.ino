
#include "SerialLink.h"

unsigned char TxBuf[10];
unsigned char RxBuf[128];
unsigned int in = 0;
volatile unsigned int RxLen = 0;
volatile bool RxFlag = false;
elapsedMillis t;

void receive_handler(unsigned int len) {
  Serial1Link.read(RxBuf,len);
  RxLen = len;
  RxFlag = true;
}

void setup() 
{
  Serial.begin(115200);
  while (!Serial) {}
  Serial1Link.begin(6000000);
  Serial1Link.onReceive(receive_handler);
  t = 0;
}

void loop()
{
  if (RxFlag) {
    RxFlag = false;
    for (unsigned int i = 0; i < RxLen; i++) {
      Serial.println(RxBuf[i]);
    }
  }
  if (t > 1000) {
    t -= 1000;
    writeMsg();
  }
}

void writeMsg()
{
  for (unsigned int i = 0; i < sizeof(TxBuf); i++, in++) {
    TxBuf[i] = in;
  }
  Serial1Link.beginTransmission();
  Serial1Link.write(TxBuf,sizeof(TxBuf));
  Serial1Link.endTransmission(1000);
}
