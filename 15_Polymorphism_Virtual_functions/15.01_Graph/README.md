Statistics are usually shown in the form of graphs. Graphs can be of different types,
such as bar graphs, line graphs, pie charts, and so on. A bar graph is shown with
vertical or horizontal bars against a scale, while a pie chart is shown by dividing
a circle into proportionate segments. In a well-designed system, these would be
derived from a common class, Graph. You are to implement such a system.

The class Graph is the base class. You should add only BarGraph and LineGraph
classes derived from Graph. Each class has stubs for member functions erase and
draw. Each of these member functions outputs a message telling what function has
been called and what the class of the calling object is. Since these are just stubs, they
do nothing more than output this message. The member functions should take no
arguments. There are three parts to this project:
a. Do the class definitions using no virtual functions. Compile and test.
b. Make the base class member functions virtual. Compile and test.
c. Explain the difference in results.

---
In the current main, there is no observable difference.
When we call draw()/erase() on concrete objects (bar.draw(), line.draw()), 
the compiler already knows the exact type.

The real difference appears when calling through a Graph* or Graph&:
- Without virtual (Graph::draw, Graph::erase non-virtual):
  calls are resolved by the static type (Graph) → Graph::draw() / Graph::erase() run.
- With virtual:
  calls are resolved by the runtime object type (BarGraph or LineGraph): overridden derived methods run.

So virtual enables runtime polymorphism (dynamic dispatch).

- If we don't use virtual, the function that gets called depends on the type of the pointer or reference, not the actual object.
For example:
```cpp
Graph* g = new BarGraph();
g->draw(); // Calls Graph::draw() if not virtual
```

- If we use virtual, the function that gets called depends on the actual type of the object the pointer or reference points to,
  not just the pointer type. For example:
```cpp
Graph* g = new BarGraph();
g->draw(); // Calls BarGraph::draw() if virtual
```