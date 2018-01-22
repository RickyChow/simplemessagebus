#include <stdio.h>

#include "globalmessagebus.h"
#include "eventmessagedef.h"

class SignalDataConsumer
  : public GlobalEventSubscriber<SignalData>
{
public:
  SignalDataConsumer(int id)
    : m_id(id)
  {
  }

  void ReceivedEvent(const SignalData& signalData)
  {
    if (signalData.id == m_id) {
      printf("SignalDataConsumer Received event data: %s!\r\n", signalData.data.c_str());
    }
  }

private:
  int m_id;
};

class AllConsumer
  : public GlobalEventSubscriber<SignalData>
  , public GlobalEventSubscriber<SignData>
  , public GlobalEventSubscriber<int>
{
public:
  void ReceivedEvent(const SignalData& signalData)
  {
    printf("AllConsumer received signalData %s!\r\n", signalData.data.c_str());
  }

  void ReceivedEvent(const SignData& signData)
  {
    printf("AllConsumer received signData magic number: %d!\r\n", signData.magicNumber);
  }

  void ReceivedEvent(const int& intData)
  {
    printf("AllConsumer received int data %d!\r\n", intData);
  }
};

int main()
{
  SignalDataConsumer dataConsumer(1);
  AllConsumer allConsumer;

  SignalData signalData1;
  signalData1.id = 1;
  signalData1.data = "Data for signal 1";
  
  SignalData signalData2;
  signalData2.id = 2;
  signalData2.data = "Data for signal 2";

  SignData signData1;
  signData1.id = 3;
  signData1.magicNumber = 23;

  g_messageBus.Publish(signalData1);
  g_messageBus.Publish(signalData2);
  g_messageBus.Publish(signData1);
  g_messageBus.Publish(123);
  return 0;
}
