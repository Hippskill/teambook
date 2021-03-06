/*
 * Convex hull(Graham's traversal).
 *
 * Complexity: O(NlogN)
 *
 * Requrements: "point class"
 */

bool cmp(Point a, Point b) {
     return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool cw(Point a, Point b, Point c) {
     return a.x * (b.y - c.y) +
            b.x * (c.y - a.y) +
            c.x * (a.y - b.y) < 0;
}

bool ccw(Point a, Point b, Point c) {
     return a.x * (b.y - c.y) +
            b.x * (c.y - a.y) +
            c.x * (a.y - b.y) > 0;
}

void convex_hull(vector<Point>& a) {
     if (a.size() == 1) return;
     sort(a.begin(), a.end(), &cmp);
     Point p1 = a[0];
     Point p2 = a.back();
     vector<Point> up, down;
     up.push_back(p1);
     down.push_back(p1);
     for (size_t i = 1; i < a.size(); ++i) {
          if (i == a.size() - 1 || cw(p1, a[i], p2)) {
               while (up.size() >= 2 &&
                      !cw(up[up.size() - 2], up[up.size() - 1], a[i])) {
                    up.pop_back();
               }
               up.push_back (a[i]);
          }
          if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
               while (down.size() >= 2 &&
                      !ccw(down[down.size() - 2], down[down.size() - 1], a[i])) {
                    down.pop_back();
               }
               down.push_back(a[i]);
          }
     }
     a.clear();
     for (size_t i = 0; i < up.size(); ++i) {
          a.push_back(up[i]);
     }
     for (size_t i = down.size() - 2; i > 0; --i) {
          a.push_back(down[i]);
     }
}

