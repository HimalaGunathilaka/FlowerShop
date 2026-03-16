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

/**
 * @brief Struct for buy side of order_book
 *
 */
struct buy
{
    array<char, 7> order_id;
    int qty;
    double price;
} temp_buy;

/**
 * @brief Struct for sell side of order_book
 *
 */
struct sell
{
    double price;
    int qty;
    array<char, 7> order_id;
} temp_sell;

/**
 * @brief Order book it self
 *
 */
struct order
{
    vector<pair<buy, sell>> order_book;
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
    unordered_map<string, order> books;
    // multiset<

public:
    order_manager(vector<string> types);
    ~order_manager();

    void insertOrder(vector<string> new_order);
};

order_manager::order_manager(vector<string> types)
{
    for (size_t i = 0; i < types.size(); i++)
    {
        string type = types[i];
        transform(type.begin(), type.end(), type.begin(), ::tolower);
        books.insert({type, order()});
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

    for (size_t i = 0; i < new_order.size(); i++)
    {
        string type = new_order[i];
        transform(type.begin(), type.end(), type.begin(), ::tolower);
        // Buy
        if (new_order[2] == "1")
        {
            for (int j = 0; j < 7; j++)
            {
                temp_buy.order_id[j] = new_order[0][j];
            }
            temp_buy.price = stod(new_order[3]);
            temp_buy.qty = stoi(new_order[4]);
        }
        // Sell
        else if (new_order[2] == "2")
        {
            for (int j = 0; j < 7; j++)
            {
                temp_sell.order_id[j] = new_order[0][j];
            }
            temp_sell.price = stod(new_order[3]);
            temp_sell.qty = stoi(new_order[4]);
        }
        books.at(type).order_book.push_back(make_pair(temp_buy, temp_sell));
    }
}

#endif