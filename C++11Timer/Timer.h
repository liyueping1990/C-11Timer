#pragma once
#ifndef TIMER_H_
#define TIMER_H_
#include <iostream>
#include<thread>
#include<atomic>
#include<mutex>

//#include<condition_variable>
//#include<memory>
//#include<functional>
//#include<chrono>

class Timer 
{
public:
	Timer() :expired_(true), try_to_expire_(false) {}
	Timer(const Timer& t);
	~Timer();

	void StartTimer(int interval, std::function<void()> task);
	void Expire();

	// Õ¨≤Ω
	template<typename callable, class... arguments>
	void SyncWait(int after, callable&& f, arguments&&... args);

	// “Ï≤Ω
	template<typename callable, class... arguments>
	void AsyncWait(int after, callable&& f, arguments&&... args);


private:
	std::atomic<bool> expired_;
	std::atomic<bool> try_to_expire_;
	std::mutex mutex_;
	std::condition_variable expired_cond_;
};

template<typename callable, class ...arguments>
inline void Timer::SyncWait(int after, callable && f, arguments && ...args)
{
	std::function<typename std::result_of<callable(arguments...)>::type()> task
	(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));
	std::this_thread::sleep_for(std::chrono::milliseconds(after));
	task();
}

template<typename callable, class ...arguments>
inline void Timer::AsyncWait(int after, callable && f, arguments && ...args)
{
	{
		std::function<typename std::result_of<callable(arguments...)>::type()> task
		(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

		std::thread([after, task]()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(after));
			task();
		}).detach();
	}
}
#endif