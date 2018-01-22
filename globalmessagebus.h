#ifndef GLOBAL_MESSAGE_BUS_H_
#define GLOBAL_MESSAGE_BUS_H_

#include "messagebus.h"

extern EventMessageBus g_messageBus;

template<typename data_t>
class GlobalEventSubscriber
  : public EventSubscriber<data_t>
{
public:
  GlobalEventSubscriber()
  {
    g_messageBus.Subscribe<data_t>(this);
  }

  ~GlobalEventSubscriber()
  {
    g_messageBus.Unsubscribe<data_t>(this);
  }
};

#endif
