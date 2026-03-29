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
#include <string>

#include "execution_report.h"

using namespace std;


#include <algorithm>

template<size_t N>
std::string arrayToString(const std::array<char, N>& arr) {
    auto it = std::find(arr.begin(), arr.end(), '\0');
    return std::string(arr.begin(), it);
}


struct Order{
    double price;
    int qty;
    array<char,8> id;
} temp_order,buy,sell;

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
    // Highest price first for buyers
    map<double, list<Order>, greater<double>> buy_side; 
    // Lowest price first for sellers
    map<double, list<Order>> sell_side;                 
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
    execution_report &report;
    
    public:
    order_manager(vector<string> types, execution_report& rep);
    ~order_manager();
    
    void insertOrder(vector<string> new_order);
    void print_stats();
    void process_orders();
};

order_manager::order_manager(vector<string> types,execution_report& rep)
   : report(rep)
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

    vector<string> push_this = new_order;
    push_this.insert(push_this.begin() + 3, "New");
    
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
        books.at(type).buy_side[temp_order.price].push_back(temp_order);
    }
    // Sell
    else if(new_order[2] == "2"){
        books.at(type).sell_side[temp_order.price].push_back(temp_order);
    }else{
        throw runtime_error("Invalid side!");
    }
    report.insert_row(push_this);
}

void order_manager::print_stats(){
    cout<<books.size()<<endl;
    cout<<books.at("rose").buy_side.size()<<endl;
}

void order_manager::process_orders(){    
    for(const string type:valid_types){

        auto& buy_map = books[type].buy_side;
        auto& sell_map = books[type].sell_side;
        
        while (!buy_map.empty() && !sell_map.empty()) 
        {
            auto buy_it = buy_map.begin();
            auto sell_it = sell_map.begin();

            if(buy_it->first < sell_it->first) break;

            Order& top_buy = buy_it->second.front();
            Order& top_sell = sell_it->second.front();

            int matched_qty = min(top_buy.qty, top_sell.qty);
            double match_price = sell_it->first;

            vector<string> buy_row;
            buy_row.push_back(arrayToString(top_buy.id));
            buy_row.push_back(type);
            buy_row.push_back("1");
            buy_row.push_back(top_buy.qty == matched_qty ? "Fill" : "PFill");
            buy_row.push_back(to_string(matched_qty));
            buy_row.push_back(to_string(match_price));
            report.insert_row(buy_row);

            vector<string> sell_row;
            sell_row.push_back(arrayToString(top_sell.id));
            sell_row.push_back(type);
            sell_row.push_back("2");
            sell_row.push_back(top_sell.qty == matched_qty ? "Fill" : "PFill");
            sell_row.push_back(to_string(matched_qty));
            sell_row.push_back(to_string(match_price));
            report.insert_row(sell_row);

            top_buy.qty -= matched_qty;
            top_sell.qty -= matched_qty;

            if(top_buy.qty == 0){
                buy_it->second.pop_front();
                if(buy_it->second.empty()) buy_map.erase(buy_it);
            }

            if(top_sell.qty == 0){
                sell_it->second.pop_front();
                if(sell_it->second.empty()) sell_map.erase(sell_it);
            }
        }
    }
}

// ==================================

#include <array>
#include <string>
#include <algorithm>
#include <array>
#include <string>
#include <algorithm>

#endif