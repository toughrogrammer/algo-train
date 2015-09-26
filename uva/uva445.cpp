#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void print_character(char c, int count) {
	for( int i = 0; i < count; i ++ ) {
		cout << c;
	}
}

void print_maze(string& line) {
	int length = line.size();
	if( line[0] == ' ' ) {
		cout << ' ';
		return;
	}

	int count = 0;
	char arr[10];

	for( int i = 0; i < length; i ++ ) {
		if( line[i] >= '0' && line[i] <= '9' ) {
			arr[0] = line[i];
			arr[1] = '\0';
			count += atoi(arr);
		} else {
			if( line[i] == 'b' ) {
				print_character(' ', count);
			} else if( line[i] == '!' ) {
				cout << endl;
			} else {
				print_character(line[i], count);
			}

			count = 0;
		}
	}
}

int main()
{
	string line;

	while(true) {
		line.clear();
		if( ! std::getline(std::cin, line) ) {
			break;
		}

		print_maze(line);
		cout << endl;
	}

	return 0;
}