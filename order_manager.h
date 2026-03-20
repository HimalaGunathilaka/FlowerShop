/**
 * @file order_manager.h
 * @author Himala Gunathilaka
 * @brief This file is for the declaring the order_manager class for handling the orders
 * @version 0.1
 * @date 2026-03-16
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include <vector>
#include <array>
#include <unordered_map>
#include <string>
#include <bits/stdc++.h>
#include <utility>
#include <set>

using namespace std;

struct Order{
    double price;
    int qty;
    array<char,8> id;
} temp_sell, temp_buy;

struct CompareSellPrice{
    bool operator()(const Order& a, const Order& b) const{
        return a.price > b.price;
    }
};

struct CompareBuyPrice{
    bool operator()(const Order& a, const Order& b) const{
        return a.price < b.price;
    }
};

struct OrderBook {
    map<double,vector<Order>> asc_buy_side;
    map<double,vector<Order>,greater<double>> desc_sell_side;
};

// ============================================
// ============================================
// ============================================
class order_manager
{
private:
    /**
     * @brief collection of order book. It is a keyvalue pair
     *
     */
    unordered_map<string, OrderBook> books;    

public:
    order_manager(vector<string> types);
    ~order_manager();

    void insertOrder(vector<string> new_order);
    void print_stats();
};

order_manager::order_manager(vector<string> types)
{
    for (size_t i = 0; i < types.size(); i++)
    {
        string type = types[i];
        transform(type.begin(), type.end(), type.begin(), ::tolower);
        books.insert({type, OrderBook()});
    }
}

// Runs when the object gets destroyed.
order_manager::~order_manager()
{
}

/**
 * @brief Insert new orders to the order book collection
 *
 * @param new_order Row of string from the orders.csv file
 */
void order_manager::insertOrder(vector<string> new_order)
{
    string type = new_order[1];
    transform(type.begin(), type.end(), type.begin(), ::tolower);
    // cout<<type<<endl;
    // Buy
    if (new_order[2] == "1")
    {
        for (int j = 0; j < 7; j++)
        {
            temp_buy.id[j] = new_order[0][j];
        }
        temp_buy.price = stod(new_order[3]);
        temp_buy.qty = stoi(new_order[4]);
        books.at(type).asc_buy_side[temp_buy.price].push_back(temp_buy);
    }
    // Sell
    else if (new_order[2] == "2")
    {
        for (int j = 0; j < 7; j++)
        {
            temp_sell.id[j] = new_order[0][j];
        }
        temp_sell.price = stod(new_order[3]);
        temp_sell.qty = stoi(new_order[4]);
        books.at(type).desc_sell_side[temp_sell.price].push_back(temp_sell);
    }
}

void order_manager::print_stats(){
    cout<<books.size()<<endl;
    cout<<books.at("rose").asc_buy_side.size()<<endl;
}


#endif