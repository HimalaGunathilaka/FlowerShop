#include <iostream>
#include <bits/stdc++.h>

#include "order_manager.h"
#include "execution_report.h"

using namespace std;

const string output = "data/execution_rep.csv";

const vector<string> types = {"rose", "lavender", "lotus", "tulip", "orchid"};
const vector<string> headers = {"Order_ID","Client_Order","Instrument","Side","Exec_Status","Quantity","Price"};

execution_report exe_rpt(headers,output,100);
order_manager order_mgr(types,exe_rpt);

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
            order_mgr.process_orders();
        }catch(const exception& e){
            cerr<<"Error detected: "<<e.what()<<endl;
            
            vector<string> error_input;
            error_input.push_back(row[0]);
            error_input.push_back(row[1]);
            error_input.push_back(row[2]);
            error_input.push_back("Reject");
            error_input.push_back(row[3]);
            error_input.push_back(row[4]);
            exe_rpt.insert_row(error_input);
        }
    }

    // order_mgr.print_stats();

    return 0;
}