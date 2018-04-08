#include <iostream>
#include <cmath>
#include <set>
#include <map>
using namespace std;

int mincells;
bool done;
set<int> cells;
int centerx, centery;
int minx, maxx, miny, maxy;

void reset()
{
    done = false;
    cells.clear();
    centerx = 1000 / 2;
    centery = 1000 / 2;
}

void read_gopher()
{
    int x, y;
    cin >> x >> y;
    cerr << "# received " << x << ' ' << y << endl;
    if (x == 0 && y == 0)
        done = true;
    else if (x == -1 && y == -1)
        abort();
    else
        cells.insert(y * 1000 + x);
}

void send_gopher(int x, int y)
{
    cout << x << " " << y << endl;
    //cerr << "# requested " << x << ' ' << y << endl;
    read_gopher();
}

float usefulness(int x, int y)
{
    if (x <= minx || x >= maxx || y <= miny || y >= maxy)
        return -1;
    float score = 0;
    for (auto &yy : {y - 1, y, y + 1})
        for (auto &xx : {x - 1, x, x + 1})
            if (cells.find(yy * 1000 + xx) == cells.end())
                if (xx > minx && xx < maxx && yy > miny && yy < maxy)
                    ++score;
                else
                    return 0;
    if (!score)
        return -2;
    int dx = abs(x - centerx);
    int dy = abs(y - centery);
    score /= 10 * (dx * dx + dy * dy);
    return score;
}

void update_center_and_minmax()
{
    if (cells.size())
    {
        unsigned long long sumx = 0, sumy = 0;
        for (auto &cell : cells)
        {
            sumx += cell % 1000;
            sumy += cell / 1000;
        }
        centerx = sumx / cells.size();
        centery = sumy / cells.size();
        //cerr << "# gravity center in " << centerx << "x" << centery << endl;
    }
    minx = maxx = centerx;
    miny = maxy = centery;
    for (auto &cell : cells)
    {
        auto x = cell % 1000,
             y = cell / 1000;
        minx = min(x, minx);
        maxx = max(x, maxx);
        miny = min(y, miny);
        maxy = max(y, maxy);
    }
}

void solve()
{
    cin >> mincells;
    reset();
    while (!done)
    {
        update_center_and_minmax();
        multimap<float, int> useful_cells;
        for (int y = miny; y <= maxy; ++y)
            for (int x = minx; x <= maxx; ++x)
                useful_cells.insert(make_pair(usefulness(x, y), y * 1000 + x));
        int cell = useful_cells.rbegin()->second;
        int x = cell % 1000, y = cell / 1000;
        //cerr << "# " << x << "x" << y << " usefulness = " << useful_cells.rbegin()->first << endl;
        send_gopher(x, y);
    }
}

int main()
{
    int cases;
    cin >> cases;
    cerr << "# test cases = " << cases << endl;
    for (int icase = 1; icase <= cases; ++icase)
    {
        cerr << "# case " << icase << endl;
        solve();
    }
}
