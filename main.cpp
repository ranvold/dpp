// Volodymyr Shafran TTP-32 OS Lab4

#include <iostream>
#include <thread>
#include <mutex>
#include <random>

using namespace std;

const int N = 5; // кількість філософів

mutex forks[N]; // виделки

void philosopher(int id) {
    int left = id;
    int right = (id + 1) % N;

    // визначаємо час
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> sleep_dist(500, 1500);
    
    while (true) {
        // думаємо
        cout << "Філософ " << id << " думає" << endl;
        this_thread::sleep_for(chrono::milliseconds(sleep_dist(gen)));
        
        // беремо виделки
        cout << "Філософ " << id << " бере ліву виделку " << left << endl;
        forks[left].lock();
        cout << "Філософ " << id << " бере праву виделку " << right << endl;
        forks[right].lock();
        
        // їмо
        cout << "Філософ " << id << " їсть" << endl;
        this_thread::sleep_for(chrono::milliseconds(sleep_dist(gen)));
        
        // кладемо виделки
        cout << "Філософ " << id << " кладе ліву виделку " << left << endl;
        forks[left].unlock();
        cout << "Філософ " << id << " кладе праву виделку " << right << endl;
        forks[right].unlock();
    }
}

int main() {
    thread philosophers[N];
    for (int i = 0; i < N; i++) {
        philosophers[i] = thread(philosopher, i);
    }
    for (int i = 0; i < N; i++) {
        philosophers[i].join();
    }
    return 0;
}
