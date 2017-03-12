#include <cstdio>
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Contestant {
    bool solved[10];
    int attempt[10];
    int penalty, count;
};

map<int, Contestant> Contest;
vector< int > Index;

bool comp(int c1, int c2)
{
    if (Contest[c1].count != Contest[c2].count)
        return (Contest[c1].count > Contest[c2].count);

    if (Contest[c1].penalty != Contest[c2].penalty)
        return (Contest[c1].penalty < Contest[c2].penalty);

    return (c1 < c2);
}

int main()
{
    int N;
    scanf("%d\n\n", &N);
    while(N--)
    {
        Contest.clear();
        Index.clear();
        int id, prob, time;
        char judge;
        string entry;
        stringstream ss;

        while( getline( cin, entry ) && entry != "" )
        {
            ss.clear();
            ss.str(entry);
            ss >> id >> prob >> time >> judge;

            if (Contest.find(id) == Contest.end())
            {
                Contestant Con;
                memset(Con.solved, false, sizeof Con.solved);
                memset(Con.attempt, 0, sizeof Con.attempt);
                Con.penalty = 0;
                Con.count = 0;
                Index.push_back(id);
                Contest[id] = Con;
            }
            if (judge == 'C' || judge == 'I')
            {
                if (Contest[id].solved[prob]) continue;

                if (judge == 'C')
                {
                    Contest[id].solved[prob] = true;
                    Contest[id].penalty += (20 * Contest[id].attempt[prob] + time);
                    Contest[id].count += 1;
                }
                else
                {
                    Contest[id].attempt[prob] += 1;
                }
            }
        }

        sort(Index.begin(), Index.end(), comp);

        for(int i = 0; i < Index.size(); i++)
            printf("%d %d %d\n", Index[i], Contest[Index[i]].count, Contest[Index[i]].penalty);

        if(N != 0)
        	printf("\n");
    }
    return 0;
}
