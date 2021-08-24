#include <iostream>
#include <set>
#include<map>
using namespace std;

class Person_Compare{
public:
    bool operator()(pair<string,int> p1, pair<string,int> p2){
        return p1.second < p2.second;
    }
};

int main() {
	int no_of_transactions, friends;
	cin>> no_of_transactions>> friends;
	
	string x,y;
	int amount;
	
	//make a hashmap to store name as a key and  net amount as a value that will have to take at friends
	map<string,int> net;
	
	while(no_of_transactions--){
	    cin>>x>>y>>amount;
	    if(net.find(x) == net.end()) net[x] = 0;
	    if(net.find(y) == net.end()) net[y] = 0;
	    net[x] -= amount;
	    net[y] += amount;
	}
	
	// Iterate over the person, add those person to multiset whe have non zero net
	multiset<pair<string, int>, Person_Compare> m;
	
	for(auto &p: net){
        string person = p.first;
        int amount = p.second;
	    if(amount!=0)
	        m.insert({person, amount});
	}
	
	// cnt store minimum total number of transaction  
	int cnt = 0;
	//Pop out two person (left & right) and try to settle them
	while(!m.empty()){
	    auto low = m.begin();
	    auto high = prev(m.end());
	    
	    int debit = low->second;
        string debit_person = low->first;

	    int credit = high->second;
        string credit_person = high->first;
	    
	    //erase these two from multiset
	    m.erase(low);
	    m.erase(high);
	    
	    //Settlement
	    int Settled_amount = min(-debit, credit);
	    cnt++;
	    
	    // Settlement_amount from donor to acceptor
	    debit += Settled_amount;
	    credit -= Settled_amount;

        // Print the transaction between the people
        cout<< debit_person<< " will pay " << Settled_amount << " to " << credit_person<<endl;
	    
	    if(debit != 0) m.insert({debit_person, debit});
	    if(credit != 0) m.insert({credit_person, credit});
	    
	}
	cout<<"Minimum number of transaction required for settlement : "<< cnt<<endl;
	return 0;
}
