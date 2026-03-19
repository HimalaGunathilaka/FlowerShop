#include "rapidcsv.h"
#include <vector>
#include <iostream>
#include <array>
#include <bits/stdc++.h>
#include "order_manager.h"

using namespace std;

vector<string> types = {"Rose", "Lavender", "Lotus", "Tulip", "Orchid"};
order_manager order_mgr(types);

int main()
{
    rapidcsv::Document doc("data/orders.csv");

    int num_of_rows = doc.GetRowCount();

    for (size_t i = 0; i < num_of_rows; i++)
    {
        vector<string> row = doc.GetRow<string>(i);
        order_mgr.insertOrder(row);
    }

    order_mgr.print_stats();
    return 0;
}