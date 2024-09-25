// ServerCppTest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include ".vs/ServerCppTest/httplib.h"
#include <fstream>
#include <mutex>

using namespace std;
mutex mtx;

class ConectionManager 
{
private:
    int connections=0;
public:
    void incrementConn() { connections++; }
    void dicrementConn() { connections--; }
    int getConnCount() { return connections; }

};

void append_to_file(const string& content) 
{
    lock_guard<mutex> lock(mtx);
    ofstream file("messages.txt", ios_base::app);
    file << content << endl;
}

int main() 
{
    ConectionManager counter;
    setlocale(LC_ALL, "RU");
    httplib::Server svr;
    

    
    svr.Post("/message", [](const httplib::Request& req, httplib::Response& res) 
        {  
        auto body = req.body;
        append_to_file(body); // Записывает в файл запрос в формате "номер:сообщение:время H:М:S"  
        });

    svr.Get("/hi", [&](const httplib::Request& req, auto & res) {
        cout << "Пользователь подключился к серверу\n" << endl;
        counter.incrementConn();
        res.status = httplib::StatusCode::OK_200;
        });

    svr.Get("/on", [&](const httplib::Request& req, auto& res)
        {
            res.status = httplib::StatusCode::OK_200;
        });

    svr.Get("/dic", [&counter](const httplib::Request& req, httplib::Response& res) {
        counter.dicrementConn(); 
        });

    svr.Get("/stop", [&](const httplib::Request& req, auto& res) {
        cout << "Пользователь отключился\n" << endl;
        cout << "Amount users now is - " << counter.getConnCount() << endl;
        res.status = httplib::StatusCode::Conflict_409;
        if (counter.getConnCount() == 0) 
        {
            svr.stop();
        }
        
        });

    
    

    cout << "Server running on port 8080 and now on\n";
    svr.listen("localhost", 8080);
    return 0;
}
