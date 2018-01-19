#include <stdio.h>

#include "messagebus2.h"
#include <set>

EventMessageBus g_messageBus;

class TestEventData
  : public EventData
{
public:
  int test;
  int test2;
};


class TestEventSubscriber
  : public EventSubscriber<TestEventData>
{
public:
  TestEventSubscriber()
  {
    g_messageBus.Subscribe(this);
  }

  void ReceivedEvent(TestEventData& data)
  {
    printf("Received event!\r\n");
  }
};


class BaconData
  : public EventData
{
public:
  std::string baconName;
  int crispiness;
  std::set<int> baconIds;
};

class BaconSubscriber
  : public EventSubscriber<BaconData>
{
public:
  BaconSubscriber()
  {
    g_messageBus.Subscribe(this);
  }

  void ReceivedEvent(BaconData& data)
  {
    printf("Received bacon event! name: %s, crispiness: %d \r\n",
        data.baconName.c_str(),
        data.crispiness);
  }
};

int main()
{
  TestEventSubscriber testSubscriber;
  BaconSubscriber baconSubsubscriber;

  TestEventData testEventData;
  testEventData.test = 100;
  testEventData.test2 = 200;

  BaconData bacon;
  bacon.baconName = "porky";
  bacon.crispiness = 23;
  bacon.baconIds.insert(123);

  g_messageBus.Publish(testEventData);
  g_messageBus.Publish(bacon);
  return 0;
}
