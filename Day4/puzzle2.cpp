#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <functional>
#include <set>

using namespace std;

int check_char_is_roll(char roll_character){
    if(roll_character=='@'){
        return 1;
    }
    return 0;
}

int check_above_below_line(vector<char> line, int pos){
    int roll_count=0;
    // if size is 0 we don't have any roll counts
    if(line.size()!=0){
        // always check the one above
        roll_count+=check_char_is_roll(line[pos]);

        // check top left is accessible
        if(pos!=0){
            roll_count+=check_char_is_roll(line[pos-1]);
        }
        // check right
        if(pos!=line.size()-1){
            roll_count+=check_char_is_roll(line[pos+1]);
        }
    }
    return roll_count;
}

int remove_rolls(vector<vector<char>>& total_paper_rolls){
    unsigned long long accessible_rolls_count=0;

    for(int i=0; i<total_paper_rolls.size(); ++i){
        vector<char> roll_line = total_paper_rolls[i];
        vector<char> line_above = vector<char>();
        vector<char> line_below = vector<char>();

        if(i!=0){
            line_above = total_paper_rolls[i-1];
        }
        if(i!=total_paper_rolls.size()-1){
            line_below = total_paper_rolls[i+1];
        }

        for(int j=0; j<roll_line.size(); ++j){
            if(roll_line[j]=='@'){
                int adj_rolls_count = 0;
                // look at top
                adj_rolls_count+=check_above_below_line(line_above, j);
                // look below
                adj_rolls_count+=check_above_below_line(line_below, j);
                // look left and right
                // check top left is accessible
                if(j!=0){
                    adj_rolls_count+=check_char_is_roll(roll_line[j-1]);
                }
                // check right
                if(j!=roll_line.size()-1){
                    adj_rolls_count+=check_char_is_roll(roll_line[j+1]);
                }
                // Add to the accessible rolls if adj < 4
                if(adj_rolls_count<4){
                    accessible_rolls_count++;
                    total_paper_rolls[i][j]='.';
                    cout<<'X';
                }
                else{
                    cout<<roll_line[j];
                }
            }
            else{
                cout<<roll_line[j];
            }
        }
        cout<<endl;
    }
    cout<<accessible_rolls_count<<endl;
    return accessible_rolls_count;
}

int main() {
    ifstream inputFile("puzzle_input.txt");

    if(!inputFile.is_open()){ // or can do inputFile.fail()
        cout<<"Error: Could not open file"<<endl;
        return 1;
    }
    string line;
    vector<vector<char>> total_paper_rolls;

    while(getline(inputFile, line)){
        vector<char> paper_rolls_line;
        for(int i=0; i<line.size(); ++i){
            paper_rolls_line.push_back(line[i]);
        }
        total_paper_rolls.push_back(paper_rolls_line);
    }
    /*
    for(int i=0; i<total_paper_rolls.size(); ++i){
        for(int j=0; j<total_paper_rolls[i].size(); ++j){
            cout<<total_paper_rolls[i][j];
        }
        cout<<endl;
    }
        */

    int final_removal_count = 0;

    int latest_removal = remove_rolls(total_paper_rolls);

    while(latest_removal!=0){
        final_removal_count+=latest_removal;
        latest_removal = remove_rolls(total_paper_rolls);
    }

    cout<<"Final Removal Amount: "<<final_removal_count<<endl;
    return 0;
}