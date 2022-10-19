#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
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

string search(string query, map<string, Tag>* O) {
    string ch, print, print2, print3;
    queue<string> q;
    stringstream ss(query);
    while (getline(ss, print, '.')) {
        stringstream ss2(print);
        getline(ss2, print2, '~');
        q.push(print2);
        getline(ss2, print3, '~');
        if (print3.size() > 0) {
            q.push(print3);
        }
    }
    Tag current;
    current = (*O)[q.front()];
    while (q.size() > 2) {
        q.pop();
        Tag temp = current.subtags[q.front()];
        current = temp;
    }
    q.pop();
    return current.attributes[q.front()];
}


int main() {
    int N, Q; // N lines, Q queries
    cin >> N >> Q;

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
            if (S.size() > 1) {
                Tag t;
                t = S.top();
                S.pop();
                S.top().subtags.insert(make_pair(name, t));
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
            Tag tag;
            tag.attributes = att;
            S.push(tag); // Add it to the stack
        }
    }
    string query;
    
    while (Q--) {
        cin >> query;
        string output = search(query, &O);
        if (output.size() > 0)
            cout << output << endl;
        else
            cout << "Not Found!" << endl;
    }
    
    return 0;
}
/* Some test cases
1
<tag3 another = "another" final = "final">
</tag3>

4
<tag2 name = "name">
<tag3 another = "another" final = "final">
</tag3>
</tag2>

12 2
<tag1 value = "value">
<tag2 name = "name">
</tag2>
<tag3 another = "another" final = "final">
</tag3>
</tag1>
<tag4 value = "value4">
<tag5 name = "name5">
<tag6 another = "another6" final = "final6">
</tag6>
</tag5>
</tag4>
tag4.tag5.tag6~another
tag1.tag3~final
*/