#include "rapidcsv.h"
#include <vector>
#include <iostream>
#include <array>
#include <bits/stdc++.h>
#include "order_manager.h"

using namespace std;

vector<string> types = {"rose", "lavender", "lotus", "tulip", "orchid"};


order_manager order_mgr(types);

int main()
{
    rapidcsv::Document doc("data/orders.csv");
    // rapidcsv::Document execution_rep("data/exection_rep.csv");

    int num_of_rows = doc.GetRowCount();

    for (size_t i = 0; i < num_of_rows; i++)
    {
        vector<string> row = doc.GetRow<string>(i);
        try{
            order_mgr.insertOrder(row);
        }catch(const exception& e){
            cerr<<"Error detected: "<<e.what()<<endl;
        }
    }

    order_mgr.print_stats();

    // rapidcsv::Document doc("data/execution_rep.csv");
    
    // for(size_t i=0; i< doc.GetRowCount();i++){
    //     vector<string> row = doc.GetRow<string>(i);
    //     cout<<endl;
    //     for(string ele:row){
    //         cout<<ele<<" ";
    //     }

    //     cout<<i<<endl;
    // }
    return 0;
}