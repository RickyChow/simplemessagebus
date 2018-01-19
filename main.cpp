#include <stdio.h>

#include "messagebus.h"
#include <set>

EventMessageBus g_messageBus;

struct SignalData
{
  int id;
  std::string data;
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
      printf("Received event data: %s!\r\n", signalData.data.c_str());
    }
  }

private:
  int m_id;
};

class EmptyClass
{
  
};

int main()
{
  SignalDataConsumer dataConsumer(1);

  SignalData signalData1;
  signalData1.id = 1;
  signalData1.data = "Data for signal 1";
  
  SignalData signalData2;
  signalData2.id = 2;
  signalData2.data = "Data for signal 2";

  EmptyClass test;

  g_messageBus.Publish(signalData1);
  g_messageBus.Publish(signalData2);
  g_messageBus.Publish(test);
  return 0;
}
