#include"Task.h"
#include"TaskSystem.h"
using namespace std::chrono_literals;  // ms, s

void print() {
    std::cout << "HelloWorld" << std::endl;
    std::cout << std::this_thread::get_id() << std::endl;
}

void print2() {
    std::cout << "AAA" << std::endl;
    std::cout << std::this_thread::get_id() << std::endl;
}



int main()
{
    TaskSystem::Get().Initialize(4);
    std::vector<Task*> tasks;
    tasks.emplace_back(new Task(print));
    tasks.emplace_back(new Task(print2));
    for (auto& v : tasks)
        v->RegisterToJobSystem();
    return 1;
}

