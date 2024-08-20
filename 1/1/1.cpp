#include <iostream>
#include<thread>
#include<chrono>
#include<atomic>

std::atomic<int> num = 1;

void client(int n1) {
    while (num < n1) {
        num++;
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }
}

void Operator() {
    while (num > 0) {
        std::cout << "В очереди сейчас " << num << " человек" << std::endl;
        num--;
        std::this_thread::sleep_for(std::chrono::seconds(2));

    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int max_cl = 10;
    std::thread t1(client, max_cl);
    std::thread t2(Operator);
    t1.join();
    t2.join();

    return 0;
}