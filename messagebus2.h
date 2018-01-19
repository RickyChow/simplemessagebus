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
  typedef EventSubscriber<super_t> Subscriber;
};


class EventSubscriberGeneric
{
private:
  template<typename data_t>
  void ReceivedEventInner(EventData<data_t>& data)
  {
    EventData<data_t>::Subscriber* subTyped = dynamic_cast<EventData<data_t>::Subscriber*>(this);
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
  static int GetEventId()
  {
    return 0;
  }

public:

  template<typename data_t>
  void Publish(EventData<data_t>& data)
  {
    EventSubscriberGeneric* sub = m_subscribers[GetEventId<data_t>()];
    sub->ReceivedEventInner(data);
  }

  template<typename sub_t>
  void Subscribe(sub_t* subscriber)
  {
    m_subscribers[GetEventId<sub_t>()] = subscriber; 
  }


private:
  std::map<int, EventSubscriberGeneric*> m_subscribers;
};


#endif
