#include <iostream>
#include <string>
#include "AlgoBowlMethods.h"

using namespace std;

string files[] = {"592", "593", "594", "595", "596", "597", "598", "599", "600",
                  "601", "602", "603", "604", "606", "607", "608", "609",
                  "610", "611", "613", "614", "615", "616", "618", "620",
                  "622", "624", "626", "628", "630", "632"};

int main() {
    for(const string &fileNum: files){
        cout << fileNum << " | ";
        if(report_valid_out(fileNum)){
            cout << "Valid" << endl;
        }else{
            cout << "Invalid" << endl;
        }
    }
    return 0;
    for(const string& fileNum: files){
        heuristic_run_file_manage(fileNum);
    }
    return 0;
}