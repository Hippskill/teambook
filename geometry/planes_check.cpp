/*
 * Checks if union of half-planes has non-zero area.
 *
 * Expected complexity: O(n).
 *
 */


#define ld long double

const ld inf = 1e9;
const ld eps = 1e-9;

inline ld det(ld a, ld b, ld c, ld d) {
    return a * d - b * c;
}

struct line {
    ld a, b, c;
    line(ld a = 0, ld b = 0, ld c = 0) : a(a), b(b), c(c) {}
    line(pt p, pt q) {
        a = p.y - q.y;
        b = q.x - p.x;
        c = -a * p.x - b * p.y;
        ld g = hypot(a, b);
        a /= g;
        b /= g;
        c /= g;
    }

    ld get_y(ld x) const {
        return -(a/b * x + c / b);
    }
    ld get_val(pt p) const {
        return a * p.x + b * p.y + c;
    }

    pt intersect(const line& p) const {
        ld d = det(a, b, p.a, p.b);
        if (fabs(d) > eps) {
            pt res;
            res.x = -det(c, b, p.c, p.b) / d;
            res.y = -det(a, c, p.a, p.c) / d;
            return res;
        }
        assert(false);
    }

    bool equivalent(const line &p) const {
        return fabs(det(a, b, p.a, p.b)) < eps
               && fabs(det(a, c, p.a, p.c)) < eps
               && fabs(det(b, c, p.b, p.c)) < eps;
    }

    bool parallel(const line& p) const {
        return fabs(det (a, b, p.a, p.b)) < eps;
    }
};

pair<ld, ld> intersect(pair<ld, ld> a, pair<ld, ld> b) {
    return {max(min(a.first, a.second), min(b.first, b.second)),
            min(max(a.first, a.second), max(b.first, b.second))};
}

bool check(vector<line>& a) {
    random_shuffle(a.begin(), a.end());
    a.push_back(line({-inf, -inf}, {-inf, inf}));
    a.push_back(line({-inf, inf}, {inf, inf}));
    a.push_back(line({inf, inf}, {inf, -inf}));
    a.push_back(line({inf, -inf}, {-inf, -inf}));
    reverse(a.begin(), a.end());
    for (int i = 0; i < 4; ++i) {
        a[i].a *= -1;
        a[i].b *= -1;
        a[i].c *= -1;
    }
    pt p(-inf, inf);
    int res = 0;
    for (int i = 4; i < a.size(); ++i) {
        if (a[i].get_val(p) < eps) {
            pair<ld, ld> xx = {-inf, inf};
            for (int j = 0; j < i; ++j) {
                if (a[i].parallel(a[j])) {
                    pt q(1.0, a[i].get_y(1.0));
                    if (a[j].get_val(q) < eps)
                        return false;
                } else {
                    pt q = a[i].intersect(a[j]);
                    pt q2(q.x - 1.0, a[i].get_y(q.x - 1.0));
                    if (a[j].get_val(q2) > -eps) {
                        xx = intersect(xx, {-inf, q.x});
                    } else {
                        xx = intersect(xx, {q.x, inf});
                    }
                }
                if (xx.second - xx.first < -eps)
                    return false;
            }
            if (xx.second - xx.first > -eps) {
                pt p1(xx.first, a[i].get_y(xx.first));
                pt p2(xx.second, a[i].get_y(xx.second));
                if (p1.y - p2.y > -eps)
                    p = p1;
                else
                    p = p2;
            } else {
                return false;
            }
        }
        ++res;
    }
    return true;
}
