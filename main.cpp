#include <stdio.h>

#include "messagebus2.h"


EventMessageBus g_messageBus;


class TestEventData
  : public EventData<TestEventData>
{
public:
  int test;
  int test2;
};


class TestEventSubscriber
  : public TestEventData::Subscriber
{
public:
  TestEventSubscriber()
  {
    g_messageBus.Subscribe(this);
  }

  void ReceivedEvent(TestEventData& data)
  {
    printf("Received event!\n\r");
  }
};



int main()
{
  TestEventSubscriber testSubscriber;

  TestEventData testEventData;
  testEventData.test = 100;
  testEventData.test2 = 200;

  g_messageBus.Publish(testEventData);
  return 0;
}
