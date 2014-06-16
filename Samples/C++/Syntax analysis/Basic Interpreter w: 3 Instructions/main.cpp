//
//  main.cpp
//  BASIC INTERPRETER
//
//  Created by Pierre van Houtryve on 15/06/14.
//  Copyright (c) 2014 Pierre van Houtryve. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
using namespace std;

void analyze(string line,int linenum)
{
    string print = "print:'"; // Print in console
    string cin = "getline+sprint;"; // Get user input and print it
    string slp = "sleepms:"; // Sleep in MS
    string ffos = "Unknown syntax";
    for (int k = 0;k<=line.size();k++) {
        //Char-Char Syntax reading
        //ffos = help to know where the problem happened
        //linenum help to debug
        //The rest is checking if the character is the last one like ':' or ';' so i know that the line is completed
        //(c) Pierre van Houtryve 2014 - Open source,free to use, it's a basic interpreter
        if(line[k]==print[k])
        {
            ffos="Print instruction";
            if(line[k]==':')
            {
                if(line[line.length()-1]==';'){
                    ffos="Print instruction, no ';' ";
                    //Line Confirmed
                    size_t kx;
                    string m = line;
                    m.pop_back();
                    kx = m.find("&n");
                while(kx!=string::npos)
                    {
                        kx = m.find("&n");
                        if(kx!=string::npos)
                        {
                            m.replace(kx,2,"\n");
                        }
                    }
                            cout << m.substr(k+1,(m.size()-k));
                            break;
                }
            }
        }
        else if(line[k]==cin[k])
        {
                ffos="Getline instruction";
                string m;
                getline(std::cin,m);
                cout << m << endl;
                break;
        }
        else if(line[k]==slp[k])
        {
            ffos="Sleep instruction";
            if(line[k]==':')
            {
                string val=line.substr(k+1,line.length()-1);
                ostringstream txk(val);
                float z = atoi(val.c_str());
                z = z/1000;
                sleep(z);
            break;
            }
        }
        else
        {
            cout << "Incorrect syntax at line " << linenum << " ->  " << ffos << endl;
            break;
        }
    }
    
}

int main(int argc, const char * argv[])
{
    ifstream storm;
    string fpath = "tk.storm";
    storm.open(fpath);
    string jk;
    int k;
    if(storm.is_open())
    {
        while(getline(storm,jk))
        {
            k++;
            analyze(jk,k);
        }
    }
    else{
        cout << "Unable to open " << fpath << endl;
    }
    return 0;
}
