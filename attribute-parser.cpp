#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <unordered_map>

using namespace std;

struct tag
{
    string tag_name; // name of the tag
    unordered_map<string,string> attr; // map for attribute and values
    string parents;
};

char *parser(string hrmLine)
{
    if(hrmLine[1] == '/')
    {
        char *closeTag = "EOL";

        return closeTag;
    }
    else if (hrmLine.length() == 0)
    {
        return nullptr;
    }

    else
    {
        char *chrmLine = new char[hrmLine.length() + 1] ;

        strcpy(chrmLine, hrmLine.c_str());

        char* p = strtok(chrmLine," <>\"");

        return p;
    }
}
int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n,q;
    cin>>n>>q;
    unordered_map<string,tag> hrmParse;
    string line;
    vector<string>tags_queue;
    tag temp;
    bool nested = true;
    int base_nested = 0;

    getline(cin,line);
    for(int i =0; i<n; i++)
    {
        tag hrm_tag;
        getline(cin,line);
        if (parser(line) != nullptr && parser(line) != "EOL")
        {
            nested = true;
            char *p_to_cstring = parser(line);
            int tag_flag = 0;
            bool value = false;
            string tag_att;
            string tag_value;
            while (p_to_cstring != NULL)
            {
                if (tag_flag == 0)
                {
                    hrm_tag.tag_name = p_to_cstring;
                    tags_queue.push_back(hrm_tag.tag_name);
                    tag_flag +=1;
                }
                else
                {
                    if(strcmp("=",p_to_cstring)== 0)
                    {
                        value = true;
                    }
                    else if(value == false)
                    {
                        tag_att = p_to_cstring;

                    }
                    else
                    {
                        tag_value = p_to_cstring;
                        hrm_tag.attr.insert({tag_att,tag_value});
                        value = false;
                    }
                }
                p_to_cstring = strtok(NULL," <>\"");
            }
            
            if (tags_queue.size() >= 2) {
                hrm_tag.parents = hrmParse[*(tags_queue.end()-2)].parents + *(tags_queue.end()-2);
            }
            hrmParse.insert({hrm_tag.tag_name,hrm_tag});
        }
        else if(parser(line) == "EOL")
        {
            tags_queue.pop_back();
        }
    }
    
    for (int j = 0 ; j < q; j++)
    {
        vector<string>query;
        getline(cin,line);
        string query_string="";
        char *queryLine = new char[line.length()-1];
        strcpy(queryLine, line.c_str());
        char *q_pointer = strtok(queryLine, ".~");
        tag next_tag = hrmParse[q_pointer];
        
        while(q_pointer!=NULL){
            query.push_back(q_pointer);
            q_pointer = strtok(NULL, ".~");
        }
        
        for (auto it = query.begin() ; it!=query.end()-2; it++) {
            next_tag = hrmParse[*it];
            query_string += *it;
        }
        
        next_tag = hrmParse[*(query.end()-2)];
        string value = next_tag.attr[*(query.end()-1)];
        
        if (next_tag.parents!="" && next_tag.parents == query_string) {
            cout<<((value == "")?"Not Found!":value)<<endl;
        }else if(next_tag.parents == ""){
            cout<<((value == "")?"Not Found!":value)<<endl;
        }else {
            cout<<"Not Found!"<<endl;
        }
    }
    return 0;
}


