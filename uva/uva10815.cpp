#include <iostream>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

map<string, int> dict;


bool valid(char c) {
	return (c >= 'a' && c <= 'z');
}

void push_if_valid(const string &str) {
	int i;
	for( i = 0; i < str.size(); i ++ ) {
		if( ! valid(str[i]) ) {
			break;
		}
	}

	if( i != str.size() ) {
		return;
	}

	if( ! valid( str[0] ) ) {
		return;
	}

	dict[str] ++;
}

void lowercase(string &input) {
	for( int i = 0; i < input.size(); i ++ ) {
		if( input[i] >= 'A' && input[i] <= 'Z' ) {
			input[i] += 'a' - 'A';
		}
	}
}

void strip_side(string &input) {
	int left, right;

	for( left = 0; left < input.size(); left ++ ) {
		if( valid(input[left]) ) {
			break;
		}
	}

	for( right = input.size() - 1; right >= 0; right -- ) {
		if( valid(input[right]) ) {
			break;
		}
	}

	input = input.substr(left, right - left + 1);
}

void tokenizing(string input) {
	// how many token there is?
	int count = 0;
	for( int i = 0; i < input.size(); i ++ ) {
		if( ! valid(input[i]) ) {
			count++;
		}
	}

	// we need to do tokenizing
	if( count > 0 ) {
		int left = 0;
		for( int i = 0; i < input.size(); i ++ ) {
			if( ! valid(input[i]) ) {
				string str = input.substr(left, i - left);
				left = i + 1;
				push_if_valid(str);
			}
		}

		// last item
		push_if_valid(input.substr(left, input.size() - left + 1));
	} else {
		push_if_valid(input);
	}
}

int main(int argc, char const *argv[])
{
	string str;

	while(!cin.eof()) {
		cin >> str;
		lowercase(str);
		strip_side(str);
		tokenizing(str);
	}

	for(auto it = dict.begin(); it != dict.end(); ++it) {
		cout << it->first << endl;
	}

	return 0;
}