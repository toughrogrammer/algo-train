#include <iostream>
#include <string>
#include <vector>

#define MAX_WORDS 2000

using namespace std;


int arrLCS[MAX_WORDS][MAX_WORDS];


void inputting(vector<string>& dst) {
	string str;
	while(1) {
		cin >> str;
		if( str == "#" ) {
			break;
		}

		dst.push_back(str);
	}
}

void backtracking(vector<string>& ret,
	const vector<string>& first, 
	const vector<string>& second,
	int i,
	int j) {
	if( i <= 0 || j <= 0 ){
		return;
	}

	if(first[i] == second[j]) {
		ret.push_back(first[i]);
		backtracking(ret, first, second, i - 1, j - 1);
		return;
	}

	if(arrLCS[i][j-1] > arrLCS[i-1][j]) {
		backtracking(ret, first, second, i, j - 1);
	} else {
		backtracking(ret, first, second, i - 1, j);
	}
}

int main(int argc, char const *argv[])
{
	while(!cin.eof()) {
		vector<string> first;
		first.push_back("");

		vector<string> second;
		second.push_back("");

		inputting(first);
		cin >> ws;
		inputting(second);
		cin >> ws;

		for( int i = 0; i < MAX_WORDS; i ++ )
			for( int j = 0; j < MAX_WORDS; j ++ )
				arrLCS[i][j] = 0;

		for( int i = 1; i <= first.size() - 1; i ++ ) {
			string str1 = first[i];
			for( int j = 1; j <= second.size() - 1; j ++ ) {
				string str2 = second[j];
				if( str1 == str2 ) {
					arrLCS[i][j] = arrLCS[i-1][j-1] + 1;
				} else {
					int lhs = arrLCS[i][j-1];
					int rhs = arrLCS[i-1][j];
					arrLCS[i][j] = lhs > rhs ? lhs : rhs;
				}
			}
		}

		vector<string> result;
		backtracking(result, first, second, first.size() - 1, second.size() - 1);

		for( int i = result.size() - 1 ; i >= 0; i -- ) {
			string str = result[i];
			if( str.size() == 0 ) {
				continue;
			}

			cout << result[i];
			if( i != 0 ) {
				cout << " ";
			}
		}
		cout << endl;
	}

	return 0;
}