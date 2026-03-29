#ifndef EXECUTION_REPORT_H
#define EXECUTION_REPORT_H

#include <string>
#include <vector>
#include "rapidcsv.h"

using namespace std;

class execution_report
{
    private:
        rapidcsv::Document doc;  
        string filename;  
        int row_buffer; // To store upto some amount of rows before writing into disk.
        int ROW_BUFFER_UPPER_LIMIT;
    public:
        execution_report(const vector<string>& headers, const string& name, int buffer_limit = 100);
        ~execution_report();

        void insert_row(const vector<string>& row);
};

inline execution_report::execution_report(const vector<string>& headers,const string& name, int buffer_limit)
    : filename(name), ROW_BUFFER_UPPER_LIMIT(buffer_limit), row_buffer(0) 
{
    for(size_t i = 0; i < headers.size(); i++){
        doc.SetColumnName(i, headers[i]);
    }
}

inline execution_report::~execution_report()
{
    doc.Save(filename);
}

inline void execution_report::insert_row(const vector<string>& row){
    int row_count = doc.GetRowCount();
    vector<string> push_this;
    push_this.reserve(row.size() +1);

    push_this.push_back("ord" + to_string(row_count));
    push_this.insert(push_this.end(), row.begin(), row.end());

    doc.InsertRow(row_count,push_this);
    row_buffer ++;

    if(row_buffer >= ROW_BUFFER_UPPER_LIMIT){
        doc.Save(filename);
        row_buffer = 0;
    }
}

#endif