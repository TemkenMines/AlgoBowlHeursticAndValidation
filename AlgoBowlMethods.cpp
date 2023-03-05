#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "AlgoBowlMethods.h"

using namespace std;

void print_made_numbers(const vector<int>&, const int[], const string&);

int bad_guarantee_simple(int n, const int numbersIn[]) {
    return numbersIn[n - 1] - 1;
}

pair<int, vector<pair<int, int>>> bad_guarantee(int n, const int numbersIn[]){
    int additions = 1, *hold = new int(numbersIn[n - 1] - 1);
    vector<pair<int, int>> steps = {{1, 1}};

    while(additions < *hold){
        additions++;
        steps.emplace_back(steps.back().first + 1, 1);
    }
    delete hold;
    return {additions, steps};
}

pair<int, vector<pair<int, int>>> heuristic_run(int n, const int numbersIn[], const string &fileNum){
    int additions = 1;
    vector<pair<int, int>> steps = {{1, 1}};
    vector<int> numbersMade = {1, 2};

    int i = 0;
    if(numbersIn[0] == 2){
        i++;
    }

    int diff;
    while(i < n){
        diff = numbersIn[i] - numbersMade.back();

        for(int j = numbersMade.size() - 1; j >= 0; j--){
            if(numbersMade[j] == diff){
                steps.emplace_back(numbersMade.back(), numbersMade[j]);
                numbersMade.emplace_back(numbersMade.back() + numbersMade[j]);
                additions++;
                i++;
                break;
            }else if(numbersMade[j] < diff){
                steps.emplace_back(numbersMade.back(), numbersMade[j]);
                numbersMade.emplace_back(numbersMade.back() + numbersMade[j]);
                additions++;
                break;
            }
        }
    }

    print_made_numbers(numbersMade, numbersIn, fileNum);
    return {additions, steps};
}

void print_made_numbers(const vector<int> &numbersMade, const int numbersIn[], const string &fileNum){
    int i = 0;
    ofstream outNums;
    outNums.open("numbersMade/nums_made_group" + fileNum + ".txt");
    for(int iter: numbersMade){
        if(iter == numbersIn[i]){
            outNums << iter << '*' << endl;
            i++;
        }else{
            outNums << iter << endl;
        }
    }
    outNums.close();
}

int heuristic_run_file_manage(const string &fileNum){
    ifstream in;
    int *n = new int;
    in.open("inputs/input_group" + fileNum + ".txt");
    if(in.fail()){
        cerr << "File 'inputs/input_group" + fileNum + ".txt" << "' not found" << endl;
        return -1;
    }

    in >> *n;
    auto numbersIn = new int[*n];
    for(unsigned int i = 0; i < *n; i++){
        if(in.eof()){
            cerr << "input file contains less than " << *n << " numbers" << endl;
            delete[] numbersIn;
            delete n;
            in.close();
            return -1;
        }
        in >> numbersIn[i];
    }
    in.close();

    pair<int, vector<pair<int, int>>> solution = heuristic_run(*n, numbersIn, fileNum);

    ofstream outFile;
    outFile.open("outputs/output_group" + fileNum + ".txt");

    if(outFile.fail()){
        cerr << "open failure on 'outputs/output_group" + fileNum + ".txt'" << endl;
        delete n;
        delete[] numbersIn;
        return -1;
    }

    outFile << solution.first << endl;
    for(pair<int, int> iter: solution.second){
        outFile << iter.first << " " << iter.second << endl;
    }
    outFile.close();

    delete[] numbersIn;
    delete n;
    return 0;
}

bool report_valid_out(const string &fileNum){
    ifstream in;
    int n;
    in.open("/inputs/input_group613.txt");
    in >> n;
    auto numbersIn = new int[n];
    for(unsigned int i = 0; i < n; i++){
        in >> numbersIn[i];
    }
    in.close();

    ifstream in2;

    in2.open("/verification_outputs/output_from_" + fileNum + "_to_613.txt");
    int additions;
    in2 >> additions;
    pair<int, int> currentStep;
    vector<int> numbersMade = {1};
    for(unsigned int i = 0; i < additions; i++){
        if(in2.eof()){
            in2.close();
            delete[] numbersIn;
            cerr << "File has fewer additions than reported" << endl;
            return false;
        }
        in2 >> currentStep.first;
        in2 >> currentStep.second;
        if(!binary_search(numbersMade.begin(), numbersMade.end(), currentStep.first) ||
            !binary_search(numbersMade.begin(), numbersMade.end(), currentStep.second)){
            in2.close();
            delete[] numbersIn;
            cerr << "addition used number not previously made" << endl;
            return false;
        }
        numbersMade.emplace_back(currentStep.first + currentStep.second);
        sort(numbersMade.begin(), numbersMade.end());
    }
    in2.close();

    int j;
    for(unsigned int i = 0; i < n; i++){
        for(j = 0; j < numbersMade.size(); j++){
            if(numbersMade[j] > numbersIn[i]){
                cerr << "Number not made: " << numbersIn[i] << " | wrapped: " << numbersMade[j - 1] << ", "
                     << numbersMade[j] << endl;
                delete[] numbersIn;
                return false;
            }
            if(numbersMade[j] == numbersIn[i]){
                i++;
                break;
            }
        }
    }
    return true;
}
