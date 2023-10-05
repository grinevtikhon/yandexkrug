#include <bits/stdc++.h>

using namespace std;

using int128 = __int128_t;

void init() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
}

struct point {
    long long x = 0, y = 0;

    point() = default;

    point(long long _x, long long _y) : x(_x), y(_y) {}

    int128 operator*(const point &p) const {
        return (int128) x * p.x + (int128) y * p.y;
    }

    int128 operator%(const point &p) const {
        return (int128) x * p.y - (int128) y * p.x;
    }

    point operator+(const point &p) const {
        return {x + p.x, y + p.y};
    }

    point operator-() const {
        return {-x, -y};
    }

    point operator-(const point &p) const {
        return *this + (-p);
    }

    point operator*(long long k) const {
        return {x * k, y * k};
    }

    [[nodiscard]]
    int128 len2() const {
        return (int128) x * x + (int128) y * y;
    }

    [[nodiscard]]
    long double len() const {
        return sqrt((long double) len2());
    }

    [[nodiscard]]
    int128 dist2(const point &p) const {
        return (*this - p).len2();
    }

    [[nodiscard]]
    long double dist(const point &p) const {
        return (*this - p).len();
    }
};

int sgn(int128 a) {
    if (a < 0) {
        return -1;
    } else if (a == 0) {
        return 0;
    } else {
        return 1;
    }
}

int sgn(long long a) {
    if (a < 0) {
        return -1;
    } else if (a == 0) {
        return 0;
    } else {
        return 1;
    }
}

int sgn(int a) {
    if (a < 0) {
        return -1;
    } else if (a == 0) {
        return 0;
    } else {
        return 1;
    }
}

struct segment {
    point a, b;

    segment(const point &p1, const point &p2) : a(p1), b(p2) {}

    [[nodiscard]]
    long double dist(const point &p) const {
        if ((a - b) * (p - b) <= 0 || (b - a) * (p - a) <= 0) {
            return min(p.dist(a), p.dist(b));
        } else {
            return abs ((long double) ( (long double) ((p - a) % (p - b)) / a.dist(b)));
        }
    }

    [[nodiscard]]
    long double dist(const segment &s) const {
        if ((s.a - a) % (b - a) == 0) {
            if ((s.b - a) % (b - a) == 0) {
                return min(s.dist(a), s.dist(b));
            } else {
                return min({s.dist(a), s.dist(b), dist(s.a), dist(s.b)});
            }
        }
        if ((s.b - a) % (b - a) == 0) {
            return min({s.dist(a), s.dist(b), dist(s.a), dist(s.b)});
        }
        if (sgn((a - b) % (s.a - b)) * sgn((a - b) % (s.b - b)) < 0 &&
            sgn((a - s.b) % (s.a - s.b)) * sgn((b - s.b) % (s.a - s.b)) < 0) {
            return 0;
        } else {
            return min({s.dist(a), s.dist(b), dist(s.a), dist(s.b)});
        }
    }
};

struct ray {
    point a, b, r;
    // a -> beginning, b -> point on ray, r -> radius vector

    ray(const point &p1, const point &p2) : a(p1), b(p2), r(p2 - p1) {}

    [[nodiscard]]
    long double dist(const point &p) const {
        if (r * (p - a) <= 0) {
            return a.dist(p);
        } else {
            return abs ((long double) ( (long double) ((p - a) % (p - b)) / a.dist(b)));
        }
    }

    [[nodiscard]]
    long double dist(const segment &s) const {
        point t = a + r * 25000;
        return s.dist(segment(a, t));
    }

    [[nodiscard]]
    long double dist(const ray &t) const {
        if (t.r % r == 0) {
            return dist(t.a);
        } else {
            if (sgn((-t.r) % (r)) * sgn((-t.r) % (t.a - a)) >= 0) {
                return 0;
            } else {
                return min({dist(t.a), dist(t.b), t.dist(a), t.dist(b)});
            }
        }
    }
};


struct line {
    point a, b;

    line(const point &p1, const point &p2) : a(p1), b(p2) {}

    [[nodiscard]]
    long double dist(const point &p) const {
        return abs ((long double) ( (long double) ((p - a) % (p - b)) / a.dist(b)));
    }

    [[nodiscard]]
    long double dist(const segment &s) const {
        if (sgn((a - b) % (s.a - b)) * sgn((a - b) % (s.b - b)) <= 0) {
            return 0;
        } else {
            return min(dist(s.a), dist(s.b));
        }
    }

    [[nodiscard]]
    long double dist(const ray &r) const {
        if (r.r % (a - b) == 0) {
            return dist(r.a);
        } else {
            return 0;
        }
    }

    [[nodiscard]]
    long double dist(const line &l) const {
        if ((l.a - l.b) % (a - b) == 0) {
            return dist(l.a);
        } else {
            return 0;
        }
    }
};

signed main() {
    init();
    point a, b, c, d;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
    cout << fixed << setprecision(8);
    cout << a.dist(c) << '\n';
    cout << segment(c, d).dist(a) << '\n';
    cout << ray(c, d).dist(a) << '\n';
    cout << line(c, d).dist(a) << '\n';
    cout << segment(a, b).dist(c) << '\n';
    cout << segment(a, b).dist(segment(c, d)) << '\n';
    cout << ray(c, d).dist(segment(a, b)) << '\n';
    cout << line(c, d).dist(segment(a, b)) << '\n';
    cout << ray(a, b).dist(c) << '\n';
    cout << ray(a, b).dist(segment(c, d)) << '\n';
    cout << ray(a, b).dist(ray(c, d)) << '\n';
    cout << line(c, d).dist(ray(a, b)) << '\n';
    cout << line(a, b).dist(c) << '\n';
    cout << line(a, b).dist(segment(c, d)) << '\n';
    cout << line(a, b).dist(ray(c, d)) << '\n';
    cout << line(a, b).dist(line(c, d));
}
