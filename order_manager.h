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
#include <list>
#include <stdexcept>

using namespace std;


struct Order{
    double price;
    int qty;
    array<char,8> id;
} temp_order;

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
    map<double,list<Order>> asc_buy_side;
    map<double,list<Order>,greater<double>> desc_sell_side;
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
    unordered_set<string> valid_types;

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
        // Insert to set of valid types
        valid_types.insert(type);
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
    if(new_order.size() < 5){
        throw runtime_error("All elements must not be empty!");
    }
    string type = new_order[1];
    transform(type.begin(), type.end(), type.begin(), ::tolower);

    if(valid_types.find(type) == valid_types.end()){
        throw runtime_error("Invalid type!");
    }

    for (int j = 0; j < 7; j++)
    {
        temp_order.id[j] = new_order[0][j];
    }

    temp_order.qty = stod(new_order[3]);
    // Throw error when invalid quantity
    if(temp_order.qty % 10 != 0){
        // cout<<temp_order.qty<<endl;
        throw runtime_error("Invalid quantity! Must be multiple of 10!");
    }else if(temp_order.qty < 10 || temp_order.qty > 1000){
        throw runtime_error("Quantity is not within valid range!");
    }


    temp_order.price = stoi(new_order[4]);
    // Throw error when invalid price
    if(temp_order.price < 0){
        throw std::runtime_error("Invalid price! Must be positive.");
    }

    // Buy
    if(new_order[2] == "1"){
        books.at(type).asc_buy_side[temp_order.price].push_back(temp_order);
    }
    // Sell
    else if(new_order[2] == "2"){
        books.at(type).desc_sell_side[temp_order.price].push_back(temp_order);
    }else{
        throw runtime_error("Invalid side!");
    }

    
}

void order_manager::print_stats(){
    cout<<books.size()<<endl;
    cout<<books.at("rose").asc_buy_side.size()<<endl;
}


#endif