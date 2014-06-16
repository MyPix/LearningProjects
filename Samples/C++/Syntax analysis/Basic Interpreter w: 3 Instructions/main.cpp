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

inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

void analyze(string line,int linenum)
{
    string print = "print:'";
    string cin = "getline+sprint;";
    string slp = "sleepms:";
    string writin = "write%";
    string prtfile = "sprint: %file:";
    string ffos = "Unknown syntax";
    for (int k = 0;k<=line.size();k++) {
        //Char-Char Syntax reading
        //ffos = help to know where the problem happened
        //linenum help to debug
        //The rest is checking if the character is the last one like ':' or ';' so i know that the line is completed
        //(c) Pierre van Houtryve 2014 - Open source,free to use, it's a basic interpreter
        trim(line);
        size_t cmt = line.find("&//");
        if(cmt != string::npos) // If contains comment (comment = &//), clears it.
        {
                line = line.substr(0,cmt-1);
                trim(line);
        }
        if(line[k]==print[k])
        {
            ffos="Print instruction";
            if(line[k]==':')
            {
                if(line[line.length()-1]==';'){
        
                    //Line Confirmed
                    size_t kx;
                    string m = line;
                    m.pop_back();
                    if(m.find("%file:") != string::npos)
                    {
                        size_t jk = m.find("%file:");
                        jk+=6;
                        m = m.substr(jk,(m.length()-jk));
                        trim(m);
                        ifstream kstr(m);
                        if(kstr.is_open())
                        {
                            string cont;
                            string topprint;
                            while(getline(kstr,cont))
                            {
                                topprint+=cont;
                                topprint+="\n";
                            }
                            cout << topprint;
                        }
                        else
                        {
                            cout << "The file" << m << "does not exists" << endl;
                        }
                    }
                    else
                    {
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
                    }
                            break;
                }
                else
                {
                    ffos="Print instruction, no ';' ";
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
                if(line[line.length()-1]==';')
                {
                    string val=line.substr(k+1,line.length()-1);
                    ostringstream txk(val);
                    float z = atoi(val.c_str());
                    z = z/1000;
                    sleep(z);
                }
            break;
            }
        }
        else if(line[k]==writin[k])
        {
            ffos="Write instruction";
            if(line[k]=='%')
            {
                if(line[line.length()-1]==';')
                {
                    if(line.find('@')!=string::npos)
                    {
                        // Line is ok
                        string toprint;
                        string towhat;
                        size_t a,b,c;
                        a=line.find('%');
                        b=line.find('@');
                        c=line.find(';');
                        toprint = line.substr(a+1,(b-a));
                        towhat = line.substr(b+1,(line.length()-b));
                        trim(towhat);
                        towhat.pop_back(); // Clearing ;
                        trim(toprint);
                        ofstream k(towhat);
                        if(k.is_open()){
                            if(toprint.substr(0,7)=="%input%")
                            {
                                cout << "Enter something to write in " << towhat << " :";
                                string mpk;
                                getline(std::cin,mpk);
                                toprint=mpk;
                                trim(toprint);
                                k << toprint;
                                cout << "Wrote" << endl << "----" << endl << toprint << endl << "----" << endl << "in " << towhat << endl << endl;
                            }
                            else
                            {
                                size_t kx;
                                string m = toprint;
                                m.pop_back();
                                kx = m.find("&n");
                                while(kx!=string::npos)
                                {
                                    kx = m.find("&n");
                                    if(kx!=string::npos)
                                    {
                                        m.replace(kx,2,"\n");
                                        trim(m);
                                    }
                                }
                                k << m;
                                cout << "Wrote" << endl << "----" << endl << m << endl << "----" << endl << "in " << towhat << endl << endl;
                            }
                            
                        }
                        else
                        {
                            cout<<"FILE DOES NOT EXIST" << endl;
                        }
                        break;
                    }
                    else
                    {
                        ffos="Write instruction - No '@' to mark the name of the file";
                        cout << "Incorrect syntax at line " << linenum << " ->  " << ffos << endl;
                        break;
                    }
                }
                else
                {
                    ffos="Write instruction - No ';' at the end";
                    cout << "Incorrect syntax at line " << linenum << " ->  " << ffos << endl;
                    break;
                }
            }
        }
        else if(line[k]==' ')
        {
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
    string fpath = "/Users/pierre/Desktop/Dev C++/Storm/Storm/tk.storm";
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
        cout << "Unable to open " << fpath;
    }
    return 0;
}
