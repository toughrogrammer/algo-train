#include <iostream>
#include <vector>
#include <climits>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

using namespace std;


class Point {
public:
	int x, y;
	
	Point() {
		Set(0, 0);
	}
	
	Point(int x, int y) {
		Set(x, y);
	}

	Point(const Point& obj) {
		Set(obj.x, obj.y);
	}
	
	void Set(int x, int y){
		this->x = x;
		this->y = y;
	}
};

class Rect {
public:
	Point left_top, right_bottom;
	
	Rect() {
		left_top = Point();
		right_bottom = Point();
	}
	
	Rect(Point p1, Point p2) {
		left_top = p1;
		right_bottom = p2;
	}
};


int size;
vector< vector<int> > arr;
vector< vector<int> > dp;
vector< vector<Rect> > rectArr;


int sum_of_rect(const Point& left_top, const Point& right_bottom) {
	if( left_top.y > right_bottom.y
		|| left_top.x > right_bottom.x ) {
		return INT_MIN;
	}

	int n = 0;
	for( int i = left_top.y; i <= right_bottom.y; i ++ )
		for( int j = left_top.x; j <= right_bottom.x; j ++ )
			n += arr[i][j];
	
	// printf("[%3d][%3d] to [%3d][%3d] = %3d\n",
	// 	   left_top.y,
	// 	   left_top.x,
	// 	   right_bottom.y,
	// 	   right_bottom.x,
	// 	   n);
	
	return n;
}

int sum_of_rect(const Rect& rect) {
	return sum_of_rect(rect.left_top, rect.right_bottom);
}

void solve() {
	int new_sum = 0;
	
	dp[1][1] = arr[1][1];
	rectArr[1][1] = Rect( Point(1, 1), Point(1, 1) );
	for( int i = 0; i <= size; i ++ ) {
		rectArr[0][i] = Rect( Point(1, 1), Point(1, 1) );
		rectArr[i][0] = Rect( Point(1, 1), Point(1, 1) );
	}
	
	for( int i = 1; i <= size; i ++ ) {
		for( int j = 1; j <= size; j ++ ) {
			// case 1
			{
				const Rect& rect = rectArr[i-1][j];
				Point left_top1(rect.left_top);
				Point left_top2(rect.left_top.x + 1, rect.left_top.y);
				Point left_top3(rect.left_top.x, rect.left_top.y + 1);
				Point right_bottom(j, i);

				int sum1 = sum_of_rect(left_top1, right_bottom);
				int sum2 = sum_of_rect(left_top2, right_bottom);
				int sum3 = sum_of_rect(left_top3, right_bottom);

				if( dp[i][j] < dp[i-1][j] ) {
					dp[i][j] = dp[i-1][j];
					rectArr[i][j] = rectArr[i-1][j];
				}
				if( dp[i][j] < sum1 ) {
					dp[i][j] = sum1;
					rectArr[i][j] = Rect(left_top1, right_bottom);
				}
				if( dp[i][j] < sum2 ) {
					dp[i][j] = sum2;
					rectArr[i][j] = Rect(left_top2, right_bottom);
				}
				if( dp[i][j] < sum3 ) {
					dp[i][j] = sum3;
					rectArr[i][j] = Rect(left_top3, right_bottom);
				}
			}

			// case 2
			{
				const Rect& rect = rectArr[i][j-1];
				Point left_top1(rect.left_top);
				Point left_top2(rect.left_top.x + 1, rect.left_top.y);
				Point left_top3(rect.left_top.x, rect.left_top.y + 1);
				Point right_bottom(j, i);

				int sum1 = sum_of_rect(left_top1, right_bottom);
				int sum2 = sum_of_rect(left_top2, right_bottom);
				int sum3 = sum_of_rect(left_top3, right_bottom);

				if( dp[i][j] < dp[i][j-1] ) {
					dp[i][j] = dp[i][j-1];
					rectArr[i][j] = rectArr[i][j-1];
				}
				if( dp[i][j] < sum1 ) {
					dp[i][j] = sum1;
					rectArr[i][j] = Rect(left_top1, right_bottom);
				}
				if( dp[i][j] < sum2 ) {
					dp[i][j] = sum2;
					rectArr[i][j] = Rect(left_top2, right_bottom);
				}
				if( dp[i][j] < sum3 ) {
					dp[i][j] = sum3;
					rectArr[i][j] = Rect(left_top3, right_bottom);
				}
			}

			if( dp[i][j] < arr[i][j] ) {
				dp[i][j] = arr[i][j];
				rectArr[i][j] = Rect(Point(j, i), Point(j, i));
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	cin >> size;
	arr.push_back( vector<int>( size + 1 ) );
	dp.push_back( vector<int>( size + 1 ) );
	rectArr.push_back( vector<Rect>( size + 1 ) );
	
	for( int i = 0; i < size; i ++ ) {
		vector<int> row( size + 1 );
		dp.push_back( row );
		rectArr.push_back( vector<Rect>( size + 1 ) );
		
		for( int j = 0; j < size; j ++ ) {
			cin >> row[j+1];
		}
		arr.push_back( row );
	}

	for( int i = 0; i <= size; i ++ ) {
		for( int j = 0; j <= size; j ++ ) {
			dp[i][j] = INT_MIN;
		}
	}
	
	solve();
	
	for( int i = 1; i <= size; i ++ ) {
		for( int j = 1; j <= size; j ++ ) {
			if( dp[i][j] == INT_MIN ) {
				printf(" -INF");
			} else {
				printf("%5d", dp[i][j]);
			}

			const Rect& rect = rectArr[i][j];
			printf("([%3d][%3d] to [%3d][%3d])",
				rect.left_top.y,
				rect.left_top.x,
				rect.right_bottom.y,
				rect.right_bottom.x);
		}
		printf("\n");
	}

	cout << dp[size][size] << endl;
	
	return 0;
}