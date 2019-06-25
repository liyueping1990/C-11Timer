#include<iostream>
#include<string>
#include<memory>
#include"Timer.h"

using namespace std;

void EchoFunc(std::string&& s)
{
    std::cout << "test : " << s << endl;
}



int main()
{
    Timer t;

    // 周期性执行定时任务
    t.StartTimer(1000, std::bind(EchoFunc, "hello world!")); // 启动定时器
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "try to expire timer!" << std::endl;
    t.Expire();	// 终止定时器



    std::this_thread::sleep_for(std::chrono::seconds(2));

    // 只执行一次定时任务
    t.SyncWait(5000, EchoFunc, "同步!");// 同步
    std::cout << "try to 同步!" << std::endl;

    t.AsyncWait(5000, EchoFunc, "异步!");// 异步
    std::cout << "try to 异步!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}