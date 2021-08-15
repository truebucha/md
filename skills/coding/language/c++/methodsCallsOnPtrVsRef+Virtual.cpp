struct Object
{
  virtual std::string description() const {  };
};

struct Event : public Object
{
  
};

struct MyEvent : public Event
{
  std::string description() const override { };
};

main 
{


    std::vector<std::shared_ptr<Event>> events;
    for (auto pEvent : events)
    {
        ParameterAssert_NotNullPtr(pEvent, "EventsQueue::proceed pEvent nullptr");
        auto event = *(pEvent.get());

        Lss(pEvent->description()); // will call MyEvent::description();
        Lss(event.description()); // will call Object::description();
        Ll("event");
    }
}
