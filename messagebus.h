#ifndef _MESSAGEBUS_H_
#define _MESSAGEBUS_H_

#include <string>
#include <map>
//////////////////////////////////////////////////////////////////

//This is used so that we have a common form of storing subscribers
class EventSubscriberGeneric
{
public:
  virtual ~EventSubscriberGeneric() {}
};

//Necessary for type safety when downcasting 
template<typename eventdata_t>
class EventSubscriber
  : public EventSubscriberGeneric
{
public:
  virtual void ReceivedEvent(eventdata_t& event) = 0;
};


class EventMessageBus
{
private:
  template<typename data_t>
  static std::string GetEventId()
  {
    std::string eventId = typeid(data_t).name();
    return eventId;
  }

public:
  template<typename data_t>
  void Publish(data_t& data)
  {
    EventSubscriberGeneric* sub = m_subscribers[GetEventId<data_t>()];

    EventSubscriber<data_t>* subTyped = dynamic_cast<EventSubscriber<data_t>* >(sub);
    data_t* dataTyped = dynamic_cast<data_t*>(&data);
    if (!dataTyped || !subTyped) return;
    subTyped->ReceivedEvent(*dataTyped);
  }

  template<typename data_t>
  void Subscribe(EventSubscriber<data_t>* subscriber)
  {
    m_subscribers[GetEventId<data_t>()] = subscriber; 
  }

private:
  std::map<std::string, EventSubscriberGeneric*> m_subscribers;
};


#endif
