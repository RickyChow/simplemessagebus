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
  typedef EventSubscriber<super_t> Subscriber;

  std::string GetEventId() const {
    return typeid(Subscriber).name();
  }
private:
  friend class EventMessageBus;
};


class EventSubscriberGeneric
{
public:
  virtual ~EventSubscriberGeneric() {}
private:
  template<typename data_t>
  void ReceivedEventInner(EventData<data_t>& data)
  {
    typename EventData<data_t>::Subscriber* subTyped =
        dynamic_cast<typename EventData<data_t>::Subscriber*>(this);
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
    printf("Publish data_t is  %s\r\n", data.GetEventId().c_str());
    EventSubscriberGeneric* sub = 
      m_subscribers[GetEventId<typename data_t::Subscriber>()];
    sub->ReceivedEventInner(data);
  }

  template<typename sub_t>
  void Subscribe(sub_t* subscriber)
  {
    printf("EventMessageBus::Subscribe BEFORE m_subscribes.size: %ld\r\n", m_subscribers.size());
    m_subscribers[GetEventId<sub_t>()] = subscriber; 
    printf("EventMessageBus::Subscribe AFTER m_subscribes.size: %ld\r\n", m_subscribers.size());
  }

private:
  std::map<std::string, EventSubscriberGeneric*> m_subscribers;
};


#endif
