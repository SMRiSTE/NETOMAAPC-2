#include <iostream>
#include<thread>
#include<chrono>
#include<string>
#include<mutex>
#include <cstdlib>
#include<vector>
#include"Timer.h"

std::mutex m;

int my_rand() {
    int seed = 1;
    seed = seed * 1103515245 + 12345;
    return (seed / 65536) % 200;
}

void ProgBar(int num_threads) {
    consol_parameter cp;
    int num = 12;
    std::string Bar = "[            ]";
    auto ST = std::chrono::steady_clock::now();
    for (int i = 0; i < num; i++) {
        std::unique_lock<std::mutex> lk(m);
        Bar[i + 1] = '|';
        cp.SetPosition(0, num_threads - 1);
        std::cout << "Номер потока: " << num_threads << " / Id: " << std::this_thread::get_id() << " / Bar: " << Bar << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(my_rand()));
        lk.unlock();
    }
    auto FT = std::chrono::steady_clock::now();

    auto Time = std::chrono::duration_cast<std::chrono::milliseconds>(FT - ST).count();
    if (Bar[Bar.size() - 2] == '|') {
        std::unique_lock<std::mutex> lk(m);
        cp.SetPosition(0, num_threads - 1);
        std::cout << "Номер потока: " << num_threads << " / Id: " << std::this_thread::get_id() << " / Bar: " << Bar << " / Time: " << Time <<std::endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::vector<std::thread> threads;

    for (int i = 1; i <= 5; ++i) {
        threads.push_back(std::thread(ProgBar, i));
    }

    for (auto& t : threads) {
        t.join();
    }

}