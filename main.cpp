#include "rapidcsv.h"
#include <vector>
#include <iostream>
#include <array>
#include <bits/stdc++.h>

using namespace std;

struct order_row
{
    array<char, 7> orderId;
    string instrument;
    int side;
    double price;
    int quantity;
} temp_order;

int main()
{
    rapidcsv::Document doc("colhdr.csv");

    // vector<float> col = doc.GetColumn<float>("Close");
    // cout << "Read " << col.size() << " values." << endl;

    vector<order_row> orders;

    int num_of_rows = doc.GetRowCount();

    for (size_t i = 0; i < num_of_rows; i++)
    {
        vector<string> row = doc.GetRow<string>(i);

        char temp[7];
        strcpy(temp, row[0].c_str());

        for (int j = 0; j < 7; j++)
        {
            temp_order.orderId[j] = temp[j];
        }

        temp_order.instrument = row[1];
        temp_order.side = stoi(row[2]);
        temp_order.price = stod(row[3]);
        temp_order.quantity = stoi(row[4]);

        orders.push_back(temp_order);
    }

    return 0;
}