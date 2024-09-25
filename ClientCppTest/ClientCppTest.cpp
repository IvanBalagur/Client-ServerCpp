<<<<<<< HEAD
﻿// ClientCppTest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "../ServerCppTest/.vs/ServerCppTest/httplib.h"
#include <chrono>
#include <thread>
#include <sstream>
#include <string>
#include "windows.h"
using namespace std;

//class Exception
//{
//protected:
//    int num;
//    char* str;
//public:
//    virtual void display() = 0;
//};
//
//class GlobException : public Exception
//{
//public:
//    GlobException(int num, char* str)
//    {
//        this->num = num;
//        this->str = str;
//    }
//
//    void display()
//    {
//        cout << "GlobException - #:" << num << ", " << str << endl;
//    }
//};

//Проверка принимает ли сервер запросы
bool is_server_respond(httplib::Result& res)
{
    if (res) {
        return true; 
    }
    else
    {
        auto err = res.error();
        std::cout << "HTTP error: " << httplib::to_string(err) << std::endl;
        Sleep(5000);
        exit(1);
    }
    return false;
}

void client_thread(int id, const string& message, int interval_ms)
{
    int i = 0;
    setlocale(LC_ALL, "RU");
    httplib::Client cli("localhost", 80860);

    ////Проверка того, чт пользователь успешно подключился к серверу или же нет.
    auto res = cli.Get("/hi");
    if (is_server_respond(res) == true)
    {
        std::cout << "Подключение успешно\n" << std::endl;
    }

    while (i!=10)
    {  
        
        //форматирование времени до необходимого результата
        time_t t = time(nullptr);  
        tm* timeinfo = localtime(&t);
        stringstream ss;
        ss << setfill('0')
            << setw(2) << timeinfo->tm_hour << ":"
            << setw(2) << timeinfo->tm_min << ":"
            << setw(2) << timeinfo->tm_sec;
        string timeString = ss.str();

        //debug console
        cout << " " << id << " " << message << " " << timeString << endl;


        stringstream ss2;
        ss2 << " " << id << " " << message << " " << timeString;

        auto rest = cli.Get("/on");

        if (is_server_respond(rest) == true)
        {
            cli.Post("/message", ss2.str(), "text/plain");
        }
        this_thread::sleep_for(chrono::milliseconds(interval_ms));
        i++;
    }
    
    //Пользователь закончил работу и разрывает соединение. Счетчик подключенных клиентов уменьшается.
    cli.Get("/dic");
    if (auto resp = cli.Get("/stop")) {
        if (resp->status == httplib::StatusCode::Conflict_409) {
            std::cout << "Пользователь "<< id << " закончил работу и отключился.\n" << std::endl;
            
        }
    }

}


 

int main() 
{

    thread t1(client_thread, 1, "hello", 1000);
    
    thread t2(client_thread, 2, "bay", 500);

    t1.join();
    t2.join();


    std::cout << "Program is done. Press any key and Enter to exit.\n";

    char c;
    std::cin >> c;

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
=======
﻿// ClientCppTest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "../ServerCppTest/.vs/ServerCppTest/httplib.h"
#include <chrono>
#include <thread>
#include <sstream>
#include <string>
#include "windows.h"
using namespace std;

//class Exception
//{
//protected:
//    int num;
//    char* str;
//public:
//    virtual void display() = 0;
//};
//
//class GlobException : public Exception
//{
//public:
//    GlobException(int num, char* str)
//    {
//        this->num = num;
//        this->str = str;
//    }
//
//    void display()
//    {
//        cout << "GlobException - #:" << num << ", " << str << endl;
//    }
//};



void client_thread(int id, const string& message, int interval_ms)
{
    int i = 0;
    setlocale(LC_ALL, "RU");
    httplib::Client cli("localhost", 8080);


    //Проверка того, чт пользователь успешно подключился к серверу или же нет.
    if (auto res = cli.Get("/hi")) {
        if (res->status == httplib::StatusCode::OK_200) {
            std::cout << "Подключение успешно\n" << std::endl;
        }
    }
    else {
        auto err = res.error();
        std::cout << "HTTP error: " << httplib::to_string(err) << std::endl;
        Sleep(5000);
        exit(1);
    }  

    while (i!=10)
    {       
        //форматирование времени до необходимого результата
        time_t t = time(nullptr);  
        tm* timeinfo = localtime(&t);
        stringstream ss;
        ss << setfill('0')
            << setw(2) << timeinfo->tm_hour << ":"
            << setw(2) << timeinfo->tm_min << ":"
            << setw(2) << timeinfo->tm_sec;
        string timeString = ss.str();

        //debug console
        cout << " " << id << " " << message << " " << timeString << endl;


        stringstream ss2;
        ss2 << " " << id << " " << message << " " << timeString;
        cli.Post("/message", ss2.str(), "text/plain");
        this_thread::sleep_for(chrono::milliseconds(interval_ms));
        i++;
    }
    //Пользователь закончил работу и разрывает соединение. Счетчик подключенных клиентов уменьшается.
    cli.Get("/dic");
    if (auto resp = cli.Get("/stop")) {
        if (resp->status == httplib::StatusCode::Conflict_409) {
            std::cout << "Пользователь "<< id << " закончил работу и отключился.\n" << std::endl;
            
        }
    }
}
 

int main() 
{

    thread t1(client_thread, 1, "hello", 1000);
    
    thread t2(client_thread, 2, "bay", 500);

    t1.join();
    t2.join();

    std::cout << "Program is done. Press any key and Enter to exit.\n";

    char c;
    std::cin >> c;

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
>>>>>>> 2448b8c8ddf1407bdaf152c6b1ff1895122395c3
