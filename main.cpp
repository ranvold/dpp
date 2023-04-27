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
    
    while (true) {
        // думаємо
        cout << "Філософ " << id << " думає" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        
        // пробуємо взяти виделки
        cout << "Філософ " << id << " бере ліву виделку " << left << endl;
        forks[left].lock();

        cout << "Філософ " << id << " бере праву виделку " << right << endl;
        if (forks[right].try_lock()) {
          // їмо
          cout << "Філософ " << id << " їсть" << endl;
          this_thread::sleep_for(chrono::milliseconds(1000));

          // кладемо виделки
          cout << "Філософ " << id << " кладе ліву виделку " << left << endl;
          forks[left].unlock();
          cout << "Філософ " << id << " кладе праву виделку " << right << endl;
          forks[right].unlock();
        }
        else {
          // кладемо ліву виделку
          cout << "Філософ " << id << " кладе ліву виделку " << left << endl;
          forks[left].unlock();
        }
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
