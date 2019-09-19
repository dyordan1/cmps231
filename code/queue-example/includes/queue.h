#include <stdexcept>

const int QMAX_SIZE = 6;  // silly.


class queue {
  public:
      queue() ;
      void enqueue(int value);
      int dequeue();
      bool is_full();
      bool is_empty();
  private:
      int data[QMAX_SIZE];
      int count;
      int front;
      int back;
};