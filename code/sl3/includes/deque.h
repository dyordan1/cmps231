class Deque
{
public:
    Deque();
    void push_back(int value);
    void push_front(int value);
    int pop_back();
    int pop_front();
    bool is_full() const;
    bool is_empty() const;

    // Make sure you reference this const whenever dealing with capacity, so you can
    // change the capacity of the Deque by altering just this line of code.
    static const int CAPACITY = 100;

private:
    // add any private members you think are necessary.

    int data[CAPACITY];
    int front;
    int back;
    int count;

    void right(int &);
    void left(int &);
};