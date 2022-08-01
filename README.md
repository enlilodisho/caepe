# Components, Actions, and Events Program Engine (or CAEPE)
Caepe is a C++ library that can be used to build multi-threaded C++ applications.

Caepe revolves around 3 main concepts: Components, Actions, and Events

## Components
A Component is a module which encapsulates a group of related functions and data, in order to act as an interface providing a
particular software feature or service. With a program build on CAEPE, all functionalities are expected to be implemented
through the use of many components, each running on their own thread. CAEPE provides Actions and Events, in order to allow 
these otherwise independent units to communicate and interact with each other.

## Actions
Actions are asynchronous messages sent from one component to another. The receiving component can also asynchronously respond
to Actions. Actions are particularly useful when a component needs to request a service or data another component can provide.

## Events
Events are messages sent to one or many components. Unlike actions, events cannot be responded to.
Components who are interested in a particular event from another component, must subscribe to that event in order to receive it.
