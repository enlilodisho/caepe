# Components, Actions, and Events Program Engine (or CAEPE)
Caepe is a C++ library that can be used to build multi-threaded C++ applications.

Caepe revolves around 3 main concepts: Components, Actions, and Events

### Components
A Component is a module which encapsulates a group of related functions and data, in order to act as an interface providing a
particular software feature or service. With a program built on CAEPE, all functionalities are expected to be implemented
through the use of many components, each running on their own thread. CAEPE provides Actions and Events, in order to allow 
these otherwise independent units to communicate and interact with each other.

### Actions
Actions are asynchronous messages sent from one component to another. The receiving component can also asynchronously respond
to Actions. Actions are particularly useful when a component needs to request a service or data another component can provide.

### Events
Events are messages sent to one or many components. Unlike actions, events cannot be responded to.
Components who are interested in a particular event from another component, must subscribe to that event in order to receive it.


## Usage

Defining a component:
```c++
class MyComponent : public caepe::Component {
protected:
  // This function is invoked when component is started.
  void onStart() override
  {
  }
  
  // This function is invoked when component is stopped.
  void onEnd() override
  {
  }
  
  // This function is called repeatedly.
  void onLoop() override
  {
    // Do not add infinite loops or prevent this method from returning.
  }
  
  // This function is invoked when an action is received.
  void onAction(Component &sender, std::shared_ptr<caepe::Action> action,
                std::shared_ptr<caepe::ActionResponseContainer> responseContainer) override
  {
    // Do not add infinite loops or prevent this method from returning.
    
    // An example of receiving an action and sending a response:
    if (action->getName() == "PingRequest")
    {
      responseContainer->setActionResponse(std::make_unique<caepe::ActionResponseContainer>("PingResponse"));
      // Note that response container can be saved in this component and used to respond later.
    } 
  }
  
  // This function is invoked when an event is received.
  void onEvent(Component &sender, std::shared_ptr<const caepe::Event> event) override
  {
    // Do not add infinite loops or prevent this method from returning.
  }
public:
  explicit MyComponent(const std::string& name) : caepe::Component(name)
  {
  }
};
```

Starting/stopping a component:
```c++
MyComponent component("MyComponent1");
component.start(); // start component
component.stop(); // stop component
```

Sending an action to a component:
```c++
caepe::Component aComponent;
std::unique_ptr<caepe::Action> actionToSend = std::make_unique<caepe::Action>("PingRequest", std::vector<caepe::Action::Parameter>{"1.1.1.1", 80});
std::shared_ptr<caepe::Action> action_cpy;
aComponent.receiveAction(this, std::move(actionToSend), action_cpy);

// to check if response available later:
if (action_cpy->isResponseSet())
{
  caepe::ActionResponse actionResponse;
  if (action_cpy->getResponse(actionResponse).getValue() == caepe::RESULT_OK)
  {
  }
}
```

Subscribing and posting events:
```c++
// Sender component header:
private:
  caepe::EventManager eventManager;
public:
  caepe::EventDelegate eventDelegate(eventManager);

// To subscribe to event from receiving component:
eventDelegate.subscribe(*this);

// To send event from sender component:
eventManager.post(this, std::make_unique<caepe::Event>());
```
