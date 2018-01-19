#include <stdio.h>

#include "messagebus.h"

EventMessageBus g_messageBus;

struct SignalData
{
  int id;
  std::string data;
};

struct SignData
{
  int id;
  int magicNumber;
};



class SignalDataConsumer
  : public EventSubscriber<SignalData>
{
public:
  SignalDataConsumer(int id)
    : m_id(id)
  {
    g_messageBus.Subscribe(this);
  }

  void ReceivedEvent(SignalData& signalData)
  {
    if (signalData.id == m_id) {
      printf("SignalDataConsumer Received event data: %s!\r\n", signalData.data.c_str());
    }
  }

private:
  int m_id;
};

class AllConsumer
  : public EventSubscriber<SignalData>
  , public EventSubscriber<SignData>
{
public:
  AllConsumer()
  {
    g_messageBus.Subscribe<SignalData>(this);
    g_messageBus.Subscribe<SignData>(this);
  }
  void ReceivedEvent(SignalData& signalData)
  {
    printf("AllConsumer received signalData %s!\r\n", signalData.data.c_str());
  }

  void ReceivedEvent(SignData& signData)
  {
    printf("AllConsumer received signData magic number: %d!\r\n", signData.magicNumber);
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
  return 0;
}
