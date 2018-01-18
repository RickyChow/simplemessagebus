#include <stdio.h>

#include "messagebus.h"

using namespace tsd;

MessageBus g_messageBus;

class TestSubscriber
  : public EventSubscriber_TestEvent2
  , public EventSubscriber_TestEvent
  , public EventSubscriber_Lol
{
public:
  TestSubscriber()
  {
    g_messageBus.Subscribe(static_cast<EventSubscriber_TestEvent2*>(this));
    g_messageBus.Subscribe(static_cast<EventSubscriber_TestEvent*>(this));
    g_messageBus.Subscribe(static_cast<EventSubscriber_Lol*>(this));
  }

  ~TestSubscriber()
  {
    g_messageBus.Unsubscribe(static_cast<EventSubscriber_TestEvent2*>(this));
    g_messageBus.Unsubscribe(static_cast<EventSubscriber_TestEvent*>(this));
    g_messageBus.Unsubscribe(static_cast<EventSubscriber_Lol*>(this));
  }
  
  void Received_TestEvent2(const EventData_TestEvent2& data)
  {
    printf("received_testEvent2 data: %s\r\n", data.test.c_str());
  }

  void Received_TestEvent(const EventData_TestEvent& data)
  {
    printf("received_testEvent data: %s\r\n", data.test.c_str());
  }
  void Received_Lol(const EventData_Lol& data)
  {
    printf("received_testEvent eggs: %d\r\n", data.eggs);
  }
};


int main()
{
  TestSubscriber testSubscriber;

  EventData_TestEvent2 testEventData2;
  testEventData2.test = "hello this is test data 2";

  EventData_TestEvent testEventData;
  testEventData.test = "hello this is test data";

  EventData_Lol lolData;
  lolData.eggs = 123;


  g_messageBus.Publish(testEventData2);
  g_messageBus.Publish(testEventData);
  g_messageBus.Publish(lolData);
  return 0;
}
