#include <iostream>
#include <array>
#include <cmath>
using namespace std;

typedef long double number;
typedef array<number, 3> vec;
typedef array<vec, 3> mat;

inline void rotateX(vec &p, number a)
{
    auto c = cos(a);
    auto s = sin(a);
    p = vec{p[0],
            c * p[1] - s * p[2],
            s * p[1] + c * p[2]};
}

inline void rotateZ(vec &p, number a)
{
    auto c = cos(a);
    auto s = sin(a);
    p = vec{c * p[0] - s * p[1],
            s * p[0] + c * p[1],
            p[2]};
}

inline number area(const mat &points)
{
    number area = 0;
    for (auto &p : points)
    {
        // vectors are not normed ==> times 2
        // dot product with y-axis ==> take y component
        // face may be facing opposite direction ==> absolute
        area += abs(2 * p[1]);
    }
    return area;
}

inline mat makeBase()
{
    return {.5, 0, 0,
            0, .5, 0,
            0, 0, .5};
}

inline void print(const vec &v)
{
    cout << v[0] << ' ' << v[1] << ' ' << v[2] << endl;
}

inline void print(const mat &m)
{
    for (const auto &v : m)
        print(v);
}

inline void rotate(mat &points, number a, number b)
{
    for (auto &p : points)
    {
        rotateX(p, a);
        rotateZ(p, b);
    }
}

// max of │sin(b)⋅cos(a)│ + │cos(a)⋅cos(b)│ + │sin(a)│
// pi + 2 arctan(1/(sqrt(2) - sqrt(3)))
const number maxA = 0.615479708670387341067464589123993687855170004677547419527l;
const number maxB = M_PI / 4;

inline number fastArea(number a, number b)
{
    return sin(b) * cos(a) + cos(a) * cos(b) + sin(a);
}

/*

  ⎡cos(b)  -sin(b)⋅cos(a)    sin(a)⋅sin(b) ⎤
  ⎢──────  ───────────────   ───────────── ⎥
  ⎢  2            2                2       ⎥
  ⎢                                        ⎥
  ⎢sin(b)   cos(a)⋅cos(b)   -sin(a)⋅cos(b) ⎥
  ⎢──────   ─────────────   ───────────────⎥
  ⎢  2            2                2       ⎥
  ⎢                                        ⎥
  ⎢            sin(a)           cos(a)     ⎥
  ⎢  0         ──────           ──────     ⎥
  ⎣              2                2        ⎦

*/
inline mat fastPoints(number a, number b)
{
    auto cosa = cos(a), cosb = cos(b), sina = sin(a), sinb = sin(b);
    return mat{
        {cosb / 2, sinb / 2, 0,
         -sinb * cosa / 2, cosa * cosb / 2, sina / 2,
         sina * sinb / 2, -sina * cosb / 2, cosa / 2}};
}

void check(const mat &points)
{
    for (auto &point : points)
    {
        auto distSq = point[0] * point[0] + point[1] * point[1] + point[2] * point[2];
        if (distSq <= 0.25 - 1e-6 || distSq >= 0.25 + 1e-6)
        {
            cerr << "\e[33m"
                 << "sq dist from origin = "
                 << distSq
                 << "\e[0m"
                 << endl;
            abort();
        }
    }
    for (auto &duo : {make_pair(points[0], points[1]),
                      make_pair(points[1], points[2]),
                      make_pair(points[0], points[2])})
    {
        auto dot = duo.first[0] * duo.second[0] +
                   duo.first[1] * duo.second[1] +
                   duo.first[2] * duo.second[2];
        auto angle = acos(4 * dot);
        if (angle <= M_PI / 2 - 1e-6 || angle >= M_PI / 2 + 1e-6)
        {
            cerr << "\e[33m"
                 << "angle between quadrants = "
                 << angle
                 << "\e[0m"
                 << endl;
            abort();
        }
    }
    for (auto &duo : {make_pair(points[0], points[1]),
                      make_pair(points[1], points[2]),
                      make_pair(points[0], points[2])})
    {
        auto sub = vec{duo.first[0] - duo.second[0],
                       duo.first[1] - duo.second[1],
                       duo.first[2] - duo.second[2]};
        auto distSq = sub[0] * sub[0] +
                      sub[1] * sub[1] +
                      sub[2] * sub[2];
        if (distSq <= .5 - 1e-6 || distSq >= .5 + 1e-6)
        {
            cerr << "\e[33m"
                 << "sq dist between points = "
                 << distSq
                 << "\e[0m"
                 << endl;
            abort();
        }
    }
}

void solve(size_t icase, number targetArea)
{
    cout << "Case #" << icase << ":" << endl;
    /*/
    cerr << "\e[33m"
         << "target = "
         << targetArea
         << "\e[0m"
         << endl;
    /*/
    number minT = 0, maxT = 1;
    number maxAor0 = targetArea <= 1.414213 + 1e-6 ? 0 : maxA;
    mat points;
    number currentArea;
    number a, b;
    do
    {
        if (minT == maxT)
            //abort();
            break;
        number t = (minT + maxT) / 2;
        a = t * maxAor0, b = t * maxB;
        /*/
        points = makeBase();
        rotate(points, a, b);
        currentArea = area(points);
        /*/
        currentArea = fastArea(a, b);
        if (currentArea < targetArea)
            minT = t;
        else
            maxT = t;
        /*/
        cerr << "\e[33m"
             << t
             << " = "
             << fastArea(a, b)
             << "\e[0m"
             << endl;
        /*/
    } while (abs(currentArea - targetArea) > 10e-8);
    points = fastPoints(a, b);
    print(points);
    //check(points);
    /*/
    cerr << "\e[33m"
         << "result = "
         << currentArea
         << "\e[0m"
         << endl;
    /*/
}

int main()
{
    cout.precision(20);
    //cout << fixed;
    cerr.precision(20);
    size_t cases;
    cin >> cases;
    for (size_t icase = 1; icase <= cases; ++icase)
    {
        number targetArea;
        cin >> targetArea;
        solve(icase, targetArea);
    }
}
