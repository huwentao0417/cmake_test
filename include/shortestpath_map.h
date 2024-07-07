#pragma once
#include<vector>
#include<stdint.h>
using namespace std;

#define MAX_LENTH 20
#define MIN_LENTH 1
#define MAX_HIGH 20
#define MIN_HIGH 1
#define MAX_OBSTACLE 9
#define MIN_OBSTACLE 1
#define STOP_NUM 6

#define TURN_LEFT "←"
#define TURN_RIGHT "→"
#define TURN_UP "↑"
#define TURN_DOWN "↓"

enum TURN_ENUM
{
    LEFT = 11,
    RIGHT,
    UP,
    DOWN
};

struct PathStruct
{
    vector<pair<int32_t, int32_t> > pathvec;
    vector<TURN_ENUM> turnvec;
    int32_t num;
    bool emptyflag;
    PathStruct(const int32_t& nhigh, const int32_t& nlength, const int32_t& nnum)
    :num(nnum)
    {
        pathvec.push_back(pair<int32_t, int32_t>(nhigh,nlength));
        emptyflag = false;  
    }
    PathStruct(bool isempty)
    {
        emptyflag = isempty;
    }
    void AddNextPath(const TURN_ENUM turnenum, const int32_t& nnum)
    {
        auto path = pathvec.back();
        switch(turnenum)
        {
            case LEFT:
                path.second--;
                break;
            case RIGHT:
                path.second++;
                break;
            case UP:
                path.first--;
                break;
            case DOWN:
                path.first++;
                break;
            default:
                return;
        }
        pathvec.push_back(path);
        turnvec.push_back(turnenum);
        num += nnum;
    }
    PathStruct operator+(const PathStruct& ps)
    {
        PathStruct pathSruct = *this;
        pathSruct.pathvec.insert(pathSruct.pathvec.end(), ps.pathvec.begin(), ps.pathvec.end());
        pathSruct.num += ps.num;
        return pathSruct;
    }
};

struct Compare
{
    bool operator()(const PathStruct &lhs, const PathStruct &rhs) const
    {
        return lhs.num > rhs.num;
    }
};

class ShortEstPath_Map
{
public:
    ShortEstPath_Map();
    virtual ~ShortEstPath_Map();
    void printinmap();
    void printoutmap();
    bool getshortestpath();

private:
    void intmap();
    int32_t getrandomnum(int32_t nmin, int32_t nmax);
    void printmap(vector<vector<int32_t> > map);
    //
    PathStruct dijkstra(vector<vector<int32_t> >& pathmap, const pair<int32_t, int32_t>& beginpath, const pair<int32_t, int32_t>& endpath);

private:
    vector<vector<int32_t> > in_map;
    vector<vector<int32_t> > out_map;
    int32_t lenth;
    int32_t high;

};