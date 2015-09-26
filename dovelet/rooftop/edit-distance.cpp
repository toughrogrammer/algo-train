#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define DEBUGGING 0

#define ACTION_COPY 0
#define ACTION_SUBSTITUTE 1
#define ACTION_INSERT 2
#define ACTION_DELETE 3

using namespace std;

class ActionItem {
public:
	int weight;
	int action;

	ActionItem() {

	}
	ActionItem(int w, int a) {
		weight = w;
		action = a;
	}
};


string origin;
string draft;


ActionItem MIN(const ActionItem& a, const ActionItem& b) {
	if( a.weight <= b.weight ) {
		return a;
	}
	return b;
}

void edit_distance(vector< vector<ActionItem> >& dp, const string& draft, const string& origin) {
	unsigned int draft_length = draft.size() - 1;
	unsigned int origin_length = origin.size() - 1;

	dp.clear();
	for( int i = 0; i <= draft_length + 2; i ++ ) {
		vector<ActionItem> row;
		row.resize(origin_length + 2);
		dp.push_back(row);
	}

	for( int i = 0; i <= draft_length; i ++ ) {
		dp[i][0] = ActionItem(i, ACTION_INSERT);
	}
	for( int i = 0; i <= origin_length; i ++ ) {
		dp[0][i] = ActionItem(i, ACTION_DELETE);
	}

	for( int i = 1; i <= draft_length; i++ ) {
		for( int j = 1; j <= origin_length; j++ ) {
			ActionItem actCopyOrSubs(dp[i-1][j-1].weight, ACTION_COPY);
			if( draft[i] != origin[j] ) {
				actCopyOrSubs.weight ++;
				actCopyOrSubs.action = ACTION_SUBSTITUTE;
			}
			ActionItem actInsert(dp[i-1][j].weight + 1, ACTION_INSERT);
			ActionItem actDelete(dp[i][j-1].weight + 1, ACTION_DELETE);

			ActionItem min;
			min.weight = 99999;

			min = MIN(min, actCopyOrSubs);
			min = MIN(min, actDelete);
			min = MIN(min, actInsert);

			dp[i][j] = min;
		}
	}
}

void backtracking(
	const vector< vector<ActionItem> >& dp, 
	vector<int>& ret, 
	int i, 
	int j) {
	if( i <= 0 && j <= 0 ) {
		return;
	}

	ActionItem act = dp[i][j];
	// because this tis backtrace, flip action
	if( act.action == ACTION_INSERT ) {
		ret.push_back( ACTION_DELETE );
	} else if( act.action == ACTION_DELETE ) {
		ret.push_back( ACTION_INSERT );
	} else {
		ret.push_back( act.action );
	}

	if( act.action == ACTION_COPY ) {
		backtracking(dp, ret, i - 1, j - 1);
	} else if( act.action == ACTION_SUBSTITUTE ) {
		backtracking(dp, ret, i - 1, j - 1);
	} else if( act.action == ACTION_INSERT ) {
		backtracking(dp, ret, i - 1, j);
	} else if( act.action == ACTION_DELETE ) {
		backtracking(dp, ret, i, j - 1);
	}
}

int main(int argc, char const *argv[])
{
	cin >> draft;
	cin >> origin;

	draft.insert(0, " ");
	origin.insert(0, " ");

	vector< vector<ActionItem> > dp;
	edit_distance(dp, draft, origin);
	cout << dp[draft.size() - 1][origin.size() - 1].weight << endl;

	vector<int> result;
	backtracking(dp, result, draft.size() - 1, origin.size() - 1);
	reverse(result.begin(), result.end());

	string newstr = draft;
	int curr = 1;
	int count = 0;

	printf("%d. %s\n", count++, newstr.c_str());
	for( int i = 0; i < result.size(); i ++ ) {
		int action = result[i];
		if( action == ACTION_COPY ) {
			curr++;
		} else if( action == ACTION_SUBSTITUTE ) {
			newstr[curr] = origin[curr];
			curr++;
			printf("%d. %s\n", count++, newstr.c_str());
		} else if( action == ACTION_INSERT ) {
			newstr.insert(newstr.begin() + curr, origin[curr]);
			curr++;
			printf("%d. %s\n", count++, newstr.c_str());
		} else if( action == ACTION_DELETE ) {
			newstr.erase(curr, 1);
			printf("%d. %s\n", count++, newstr.c_str());
		}
	}
	
	return 0;
}