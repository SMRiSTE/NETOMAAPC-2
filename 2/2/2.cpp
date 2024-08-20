#include <iostream>
#include<thread>
#include<chrono>
#include<string>
#include<mutex>
#include <cstdlib>
#include<vector>

std::mutex m;

void ProgBar(int num_threads) {
    int num = 12;
    std::string Bar = "[            ]";
    auto ST = std::chrono::steady_clock::now();
    for (int i = 0; i < num; i++) {
        std::unique_lock<std::mutex> lk(m);
        Bar[i + 1] = '|';
        std::cout << "Номер потока: " << num_threads << " / Id: " << std::this_thread::get_id() << " / Bar: " << Bar << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        lk.unlock();
    }
    auto FT = std::chrono::steady_clock::now();

    auto Time = std::chrono::duration_cast<std::chrono::milliseconds>(FT - ST).count();
    if (Bar[Bar.size() - 2] == '|') {
        std::unique_lock<std::mutex> lk(m);
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