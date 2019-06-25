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

    // ������ִ�ж�ʱ����
    t.StartTimer(1000, std::bind(EchoFunc, "hello world!")); // ������ʱ��
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "try to expire timer!" << std::endl;
    t.Expire();	// ��ֹ��ʱ��



    std::this_thread::sleep_for(std::chrono::seconds(2));

    // ִֻ��һ�ζ�ʱ����
    t.SyncWait(5000, EchoFunc, "ͬ��!");// ͬ��
    std::cout << "try to ͬ��!" << std::endl;

    t.AsyncWait(5000, EchoFunc, "�첽!");// �첽
    std::cout << "try to �첽!" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}