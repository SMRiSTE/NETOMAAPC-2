#include <iostream>
#include<thread>
#include<mutex>

class Data {
public:
    int data;
    std::mutex m;

    Data(int d) : data(d) {}

    int getData() {
        return data;
    }

    void setData(int d) {
        data = d;
    }
};

void swap_w_l(Data& d1, Data& d2) {
    std::lock(d1.m, d2.m);
    std::lock_guard(d1.m, std::adopt_lock);
    std::lock_guard(d2.m, std::adopt_lock);

    int temp = d1.getData();
    d1.setData(d2.getData());
    d2.setData(temp);

    d1.m.unlock();
    d2.m.unlock();
}

void swap_w_sl(Data& d1, Data& d2) {
    std::scoped_lock<std::mutex> sl{ d1.m, d2.m };

    int temp = d1.getData();
    d1.setData(d2.getData());
    d2.setData(temp);
}

void swap_w_ul(Data& d1, Data& d2) {
    std::unique_lock<std::mutex> ul1(d1.m, std::defer_lock);    
    std::unique_lock<std::mutex> ul2(d2.m, std::defer_lock);
    std::lock(ul1, ul2);

    int temp = d1.getData();
    d1.setData(d2.getData());
    d2.setData(temp);
}

int main() {
    Data d1(10);
    Data d2(20);

    swap_w_l(d1, d2);
    std::cout << d1.getData() << "   " << d2.getData();
}