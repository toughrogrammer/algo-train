#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

#define INFINITE 99999
#define MAX_BUY_ITEMS 110
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

using namespace std;


class Item {
public:
	int amount;
	double price;

	Item(int amount, double price) {
		this->amount = amount;
		this->price = price;
	}
};


vector<Item> items;
vector<int> problems;
int CASE = 1;


vector<int> GetTokensFromString(string input, string delimiter = " ")
{
	vector<int> tokens;

	size_t pos = 0;
	string token;
	while ((pos = input.find(delimiter)) != string::npos) {
		string subs = input.substr(0, pos);
		tokens.push_back( stoi(subs) );
		input.erase(0, pos + delimiter.length());
	}

	if( input.size() > 0 ) {
		tokens.push_back( stoi(input) );
	}

	return tokens;
}

void init() {
	items.clear();
	items.push_back( Item(999, INFINITE) );
	problems.clear();
}

void inputting() {
	double unit_price;
	int n;
	
	cin >> unit_price >> n;
	items.push_back( Item(1, unit_price) );

	for( int i = 0; i < n; i ++ ) {
		int m;
		double price;
		cin >> m >> price;
		items.push_back( Item(m, price) );
	}

	// clear buffer
	cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 

	string line;
	getline(cin, line);
	problems = GetTokensFromString(line);
}

void solve(vector<int> problems) {
	vector< vector<double> > arr;
	for( int i = 0; i < items.size() + 1; i ++ ) {
		vector<double> row;
		row.resize(MAX_BUY_ITEMS + 1);
		for( int j = 0; j < MAX_BUY_ITEMS; j ++ ) {
			row[j] = INFINITE;
		}

		arr.push_back( row );
	}

	int maxAmount = 0;
	for( int i = 0; i < problems.size(); i ++ ) {
		maxAmount = MAX(maxAmount, problems[i]);
	}

	for( int i = 1; i < items.size(); i ++ ) {
		const auto item = items[i];
		for( int j = 0; j <= maxAmount; j ++ ) {
			double min = 99999, v;

			v = j / item.amount * item.price;
			if( j % item.amount > 0 ) {
				v += item.price;
			}
			min = MIN(min, v);
			min = MIN(min, arr[i-1][j]);

			if( j - item.amount >= 0 ) {
				v = arr[i][j - item.amount] + item.price;
				min = MIN(min, v);
			}

			arr[i][j] = min;
		}
	}

	printf("Case %d:\n", CASE);
	for( int i = 0; i < problems.size(); i ++ ) {
		int amount = problems[i];
		double min = INFINITE;
		if(amount > 0) {
			for( int j = 0; j <= items.size(); j++ ) {
				if( min > arr[j][amount] ) {
					min = arr[j][amount];
				}
			}
		} else {
			min = 0;
		}
		
		printf("Buy %d for $%.2f\n", amount, min);
	}
}

int main(int argc, char const *argv[])
{
	while(1) {
		init();
		inputting();
		solve(problems);

		// clear white space
		cin >> ws;
		if( cin.eof() ) {
			break;
		}

		CASE++;
	}
	
	return 0;
}