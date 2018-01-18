#include <stdio.h>

#include "messagebus.h"

using namespace tsd;

MessageBus g_messageBus;

class TestSubscriber
  : public EventSubscriber_SignStatus
{
public:
  TestSubscriber()
  {
    g_messageBus.Subscribe(static_cast<EventSubscriber_SignStatus*>(this));
  }

  ~TestSubscriber()
  {
    g_messageBus.Unsubscribe(static_cast<EventSubscriber_SignStatus*>(this));
  }
  
  void Received_SignStatus(const EventData_SignStatus& data)
  {
    printf("received message data: %s\r\n", data.signName.c_str());
  }
};


int main()
{
  TestSubscriber testSubscriber;

  EventData_TestEvent testEventData;
  testEventData.test = "hello this is test data";

  EventData_SignStatus signStatus;
  signStatus.signName = "this is my sign name";

  g_messageBus.Publish(testEventData);
  g_messageBus.Publish(signStatus);
  return 0;
}
