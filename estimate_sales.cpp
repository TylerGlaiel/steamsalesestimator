//Code by Tyler Glaiel
//usage: "estimate_sales [achievement percentage 1] [achievement percentage 2]..."
//optional arguments: -search_start, -search_end, -max_results
//Compile to an executable. Works with -O3 on gcc just fine

#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;

bool trialdivision(double percent, int denom, int num_range = 5){
    bool match = false;
    int range_min = (denom * (percent)/100)-num_range;
    int range_max = (denom * (percent)/100)+num_range;
    if(range_min < 0) range_min = 0;

    for(int num = range_min; num<range_max; num++){
        double div = (double)((float)num/denom*100);
        if(div==percent) {
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv){
    int search_start = 0;
    int search_end = 100000000;
    int max_results = 1;
    std::vector<double> percents;
    
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-search_start")==0){
            i++;
            search_start = atoi(argv[i]);
        } else if(strcmp(argv[i], "-search_end")==0){
            i++;
            search_end = atoi(argv[i]);
        } else if(strcmp(argv[i], "-max_results")==0){
            i++;
            max_results = atoi(argv[i]);
        } else {
            percents.push_back(atof(argv[i]));
        }
    }

    bool found = false;
    for(int denominator = search_start; denominator<search_end; denominator++){
        bool denom_possible = true;
        for(int i = 0; i<percents.size(); i++){
            if(!trialdivision(percents[i], denominator)){
                denom_possible = false;
                break;
            }
        }
        
        if(denom_possible) {
            cout << denominator << endl;
            found = true;
            if(--max_results <= 0) return 0;
        }
    }
    if(!found) cout << 0 << endl;
    return 0;
}
