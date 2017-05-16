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
	t.StartTimer(1000, std::bind(EchoFunc, "hello world!"));
	std::this_thread::sleep_for(std::chrono::seconds(4));
	//std::cout << "try to expire timer!" << std::endl;
	t.Expire();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	// 只执行一次定时任务	
	t.SyncWait(1000, EchoFunc, "同步!");// 同步	
	t.AsyncWait(1000, EchoFunc, "异步!");// 异步
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return 0;
}