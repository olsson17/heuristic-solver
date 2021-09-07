//returns actions of the computer
#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

class Action
{
    private:
        int source;
        int destination;
        int heuristic;

    public:
        Action(int s, int d):source(s),destination(d) {}
        Action(int s, int d, int h):source(s),destination(d),heuristic(h) {}

        bool operator<(const Action a) const
        {
            if (heuristic< a.heuristic)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        int getSource()
        {
            return source;
        }
        int getDestination()
        {
            return destination;
        }
        int getHeuristic()
        {
            return heuristic;
        }
};

#endif // ACTION_H_INCLUDED
