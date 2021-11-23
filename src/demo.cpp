#include  <iostream>

using namespace std;
struct point
{
  float x;
  float y;
};

void test(point *point) {
  point->x = 1;
  point->y = 2;
}

int main(){
  point p;
  test(&p);
  cout << p.x << " " << p.y << endl;
  cout << "size of int " << sizeof(int) << " bype" << endl;
  return 0;
}

