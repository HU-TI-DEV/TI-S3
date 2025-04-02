# Handler pattern [](title-id)
Het grootste deel van deze pagina is vertaald naar het Nederlands en afkomstig van Wikipedia: [Chain of responsibility pattern](https://en.wikipedia.org/wiki/Chain-of-responsibility_pattern).


## Inhoud
- [Handler pattern ](#handler-pattern-)
  - [Inhoud](#inhoud)
  - [Introductie](#introductie)
  - [UML voorbeeld (wikipedia)](#uml-voorbeeld-wikipedia)
  - [Codevoorbeeld Handler pattern](#codevoorbeeld-handler-pattern)
  - [Andere design patterns](#andere-design-patterns)
  - [Referenties](#referenties)

## Introductie
Het handler pattern wordt ook wel het *"Chain of Responsibility"* design pattern genoemd.
Het handler pattern voorkomt dat de zender van een verzoek direct gekoppeld is aan de ontvanger van het verzoek.
Door toepassing van het handler pattern is het mogelijk dat meer dan één ontvanger een verzoek kan afhandelen.

## UML voorbeeld (wikipedia)
![uml voorbeeld](https://upload.wikimedia.org/wikipedia/commons/6/6a/W3sDesign_Chain_of_Responsibility_Design_Pattern_UML.jpg)
*Bron voorbeeld: [wikipedia](https://upload.wikimedia.org/wikipedia/commons/6/6a/W3sDesign_Chain_of_Responsibility_Design_Pattern_UML.jpg)

## Codevoorbeeld Handler pattern
```c++
#include <iostream>
#include <memory>

typedef int Topic;
constexpr Topic NO_HELP_TOPIC = -1;

// defines an interface for handling requests.
class HelpHandler { // Handler
public:
  HelpHandler(HelpHandler* h = nullptr, Topic t = NO_HELP_TOPIC)
    : successor(h), topic(t) {}
  virtual bool hasHelp() {
    return topic != NO_HELP_TOPIC;
  }
  virtual void setHandler(HelpHandler*, Topic) {}
  virtual void handleHelp() {
      std::cout << "HelpHandler::handleHelp\n";
      // (optional) implements the successor link.
      if (successor != nullptr) {
          successor->handleHelp();
      }
  }
  virtual ~HelpHandler() = default;
  HelpHandler(const HelpHandler&) = delete; // rule of three
  HelpHandler& operator=(const HelpHandler&) = delete;
private:
  HelpHandler* successor;
  Topic topic;
};


class Widget : public HelpHandler {
public:
  Widget(const Widget&) = delete; // rule of three
  Widget& operator=(const Widget&) = delete;
protected:
  Widget(Widget* w, Topic t = NO_HELP_TOPIC) 
    : HelpHandler(w, t), parent(nullptr) {
    parent = w;
  }
private:
  Widget* parent;
};

// handles requests it is responsible for.
class Button : public Widget { // ConcreteHandler
public:
  Button(std::shared_ptr<Widget> h, Topic t = NO_HELP_TOPIC) : Widget(h.get(), t) {}
  virtual void handleHelp() {
    // if the ConcreteHandler can handle the request, it does so; otherwise it forwards the request to its successor.
    std::cout << "Button::handleHelp\n";
    if (hasHelp()) {
      // handles requests it is responsible for.
    } else {      
      // can access its successor.
      HelpHandler::handleHelp();
    }
  }
};

class Dialog : public Widget { // ConcreteHandler
public:
  Dialog(std::shared_ptr<HelpHandler> h, Topic t = NO_HELP_TOPIC) : Widget(nullptr) {
    setHandler(h.get(), t);
  }
  virtual void handleHelp() {
    std::cout << "Dialog::handleHelp\n";
    // Widget operations that Dialog overrides...
    if(hasHelp()) {
      // offer help on the dialog
    } else {
      HelpHandler::handleHelp();
    }
  }
};

class Application : public HelpHandler {
public:
  Application(Topic t) : HelpHandler(nullptr, t) {}
  virtual void handleHelp() {
    std::cout << "Application::handleHelp\n";
    // show a list of help topics
  }
};

int main() {
  constexpr Topic PRINT_TOPIC = 1;
  constexpr Topic PAPER_ORIENTATION_TOPIC = 2;
  constexpr Topic APPLICATION_TOPIC = 3;
  // The smart pointers prevent memory leaks.
  std::shared_ptr<Application> application = std::make_shared<Application>(APPLICATION_TOPIC);
  std::shared_ptr<Dialog> dialog = std::make_shared<Dialog>(application, PRINT_TOPIC);
  std::shared_ptr<Button> button = std::make_shared<Button>(dialog, PAPER_ORIENTATION_TOPIC);

  button->handleHelp();
}
```
*Code example, taken from [wikipedia](https://en.wikipedia.org/wiki/Chain-of-responsibility_pattern).*

## Andere design patterns
Meer design patterns kun je vinden in het [overzicht van design patterns](README.md).

## Referenties
- Wikipedia: [Chain of responsibility pattern](https://en.wikipedia.org/wiki/Chain-of-responsibility_pattern)
- Erich Gamma (1994). Design Patterns: Elements of Reusable Object-Oriented Software. Addison Wesley. pp. 189 ff. ISBN 0-201-63361-2.