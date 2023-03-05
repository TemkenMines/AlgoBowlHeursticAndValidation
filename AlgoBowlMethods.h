#ifndef ALGOBOWL_ALGOBOWLMETHODS_H
#define ALGOBOWL_ALGOBOWLMETHODS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int bad_guarantee_simple(int, const int[]);

pair<int, vector<pair<int, int>>> bad_guarantee(int, const int[]);

pair<int, vector<pair<int, int>>> heuristic_run(int, const int[], const string&);

int heuristic_run_file_manage(const string&);

bool report_valid_out(const string&);

#endif //ALGOBOWL_ALGOBOWLMETHODS_H