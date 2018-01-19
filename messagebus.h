#ifndef _MESSAGEBUS_H_
#define _MESSAGEBUS_H_

#include <string>
#include <map>
#include <set>
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
  typedef std::set<EventSubscriberGeneric*> subscribercol_t;
  std::map<std::string, subscribercol_t> m_subscribers;

public:
  template<typename data_t>
  void Publish(data_t& data)
  {
    subscribercol_t subs = m_subscribers[GetEventId<data_t>()];

    subscribercol_t::iterator sub = subs.begin();

    for (; sub != subs.end(); ++sub) {

      EventSubscriber<data_t>* subTyped = 
        dynamic_cast<EventSubscriber<data_t>* >(*sub);
      data_t* dataTyped = dynamic_cast<data_t*>(&data);

      if (dataTyped && subTyped) {
        subTyped->ReceivedEvent(*dataTyped);
      }
    }
  }

  template<typename data_t>
  void Subscribe(EventSubscriber<data_t>* subscriber)
  {
    m_subscribers[GetEventId<data_t>()].insert(subscriber); 
  }

  template<typename data_t>
  void Unsubscribe(EventSubscriber<data_t>* subscriber)
  {
    m_subscribers[GetEventId<data_t>()].erase(subscriber); 
  }

};


#endif
