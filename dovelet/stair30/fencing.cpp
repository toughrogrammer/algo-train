#include <iostream>
#include <stdio.h>
#include <math.h>
#include <climits>
#include <cfloat>
#include <vector>
#include <algorithm>
#include <deque>
 
#define PI 3.14159265
 
using namespace std;
 
 
class Vector2
{
public:
    double x, y;
 
    Vector2() {
        x = 0;
        y = 0;
    }
    Vector2(double initx, double inity) {
        x = initx;
        y = inity;
    }
 
    double Length() {
        return double(sqrt(x*x + y*y));
    }
    double Angle() const {
        return atan2(y, x) /* * 180 / PI */;
    }
    static double Cross(const Vector2& lhs, const Vector2& rhs) {
        return lhs.x * rhs.y - lhs.y * rhs.x;
    }
    Vector2 operator-(const Vector2& vec) const {
        return Vector2(x - vec.x, y - vec.y);
    }
};


vector<Vector2> points;
Vector2 base_point(DBL_MAX, DBL_MAX);
int base_point_index;
vector<Vector2> sorted;


bool is_left(const Vector2& a, const Vector2& b, const Vector2& c) {
    return Vector2::Cross(a, b) + Vector2::Cross(b, c) + Vector2::Cross(c, a) > 0;
}

bool angle_comp(const pair<int, double>& lhs, const pair<int, double>& rhs) {
    return lhs.second > rhs.second;
}
 
void sort_by_angle() {
    vector< pair<int, double> > arr_for_sort;
    for( int i = 0; i < points.size(); i ++ ) {
        if( i == base_point_index ) {
            continue;
        }
 
        Vector2 diff = points[i] - base_point;
        double angle = diff.Angle(); // it is radian
        arr_for_sort.push_back( pair<int, double>(i, angle) );
    }
 
    sort(arr_for_sort.begin(), arr_for_sort.end(), angle_comp);
 
    sorted.push_back( points[base_point_index] );
    for( int i = 0; i < arr_for_sort.size(); i ++ ) {
        int target = arr_for_sort[i].first;
        sorted.push_back( points[target] );
    }
}
 
void solve() {
    sort_by_angle();
 
    deque<Vector2> deq;
    deq.push_back(sorted[0]);
    deq.push_back(sorted[1]);
    deq.push_back(sorted[2]);
 
    for( int i = 3; i < sorted.size(); i ++ ) {
        while(true) {
            Vector2 v1 = *(deq.end() - 1); // top
            Vector2 v2 = *(deq.end() - 2); // top - 1
            Vector2 v3 = sorted[i]; // curr consider point

            if( is_left(v1, v2, v3) ) {
                break;
            } else {
                deq.pop_back();
            }
        }
 
        deq.push_back(sorted[i]);
    }
 
    double length_sum = 0;
    for( int i = 0; i < deq.size(); i ++ ) {
        Vector2 v1, v2;
        v1 = deq[i];
        if( i + 1 < deq.size() ) {
            v2 = deq[i + 1];
        } else {
            v2 = deq[0];
        }
 
        length_sum += (v1 - v2).Length();
    }
 
    length_sum = ((int)((length_sum + 0.005) * 100)) * 0.01;
    printf("%.2f\n", length_sum);
}
 
int main(int argc, char const *argv[]) {
    int n;
    cin >> n;
 
    double x, y;
    for( int i = 0; i < n; i ++ ){
        cin >> x >> y;
        points.push_back(Vector2(x, y));
 
        if( base_point.y > y ) {
            base_point.x = x;
            base_point.y = y;
            base_point_index = i;
        }
    }
 
    solve();
 
    return 0;
}