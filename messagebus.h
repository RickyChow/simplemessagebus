#ifndef _MESSAGEBUS_H_
#define _MESSAGEBUS_H_

#include <string>
#include <map>
#include <set>
#include <typeinfo>

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
  virtual void ReceivedEvent(const eventdata_t& event) = 0;
};


class EventMessageBus
{
private:
  template<typename data_t>
  static std::string GetEventId()
  {
    return typeid(data_t).name();
  }
  typedef std::set<EventSubscriberGeneric*> subscribercol_t;
  std::map<std::string, subscribercol_t> m_subscribers;

public:
  template<typename data_t>
  void Publish(const data_t& data)
  {
    subscribercol_t subs = m_subscribers[GetEventId<data_t>()];
    subscribercol_t::iterator sub = subs.begin();

    for (; sub != subs.end(); ++sub) {

      EventSubscriber<data_t>* subTyped = 
        static_cast<EventSubscriber<data_t>* >(*sub);
      const data_t* dataTyped = static_cast<const data_t*>(&data);

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
