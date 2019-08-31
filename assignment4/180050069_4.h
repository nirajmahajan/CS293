#include <vector>
#include <iostream>

template <class T>
class myvector
{
    // declare variables that are needed. These are private to the class.
    int front = 0;
    int rear = 0;
    int mysize = 0;
    int curr_max = 1;
    std::vector<T> dataset;

    int nextI(int i){
        if(i == curr_max-1){
            return 0;
        } else {
            return i+1;
        }
    }
    int prevI(int i){
        if(i == 0){
            return curr_max-1;
        } else {
            return i-1;
        }
    }
    bool isfull() {
        return (nextI(front) == rear);
    }
    bool isempty() {
        return (front == rear);
    }


    public:
    
    // define the methods     

    void push_back(T x) {
        if (isfull()){
            // std::cout << curr_max << "pb is full\n";
            std::vector<T> temp(2*curr_max);
            int j = 0;
            for(int i = rear; i != front; i = nextI(i)) {
                temp[j] = dataset[i];
                j++;
            }
            curr_max = 2* curr_max;
            rear = 0;
            front = mysize;
            dataset = temp;
            temp.clear();
            // std::cout << temp.size() << std::endl;
            // for (auto a : temp) {
            //     std::cout << "a is " << a << std::endl;
            // }
            push_back(x); 
        } else {
            // std::cout << "here\n";
            dataset[front] = x;
            front = nextI(front);
            mysize++;
        }
    }
    void push_front(T x) {
        if (isfull()) {
            std::vector<T> temp(2*curr_max);
            int j = 0;
            for(int i = rear; i != front; i = nextI(i)) {
                temp[j] = dataset[i];
                j++;
            }
            curr_max = 2* curr_max;
            rear = 0;
            front = mysize;
            dataset = temp;
            temp.clear();
            push_front(x);
        } else {
            rear = prevI(rear);
            dataset[rear] = x;
            mysize++;
        }
    }
    void pop_back() {
        if (isempty()) {
            return;
        } else {
            mysize--;
            front = prevI(front);
        }
    }
    void pop_front() {
        if(isempty()) {
            return;
        } else {
            mysize--;
            rear = nextI(rear);
        }
    }
    int size() const {
        return mysize;
    }
    T & operator[](int i) {
        return this->dataset[(rear+i)%curr_max];
    }

    // You may also need to define a constructor for initialization;
    myvector<T>(){
        dataset.resize(1);
    }
};
