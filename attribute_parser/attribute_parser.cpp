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
    set<Tag*> subtags;
public:
    Tag(map<string, string>* att) {
        attributes = att;
        //subtags = NULL;
    }
    void setAttributes(map<string, string>* attr) {
        attributes = attr;
    }
    void addSubtag(Tag* st) {
        subtags.insert(st);
    }
    map<string, string>* getAttributes() {
        return attributes;
    }
    set<Tag*> getSubtags() {
        return subtags;
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
    stack<Tag*> S; // Use pointers because it's easier to push and pop pointers than whole classes.
    cin.ignore(); // This is required I dont know why
    while (N--) {
        string str; // For handling content

        // Obtain line by line
        getline(cin, str);
        str = str.substr(1, str.size() - 2); // Clip the < > at the extremes

        if (str[0] == '/') { // THis block should never run in the first iteration
            // If the line is a tag ender, first check whether this is a subtag of some other
            // This by checking there is only 1 tg in the stack
            // If that's the case, add the nested tag to the father
            if (S.size() > 1) {
                Tag* temp = S.top();
                cout << "Size of stack " << S.size() << endl;
                S.pop();
                S.top()->addSubtag(temp);
            }
        } else {
            // Use stringstream to obtain the differnt variables in the line
            map<string, string> attributes;
            pair<string, string> p;

            stringstream ss(str);
            string name, ch;
            ss >> name; 
            // Get attributes and names (remember retunrs false when there is nothing) and populate the map
            while (ss >> p.first >> ch >> p.second) { 
                p.second = p.second.substr(1, p.second.size() - 2);
                attributes.insert(p); 
            }
            // CONSIDER HERE GET RID OF ATTRIBUTES INTERMEDIATE VARIALBE AND
            // USE tag.insertAttribute() *******************************************************
            Tag tag(&attributes); // Build current tag with corresponding attributes
            S.push(&tag); // Add it to the stack

            // Here we just print the variables for checking
            cout << "Name " << name << endl;
            cout << "Size of attributes " << S.top()->getAttributes()->size() << endl;
            for (map<string, string>::iterator it = S.top()->getAttributes()->begin(); it != S.top()->getAttributes()->end(); it++) {
                cout << "Attribute called " << it->first << " with value " << it->second << endl;
            }
        }
    }

    // Print some nested classes manually


    return 0;
}
/* For checking use <tag3 another = "another_value" final = "final_value"> 
* 
<tag3 another = "another" final = "final">
</tag3>

<tag2 name = "name">
<tag3 another = "another" final = "final">
</tag3>
</tag2>


*/