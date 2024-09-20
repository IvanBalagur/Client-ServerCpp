// ServerCppTest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include ".vs/ServerCppTest/httplib.h"
#include <fstream>
#include <mutex>

using namespace std;
mutex mtx;

void append_to_file(const string& content) 
{
    lock_guard<mutex> lock(mtx);
    ofstream file("messages.txt", ios_base::app);
    file << content << endl;
}

int main() 
{
    httplib::Server svr;

    svr.Post("/message", [](const httplib::Request& req, httplib::Response& res) 
        {
        auto body = req.body;
        append_to_file(body); // Записывает в файл запрос в формате "номер:сообщение:время H:М:S"  
        });

    svr.listen("localhost", 8080);

    return 0;
}
