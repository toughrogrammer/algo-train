#include <iostream>
#include <climits>

#define DEBUGGING 0

#define MAX_NUM_OF_REPAIR_SHOP 110

using namespace std;

class Item {
public:
	int remain_distance;
	int time_cost;

	Item() {
		remain_distance = 0;
		time_cost = 0;
	}

	Item(int r, int t) {
		remain_distance = r;
		time_cost = t;
	}
};


int max_distance;
int num_of_repair_shop;
int distance_between_shop[MAX_NUM_OF_REPAIR_SHOP];
int repair_time_cost[MAX_NUM_OF_REPAIR_SHOP];
Item dp[MAX_NUM_OF_REPAIR_SHOP][MAX_NUM_OF_REPAIR_SHOP];


Item Min(const Item& lhs, const Item& rhs) {
	if( lhs.time_cost < rhs.time_cost ) {
		if( lhs.remain_distance > rhs.remain_distance ) {
			return lhs;
		}
	}

	return rhs;
}

int total_distance(int start, int end) {
	int sum = 0;
	for( int i = start; i <= end; i ++ ) {
		sum += distance_between_shop[i];
	}

	return sum;
}

void solve() {
	for( int i = 0; i <= num_of_repair_shop + 1; i ++ )
		for( int j = 0; j <= num_of_repair_shop + 1; j ++ ) {
			Item &item = dp[i][j];
			if( j == 0 ) {
				item.remain_distance = max_distance;
				item.time_cost = 0;
			} else {
				item.remain_distance = 0;
				item.time_cost = INT_MAX;
			}
		}

	int remain_distance = max_distance;
	for( int i = 0; i <= num_of_repair_shop + 1; i ++ ) {
		remain_distance -= distance_between_shop[i];
		if( remain_distance >= 0 ) {
			Item &item = dp[0][i];
			item.remain_distance = remain_distance;
			item.time_cost = 0;
		} else {
			// Item.remain_distance = INT_MIN;
		}
	}

	for( int i = 1; i <= num_of_repair_shop; i ++ ) {
		dp[i][0].remain_distance = max_distance;
	}

	for( int i = 1; i <= num_of_repair_shop; i ++ ) {
		int remain_distance = max_distance;
		for( int j = 1; j <= num_of_repair_shop + 1; j ++ ) {
			Item minItem(0, INT_MAX);

			Item item1 = dp[i-1][j];
			minItem = Min(minItem, item1);

			for( int k = j - 1; k >= 0; k -- ) {
				const Item& item2 = dp[i][k];
				if( item2.time_cost == INT_MAX ) {
					break;
				}

				// k부터 j 포인트까지의 거리
				int td = total_distance(k + 1, j);
				if( DEBUGGING ) printf("i:%3d j:%3d k:%3d td:%3d\n", i, j, k, td);
				if( max_distance - td < 0 ) {
					break;
				}

				if( item2.remain_distance - td >= 0 ) {
					if( minItem.time_cost > item2.time_cost ) {
						minItem = Item(item2.remain_distance - td, item2.time_cost);
					}
				} else {
					Item item;
					item.remain_distance = max_distance - td;
					item.time_cost = item2.time_cost + repair_time_cost[k];
					if( minItem.time_cost > item.time_cost ) {
						minItem = item;
					}
				}
			}

			dp[i][j] = minItem;
		}
	}
}

void get_input() {
	cin >> max_distance;
	cin >> num_of_repair_shop;
	for( int i = 1; i <= num_of_repair_shop + 1; i ++ ) {
		cin >> distance_between_shop[i];
	}
	for( int i = 1; i <= num_of_repair_shop; i ++ ) {
		cin >> repair_time_cost[i];
	}
}

int main(int argc, char const *argv[]) {
	get_input();
	solve();

#if DEBUGGING == 1
	for( int i = 0; i <= num_of_repair_shop + 1; i ++ ) {
		printf("%10d  ", i);
	}
	printf("\n");
	for( int i = 0 ; i <= num_of_repair_shop; i ++ ) {
		for( int j = 0 ; j <= num_of_repair_shop + 1; j ++ ) {
			const Item &item = dp[i][j];
			printf("(%4d,", item.remain_distance);
			if( item.time_cost == INT_MAX ) {
				printf("%4s", "INF");
			} else {
				printf("%4d", dp[i][j].time_cost);
			}
			printf(") ");
		}
		printf("\n");
	}
#endif

	printf("%d\n", dp[num_of_repair_shop][num_of_repair_shop+1].time_cost);

	return 0;
}