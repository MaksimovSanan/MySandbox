/*
CRTP - Curiously Recurring Template Pattern
    Alternative variant of polimorhism
    + No overhead for polimorhism in runtime (static_cast makes on compile time)
    - Long time to compilation

Example:

template <typename T>
class BaseInterface {
    public:
        void someFunc() {
            // here may be some code
            static_cast<T*>(this)->implSomeFunc();
        }
};

class Impl: public BaseInterface<Impl> {
    public:
        void implSomeFunc(){
            // implemetation of specific behavior
            std::cout << "OK" << std::endl;
        }
};
*/

#include <iostream>
#include <vector>

template <typename T>
class Printable {
 public:
  void print() { static_cast<T *>(this)->printImpl(); }
};

template <typename T>
class Scannable {
 public:
  void scan() { static_cast<T *>(this)->scanImpl(); }
};

class SimplePrinter : public Printable<SimplePrinter> {
 public:
  void printImpl() { std::cout << "SimpltPrinter" << std::endl; }
};

class SimpleScanner : public Scannable<SimpleScanner> {
 public:
  void scanImpl() { std::cout << "SimpleScanner" << std::endl; }
};

class PrinterScanner9000 : public Printable<PrinterScanner9000>,
                           public Scannable<PrinterScanner9000> {
 public:
  void printImpl() { std::cout << "PrinterScanner9000 PRINT" << std::endl; }
  void scanImp() { std::cout << "PrinterScanner9000 SCAN" << std::endl; }
};

template <typename T>
void callPrint(Printable<T> &printableObj) {
  printableObj.print();
}

template <typename T>
void callScan(Scannable<T> &scannableObj) {
  scannableObj.scan();
}

typedef std::variant<SimplePrinter, PrinterScanner9000> Printers;
void printForAllPrintableObj(std::vector<Printers> &printers) {
  for (auto &printer : printers) {
    std::visit([](auto &printer) { callPrint(printer); }, printer);
  }
}

int main() {
  std::vector<Printers> test;
  SimplePrinter simplePrinter;
  PrinterScanner9000 printerScanner9000;
  test.push_back(simplePrinter);
  test.push_back(printerScanner9000);
  printForAllPrintableObj(test);

  return 0;
}
