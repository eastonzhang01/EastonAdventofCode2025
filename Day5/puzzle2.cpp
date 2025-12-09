#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <functional>
#include <set>
#include <sstream>

using namespace std;

bool consolidate_low(vector<unsigned long long>& range_list, int low_position){
    if(low_position>0){
        return false;
    }
    int prev_high = low_position-1;
    // should only need to consolidate low once at most

    // we need to adjust
    if(range_list[prev_high]>=range_list[low_position]){
        range_list[prev_high] = range_list[low_position]-1;
        return true;
    }
    return false;
}

bool consolidate_high(vector<unsigned long long>& range_list, int high_position){
    if(high_position==range_list.size()-1){
        return false;
    }
    int next_low = high_position+1;
    int next_high = high_position+2;

    // only need to consolidate once
    if(range_list[high_position] >= range_list[next_low] && range_list[high_position] <= range_list[next_high]){
        range_list[high_position] = range_list[next_low]-1;
        return true;
    }
    else if(range_list[high_position] >= range_list[next_low] && range_list[high_position] > range_list[next_high]){
        unsigned long long temp = range_list[high_position];
        range_list[high_position] = range_list[next_low]-1;
        range_list[next_high] = temp;
        return consolidate_high(range_list, next_high);
    }
    return false;
}

int main() {
    ifstream inputFile("puzzle_input.txt");

    if(!inputFile.is_open()){ // or can do inputFile.fail()
        cout<<"Error: Could not open file"<<endl;
        return 1;
    }
    string line;
    getline(inputFile, line);

    //vector<unsigned long long> low_nums;
    //vector<unsigned long long> high_nums;

    vector<unsigned long long> range_list;
    unsigned long long num_fresh=0;
    while(line != ""){
        stringstream ss(line);
        char delimiter='-';

        string low_num;
        string high_num;

        getline(ss, low_num, delimiter);
        getline(ss, high_num);
        unsigned long long low = stoull(low_num);
        unsigned long long high = stoull(high_num);

        cout<<"-----Processing range: "<<low<<" | "<<high<<endl;

        bool found_overlap = false;
        for(int i=0; i<range_list.size(); ++i){

            if(i%2==0){//this means we are looking at a low number
                unsigned long long compare_low = range_list[i];
                unsigned long long compare_high = range_list[i+1];

                // new range fully bigger
                if(low<compare_low && high>compare_high){
                    cout<<"Found new range fully bigger: "<<low<<" < "<<compare_low<<" and "<<high<< " > "<<compare_high<<endl;
                    range_list[i] = low;
                    range_list[i+1] = high;
                    found_overlap=true;
                    consolidate_low(range_list, i);
                    consolidate_high(range_list, i+1);
                    break;
                }
                // new range partial overlap on the lower side
                else if(low<compare_low && high>=compare_low && high<=compare_high){
                    cout<<"Found lower partial overlap: "<<low<<" < "<<compare_low<<" and "<<high<< " >= "<<compare_low<<" and "<<high<<" <= "<<compare_high<<endl;
                    range_list[i] = low;
                    found_overlap=true;
                    consolidate_low(range_list, i);
                    break;
                }
                // new range partial overlap on the high side
                else if(high>compare_high && low<=compare_high && low>=compare_low){
                    cout<<"Found higher partial overlap: "<<high<<" > "<<compare_high<<" and "<<low<< " <= "<<compare_high<<" and "<<low<<" >= "<<compare_low<<endl;
                    range_list[i+1] = high;
                    found_overlap=true;
                    consolidate_high(range_list, i+1);
                    break;
                }
                // new range is fully smaller
                else if(low>=compare_low && high<=compare_high){
                    cout<<"Found new range fully smaller: "<<low<<" >= "<<compare_low<<" and "<<high<< " <= "<<compare_high<<endl;
                    found_overlap=true;
                    break;
                }
            }
            
        }

        if(!found_overlap){
            cout<<"Didn't find any overlap inserting and sorting"<<endl;
            range_list.push_back(low);
            range_list.push_back(high);
            sort(range_list.begin(), range_list.end());
        }

        cout<<"Current Range list: "<<endl;
        for(int i=0; i<range_list.size(); ++i){
            if(i%2==0){
                cout<<range_list[i]<<" : "<<range_list[i+1]<<endl;
            }
        }
        getline(inputFile, line);
    }
    inputFile.close();

    // calculate at the end
    for(int i=0; i<range_list.size(); i+=2){
        //cout<<range_list[i]<<" : "<<range_list[i+1]<<endl;
        cout<<"Adding: "<< (range_list[i+1]-range_list[i]+1)<<" for range: "<<range_list[i]<< " : "<<range_list[i+1]<<endl;
        num_fresh+=(range_list[i+1]-range_list[i]+1);
    }

    
    cout<<num_fresh<<endl;
    return 0;
}