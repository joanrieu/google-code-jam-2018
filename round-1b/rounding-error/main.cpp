#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

void solve(const unsigned test, unsigned participants, std::vector<unsigned> &languages)
{
    unsigned total = 0;
    const double coef = 100. / participants;
    const unsigned roundedCoef = round(coef);
    if (coef == (unsigned)coef)
    {
        total = 100;
    }
    else if (roundedCoef > coef)
    {
        unsigned remainingParticipants = participants;
        for (const auto &count : languages)
        {
            total += round(count * coef);
            remainingParticipants -= count;
        }
        // remainingParticipants is now valid
        cerr << "remaining: " << remainingParticipants << " * " << roundedCoef << endl;
        total += remainingParticipants * roundedCoef;
    }
    else
    {
        multimap<double, double> toComplete;
        unsigned remainingParticipants = participants;
        for (const auto &count : languages)
        {
            remainingParticipants -= count;
            double subtotal = count * coef;
            unsigned roundedSubtotal = round(subtotal);
            if (roundedSubtotal > subtotal)
                total += subtotal;
            else
            {
                double decimals = subtotal - roundedSubtotal;
                toComplete.insert(make_pair(-decimals, subtotal));
            }
        }
        // remainingParticipants is now valid
        for (unsigned i = 0; i < remainingParticipants; ++i)
            toComplete.insert(make_pair(0, 0));
        while (!toComplete.empty())
        {
            const auto it = toComplete.cbegin();
            double subtotal = it->second;
            toComplete.erase(it);
            while (subtotal - (unsigned)subtotal < .5)
            {
                if (remainingParticipants)
                {
                    remainingParticipants--;
                    subtotal += coef;
                }
                else
                {
                    break;
                }
            }
            total += round(subtotal);
        }
    }
    cout << "Case #" << test << ": " << total << endl;
}

int main()
{
    unsigned tests;
    cin >> tests;
    for (unsigned test = 1; test <= tests; ++test)
    {
        unsigned participants, languagesLength;
        cin >> participants >> languagesLength;
        std::vector<unsigned> languages;
        languages.reserve(languagesLength);
        for (unsigned language = 0; language < languagesLength; ++language)
        {
            unsigned count;
            cin >> count;
            languages.push_back(count);
        }
        cerr << "----" << endl
             << endl;
        cerr << "test " << test << endl;
        cerr << "participants " << participants << endl;
        cerr << "languages with counts";
        for (const auto &count : languages)
            cerr << ' ' << count;
        cerr << endl
             << endl;
        solve(test, participants, languages);
        cerr << endl;
    }
}
