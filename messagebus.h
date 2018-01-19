#ifndef _MESSAGEBUS_H_
#define _MESSAGEBUS_H_

#include <string>
#include <set>

//Maintain newline after this just in case somebody forgets to end def file with newline
#include "eventmessagedef.h"
//-----Don't delete this newline below

//-----Don't delete this newline above

#define EVENT_MESSAGE_DEF EVENT_MESSAGE_PARAM_ROW_EXPANDER

namespace tsd
{

//Event data struct definitions
#define EVENT_MESSAGE_PARAM_ROW_EXPANDER(eventName, params) \
struct EventData_##eventName { \
  params\
}; \
\
class EventSubscriber_##eventName \
{\
public: \
  virtual void Received_##eventName(const EventData_##eventName& eventName) = 0; \
};

EVENT_MESSAGE_PARAM_DATA
#undef EVENT_MESSAGE_PARAM_ROW_EXPANDER


class MessageBus
{
  
#define EVENT_MESSAGE_PARAM_ROW_EXPANDER(eventName, ...) \
private:\
  std::set< EventSubscriber_##eventName* > m_subscribers_##eventName; \
public: \
  void Publish(const EventData_##eventName& data) { \
    std::set<EventSubscriber_##eventName*>::iterator itr; \
    itr = m_subscribers_##eventName.begin(); \
    for (; itr != m_subscribers_##eventName.end(); ++itr) { \
      (*itr)->Received_##eventName(data); \
    } \
  } \
  \
  void Subscribe(EventSubscriber_##eventName* subscriber) \
  { \
    m_subscribers_##eventName.insert(subscriber); \
  } \
\
  void Unsubscribe(EventSubscriber_##eventName* subscriber) \
  { \
    m_subscribers_##eventName.erase(subscriber); \
  } \

EVENT_MESSAGE_PARAM_DATA
#undef EVENT_MESSAGE_PARAM_ROW_EXPANDER
};

class MessageBusServerConnection
{
public:
class EventHandler
{
  virtual void ConnectionEstablished() = 0;
};
  virtual void Open() = 0;
  virtual void Close() = 0;
  
};


}

#endif //_MESSAGEBUS_H_
