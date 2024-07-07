#include"shortestpath_map.h"
#include<random>
#include<set>
#include<iostream>
#include<queue>

ShortEstPath_Map::ShortEstPath_Map()
{
    lenth = getrandomnum(MIN_LENTH, MAX_LENTH);
    high = getrandomnum(MIN_HIGH, MAX_HIGH);
    intmap();
}

ShortEstPath_Map::~ShortEstPath_Map()
{
}

int32_t ShortEstPath_Map::getrandomnum(int32_t nmin, int32_t nmax)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(nmin, nmax);
    return distrib(gen);
}

void ShortEstPath_Map::printmap(vector<vector<int32_t> > map)
{
    for (size_t i = 0; i < map.size(); i++)
    {
        if (i == 0)
        {
            for (size_t j = 0; j < map[i].size(); j++)
            {
                if (j == 0)
                {
                    cout << "+";
                }
                cout << "---+";
            }
            cout << endl;
        }
        for (size_t j = 0; j < map[i].size(); j++)
        {
            if (j == 0)
            {
                cout << "|";
            }
            switch(map[i][j])
            {
                case -1:
                    cout << " X |";
                    break;
                case -2:
                    cout << "###|";
                    break;
                case LEFT:
                    cout << "←|";
                    break;
                case RIGHT:
                    cout << "→|";
                    break;
                case UP:
                    cout << "↑|";
                    break;
                case DOWN:
                    cout << "↓|";
                    break;
                default:
                    cout << " " << map[i][j] << " |";
                    break;
            }
        }
        cout << endl;
        for (size_t j = 0; j < map[i].size(); j++)
        {
            if (j == 0)
            {
                cout << "+";
            }
            cout << "---+";
        }
        cout << endl;
    }
}

void ShortEstPath_Map::intmap()
{
    for (int32_t i = 0; i < high; i++)
    {
        vector<int32_t> numsVec;
        vector<int32_t> outVec;
        for (int32_t j = 0; j < lenth; j++)
        {
            numsVec.push_back(getrandomnum(MIN_OBSTACLE, MAX_OBSTACLE));
            outVec.push_back(-2);
        }
        in_map.push_back(numsVec);
        out_map.push_back(outVec);
    }
    in_map[0][0] = 0;
    in_map[high - 1][lenth - 1] = 0;
    set<pair<int32_t, int32_t> > stopSet{{0,0},{high - 1, lenth - 1}};
    do{
        int32_t stop_lenth = getrandomnum(0, lenth - 1);
        int32_t stop_high = getrandomnum(0, high - 1);
        if(stopSet.insert(pair(stop_lenth, stop_high)).second)
        {
            in_map[stop_high][stop_lenth] = -1;
        }
    }while(stopSet.size() < (STOP_NUM + 2));
}

void ShortEstPath_Map::printinmap()
{
    printmap(in_map);
}

void ShortEstPath_Map::printoutmap()
{
    printmap(out_map);
}

bool ShortEstPath_Map::getshortestpath()
{
    vector<vector<int32_t> > inmap = in_map;

    PathStruct pathstruct = dijkstra(inmap, {0,0}, {high - 1, lenth - 1});
    if (pathstruct.emptyflag)
        return false;
    for (size_t i = 0; i < pathstruct.pathvec.size(); i++)
    {
        const int32_t& nhigh = pathstruct.pathvec[i].first;
        const int32_t& nlength = pathstruct.pathvec[i].second;
        int32_t outnum = 0;
        if ( i < pathstruct.turnvec.size())
            outnum = pathstruct.turnvec[i];
        out_map[nhigh][nlength] = outnum;
    }
    return true;
}

PathStruct ShortEstPath_Map::dijkstra(vector<vector<int32_t> >& pathmap, const pair<int32_t, int32_t>& beginpath, const pair<int32_t, int32_t>& endpath)
{
    int32_t npathhigh = beginpath.first;
    int32_t npathleng = beginpath.second;
    int32_t nlength = pathmap[npathhigh][npathleng];   
    priority_queue<PathStruct, vector<PathStruct>, Compare> pq;
    pq.push(PathStruct(npathhigh, npathleng, nlength));
    pathmap[npathhigh][npathleng] = -1;
    do{
        PathStruct shortpath = pq.top();
        npathhigh = shortpath.pathvec.back().first;
        npathleng = shortpath.pathvec.back().second;
        pq.pop();
        if ((size_t)npathleng + 1 < pathmap[npathhigh].size() && pathmap[npathhigh][npathleng + 1] != -1)
        {
            PathStruct newpath = shortpath;
            newpath.AddNextPath(RIGHT, pathmap[npathhigh][npathleng + 1]);
            if (pair<int32_t, int32_t>(npathhigh, npathleng + 1) == endpath)
            {
                return newpath;
            }
            pq.push(newpath);
            pathmap[npathhigh][npathleng + 1] = -1;
        }
        if (npathleng - 1 >= 0 && pathmap[npathhigh][npathleng - 1] != -1)
        {
            PathStruct newpath = shortpath;
            newpath.AddNextPath(LEFT, pathmap[npathhigh][npathleng - 1]);
            if (pair<int32_t, int32_t>(npathhigh, npathleng - 1) == endpath)
            {
                return newpath;
            }
            pq.push(newpath);
            pathmap[npathhigh][npathleng - 1] = -1;
        }
        if ((size_t)npathhigh + 1 < pathmap.size() && pathmap[npathhigh + 1][npathleng] != -1)
        {
            PathStruct newpath = shortpath;
            newpath.AddNextPath(DOWN, pathmap[npathhigh + 1][npathleng]);
            if (pair<int32_t, int32_t>(npathhigh + 1, npathleng) == endpath)
            {
                return newpath;
            }
            pq.push(newpath);
            pathmap[npathhigh + 1][npathleng] = -1;
        }
        if (npathhigh - 1 >= 0 && pathmap[npathhigh - 1][npathleng] != -1)
        {
            PathStruct newpath = shortpath;
            newpath.AddNextPath(UP, pathmap[npathhigh - 1][npathleng]);
            if (pair<int32_t, int32_t>(npathhigh - 1, npathleng) == endpath)
            {
                return newpath;
            }
            pq.push(newpath);
            pathmap[npathhigh - 1][npathleng] = -1;
        }
    }while(pq.size() > 0);
    return PathStruct(true);
}