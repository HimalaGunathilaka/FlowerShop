#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include <vector>
#include <array>
#include <unordered_map>
#include <string>

using namespace std;

struct buy
{
    array<char, 7> order_id;
    int qty;
    double price;
};

struct sell
{
    double price;
    int qty;
    array<char, 7> order_id;
};

struct order
{
    vector<buy, sell> order_book;
};

class oder_manager
{
private:
    unordered_map<string, order> books;

public:
    oder_manager(/* args */);
    ~oder_manager();
};

oder_manager::oder_manager(/* args */)
{
}

oder_manager::~oder_manager()
{
}

#endif