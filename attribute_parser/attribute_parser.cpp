#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

class Tag {
public:
    map<string, string> attributes;
    map<string, Tag> subtags;
};


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N; // N lines, Q queries
    cin >> N;

    // Create a stack, we will work in the elemment on the top always, and when we find the end, insert it
    // to the element containing it (second from top to bottom) and discard the top.


    // do while(stack.size() > 0)? No because maybe there are subsequent stacks (1 on top of the other),
    // and then I wont be able to read th second one. I have to stop based on N
    // Probably I have to use both with a boolean operator.
    // I think not

    // (TO DO) Read tag name and attributes, insert attributes
    // Here we are populating the class. Consider moving this to a function later
    // 
    // We use a stack to be able to keep track of the previously handled tag and nest correctly
    stack<Tag> S; // Use pointers because it's easier to push and pop pointers than whole classes.
    map<string, Tag> O; // Outer tags
    cin.ignore(); // This is required I dont know why
    while (N--) {
        string str; // For handling content

        // Obtain line by line
        getline(cin, str);
        str = str.substr(1, str.size() - 2); // Clip the < > at the extremes        
        
        if (str[0] == '/') {
            string name = str.substr(1, str.size() - 1);
            cout << "TAG NAME = " << name << endl;
            if (S.size() > 1) {
                Tag t;
                t = S.top();
                S.pop();
                cout << "Inserting " << name << " with " << t.attributes.size() << " attributes" << endl;
                //cout << "Size before inserting: " << S.top().subtags.size() << endl;
                S.top().subtags.insert(make_pair(name, t));
                //cout << "Size after inserting: " << S.top().subtags.size() << endl;
            }
            else { 
                // The tag is outer if the size is = 1 and then it goes to the outer map because
                // they are not contained by anyone
                O.insert(make_pair(name, S.top()));
                S.pop();
            }
        }
        else {
            // Use stringstream to obtain the differnt variables in the line
            map<string, string> att;
            pair<string, string> p;

            stringstream ss(str);
            string name, ch;
            ss >> name;
            // Get attributes and names (remember retunrs false when there is nothing) and populate the map
            while (ss >> p.first >> ch >> p.second) {
                p.second = p.second.substr(1, p.second.size() - 2);
                att.insert(p);
            }

            // CONSIDER HERE GET RID OF ATTRIBUTES INTERMEDIATE VARIALBE AND
            // USE tag.insertAttribute() *******************************************************
            Tag tag;
            tag.attributes = att;
            S.push(tag); // Add it to the stack

            // Here we just print the variables for checking
            cout << "Name " << name << endl;
            cout << "Size of attributes " << S.top().attributes.size() << endl;
            for (map<string, string>::iterator it = S.top().attributes.begin(); it != S.top().attributes.end(); it++) {
                cout << "Attribute called " << it->first << " with value " << it->second << endl;
            }
        }
    }
    cout << endl << endl;
    // Print some nested classes manually
    // tag1.tag2~name:
    cout << "tag1.tag2~name = " << O["tag1"].subtags["tag2"].attributes["name"] << endl;
    // string attee = O["tag1"].subtags["tag3"]->attributes["final"];
    cout << endl << endl;
    cout << "Number of Tag1 subtags: " << O["tag1"].subtags.size() << endl;
    
    map<string, Tag> sts = O["tag1"].subtags;
    for (map<string, Tag>::iterator iter = sts.begin(); iter != sts.end(); iter++) {
        cout << "Subtag called " << iter->first << endl;
        cout << "with " << iter->second.attributes.size() << " attributes: ..." << endl;
        for (map<string, string>::iterator ite = iter->second.attributes.begin(); ite != iter->second.attributes.end(); ite++) {
            cout << "Attribute called " << ite->first << " with value " << ite->second << endl;
        }
        cout << endl << endl;
    }
    return 0;
}
/* For checking use <tag3 another = "another_value" final = "final_value"> 
* 
1
<tag3 another = "another" final = "final">
</tag3>

4
<tag2 name = "name">
<tag3 another = "another" final = "final">
</tag3>
</tag2>

6
<tag1 value = "value">
<tag2 name = "name">
</tag2>
<tag3 another = "another" final = "final">
</tag3>
</tag1>


*/