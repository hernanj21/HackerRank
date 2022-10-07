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
private:
    map<string, string>* attributes;
    set<Tag*>* subtags;
public:
    Tag(map<string, string>* att) {
        attributes = att;
        subtags = NULL;
    }
    void setAttributes(map<string, string>* attr) {
        attributes = attr;
    }
    void addSubtag(Tag* st) {
        subtags->insert(st);
    }
};


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N, Q; // N lines, Q queries
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
    stack<Tag> S;
    cin.ignore(); // This is required I dont know why
    while (N--) {
        map<string, string> attributes;
        pair<string, string> p;
        string str, ch; // For handling content

        // Obtain line by line
        getline(cin, str);
        str = str.substr(1, str.size() - 2); // Clip the < > at the extremes

        if (str[1] == '/') {
            // If the line is a tag ender, first check whether this is a subtag of some other
            // This by checking there is only 1 tg in the stack
            // If that's the case, add the nested tag to the father
            if (S.size() > 1) {
                Tag temp = S.top();
                S.pop();
                S.top().addSubtag(&temp);
            }

        } else {
            // Use stringstream to obtain the differnt variables in the line
            stringstream ss(str);
            string name;
            ss >> name; // Get tag name
            while (ss >> p.first >> ch >> p.second) { // Get attributes and names (remember retunrs false when there is nothing)
                p.second = p.second.substr(1, p.second.size() - 2);
                attributes.insert(p); // Populate the map
            }

            // Here we just print the variables for checking
            cout << "Name " << name << endl;
            for (map<string, string>::iterator it = attributes.begin(); it != attributes.end(); it++) {
                cout << "Attribute called " << it->first << " with value " << it->second << endl;
            }

            // Insert
            // If the next line is a new tag do something, if it´s a closing one do something else
            // If next line is closing, pop, update N
            // If not, go to next line (start the cicle again)
        }
    }
    return 0;
}