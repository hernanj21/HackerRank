#include <map>
#include<iostream>
template<typename K, typename V>
//Get the types for the interval map template
class interval_map {
	friend void IntervalMapTest();
	V m_valBegin; // Value for all the keys lower than the first one in m_map
	std::map<K, V> m_map;
public:
	// constructor associates whole range of K with val
	interval_map(V const& val)
		: m_valBegin(val) // This initialises the variable mvalBegin in the constructor
	{}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign(K const& keyBegin, K const& keyEnd, V const& val) {
		// INSERT YOUR SOLUTION HERE
		// Iterators to closest values to keyBegin and keyEnd
		if (keyBegin < keyEnd) {
			auto ub = m_map.upper_bound(keyBegin);
			auto lb = m_map.lower_bound(keyEnd);

			if (lb == m_map.begin()) {
				// This is true when m_map is empty or when keyEnd is lower than the lowest one in m_map
				m_map.insert({ keyBegin, val });
				m_map.insert({ keyEnd, m_valBegin });
			}
			else {
				V valEnd = (--lb)->second; // Store value for the next interval before operating

				bool check; // This checks whether keyBegin already exists iwhtout using find()
				if (ub == m_map.begin()) {
					check = false;
					m_map.erase(ub, ++lb); // Delete intervals covered by the newly assigned
				}
				else {
					check = ((--ub)->first == keyBegin);
					m_map.erase(++ub, ++lb);
				}

				if (check) {
					m_map[keyBegin] = val; // Just replace if the key exists
				}
				else {
					m_map.insert({ keyBegin, val });
				}

				m_map.insert({ keyEnd, valEnd });
			}
		}
	}

	// look-up of the value associated with key
	V const& operator[](K const& key) const {
		auto it = m_map.upper_bound(key); // Get an iterator pointing to the next key just greater than k
		// Here the argument key might not be an existing key
		// If the key is greater thatn the largest one it points to .end()
		if (it == m_map.begin()) { // If the inserted key is lower than the first one then this holds
			// And then I should return the begin value
			// If the set is empty we return begin (=end()) because when no key is considered to go after
			// k we return map.end()
			return m_valBegin;
		}
		else {
			// If not, then i should return the value below that one, thats the reason for the --
			// Perform -- and return the value (second in the pair)
			// If for example i insert 6 and i have keys 3 and 9, it will point to 9 but i need to
			// return the value corresponding to 3
			return (--it)->second;
		}
	}
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.

#include<iostream>
int main() {
	int init = 0;
	/*std::cout << "Init value ";
	std::cin >> init;
	std::cout << std::endl;*/
	interval_map<int, int> M(init);
	std::cout << "Queries ..." << std::endl;
	
	int q = 1;

	// Subinterval test
	
	/*M.assign(6, 8, 2);
	M.assign(2, 10, 1);*/
	
	

	// Add interval before test
	/*M.assign(7, 9, 1);
	M.assign(2, 5, 2);*/

	// Add interval after test
	/*M.assign(2, 5, 1);
	M.assign(7, 9, 2);*/

	// Add one just next to the other
	/*M.assign(2, 6, 1);
	M.assign(6, 9, 2);*/

	// Add in a border intersection
	/*M.assign(2, 6, 1);
	M.assign(6, 9, 2);
	M.assign(4, 8, 3);*/

	// Add in a sepparated intersection
	/*M.assign(7, 9, 1);
	M.assign(2, 5, 2);
	M.assign(4, 8, 3);*/

	// Add in a sepparated intersection
	//M.assign(7, 9, 1);
	//M.assign(2, 5, 2);
	//M.assign(4, 9, 3);
	//M.assign(6, 7, 8); // add a single value

	M.assign(1, 4, 1);
	M.assign(6, 8, 3);
	M.assign(8, 10, 2);
	M.assign(4, 9, 4);

	while (q != 11) {
		/*std::cout << "Insert query: ";
		std::cin >> q;*/
		std::cout << "Query: " << q << " Value: " << M[q] << std::endl;
		std::cout << std::endl;
		q++;
	} 

	return 0;
}
