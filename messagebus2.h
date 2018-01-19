#ifndef _MESSAGEBUS_H_
#define _MESSAGEBUS_H_

#include <string>
#include <map>
//////////////////////////////////////////////////////////////////

template<typename eventdata_t>
class EventSubscriber;

template<typename super_t>
class EventData
{
public:
  virtual ~EventData() {}
};


class EventSubscriberGeneric
{
public:
  virtual ~EventSubscriberGeneric() {}
private:
  template<typename data_t>
  void ReceivedEventInner(EventData<data_t>& data)
  {
    EventSubscriber<data_t>* subTyped = dynamic_cast<EventSubscriber<data_t>* >(this);
    data_t* dataTyped = dynamic_cast<data_t*>(&data);
    if (!dataTyped || !subTyped) return;
    subTyped->ReceivedEvent(*dataTyped);
  }

  friend class EventMessageBus;
};

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
    printf("GetEventId %s\r\n", eventId.c_str());
    return eventId;
  }

public:
  template<typename data_t>
  void Publish(EventData<data_t>& data)
  {
    EventSubscriberGeneric* sub = m_subscribers[GetEventId<data_t>()];
    sub->ReceivedEventInner(data);
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
