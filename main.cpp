#include <iostream>
#include <fstream>
#include <vector>
#include "table.h"
#include <algorithm>
#include <sstream>
using namespace std;

int main()
{
//table which holds all results
    table<string, 10000000> t;

    //Reads dictionary file
    ifstream dictionaryfile;
    dictionaryfile.open ("words.txt");
    if(dictionaryfile.fail())
    {
        cout<<"dictionary fail"<<endl;
    }
    string temp;
    while(getline(dictionaryfile, temp)){
            transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
            t.insert(temp);
    }
    //copy of the grid
    ifstream puzzlefile;
    puzzlefile.open ("puzzle.txt");

    if(puzzlefile.fail())
    {
        cout<<"puzzle fail"<<endl;
    }

    //each string is entire row
    //grid [i][j]
    //each row contains spaces. so remove spaces

    vector <string> grid;
    while(getline(puzzlefile,temp))
    {
        string gridRow;
        istringstream istream(temp);
        char c;
        while(istream>>c)
        {
            gridRow += c;
        }
        grid.push_back(gridRow);
    }

    vector<pair <string, pair <pair<int, int>, pair<int, int>>>> dataception;

    for(int i=0; i<grid.size(); i++)
    {
            for(int j=0; j<grid[i].size(); j++)
            {
                for(int x=1; x<=8; x++)
                {
                    int vertStep(0), horStep(0);
                    switch (x){
                        case 1:
                        //North
                            horStep=0;
                            vertStep=-1;
                            break;
                        case 2:
                        //NorthEast
                            horStep=1;
                            vertStep=-1;
                            break;
                        case 3:
                        //East
                            horStep=1;
                            vertStep=0;
                            break;
                        case 4:
                        //SouthEast
                            horStep=1;
                            vertStep=1;
                            break;
                        case 5:
                        //South
                            horStep=0;
                            vertStep=1;
                            break;
                        case 6:
                        //Southwest
                            horStep=-1;
                            vertStep=1;
                            break;
                        case 7:
                        //West
                            horStep=-1;
                            vertStep=0;
                            break;
                        case 8:
                        //NorthWest
                            horStep=-1;
                            vertStep=-1;
                            break;
                    }
                    string check;
                    for(int a=i, b=j;
                        (a>= 0 && a<grid.size())&& (b>= 0 && b< grid[a].size()); a +=horStep, b+=vertStep){
                        check+=grid[a][b];
                        if(t.find(check) && check.size() >= 6){
                            pair<int, int> initialCoordinates(i+1, j+1);
                            pair<int, int> currentCoordinates(a+1, b+1);
                            pair<pair<int, int>, pair<int, int>> startFin(initialCoordinates, currentCoordinates);
                            dataception.push_back(pair<string, pair<pair<int, int>, pair<int, int>>> (check, startFin));
                            //cout<< check <<" at("<<i+1<<", "<<j+1<<") to ("<<a+1<<", "<<b+1<<")"<<endl;
                        }
                    }
                }
              }

    }
    sort(dataception.begin(), dataception.end());
    for(int i = 0; i<dataception.size(); i++){
        pair<string, pair<pair<int, int>, pair <int, int>>> info = dataception.at(i);
        pair<int, int> start = info.second.first;
        pair<int, int> finish = info.second.second;
        cout<< info.first << " at (" << start.first<< ", "<< start.second << ") to (" <<finish.first<< ", "<< finish.second << ")"<<endl;
    }
    return 0;
 }


