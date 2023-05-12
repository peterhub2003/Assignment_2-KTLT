#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#define vt vector
#define ll long long
#define sz(x) (int)(x).size()

const ll eps = 1e9 + 7;


string strip(string s){
	string res = s;
	while(res.length() > 0 && res.front() == ' ') res.erase(0, 1);
    while(res.length() > 0 && res.back() == ' ') res.pop_back();
    
    return res;
}



int main()
{
	#ifdef USING_FILE
		freopen("input.txt", stdin);
		freopen("output.txt", stdout);
	#endif

	ifstream ifs;
	ifs.open("tc1_events.txt");

	int n;
	int* ar = nullptr;

	if(ifs.is_open()){
		string s; getline(ifs, s);
		s = strip(s);	
		n = stoi(s);
		ar = new int[n];

		getline(ifs, s);
		s = strip(s);
		stringstream ss(s);
		for(int i = 0; i < n; ++i){
			string inp; ss >> inp;
			ar[i] = stoi(inp);
		}
		cout << "N:  " << n << endl;
		for(int i = 0; i < n; ++i){
			cout << ar[i] << ' ';
		}

		ifs.close();
	}
	else{
		cout << "Error: Open File is failed\n";
	}


	// string line = "  34 324 432 432 34 34 43  ";
	// cout << line.length() << " ===> " << strip(line).length() << endl;
	// stringstream ss;
	// cout << ss.str() << endl;

	// line = strip(line);
	// ss << line;
	// cout << ss.str() << endl;

	
		

	return 0;	
}