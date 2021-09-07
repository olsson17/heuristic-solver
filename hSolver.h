#ifndef HhSolver_H_INCLUDED
#define HhSolver_H_INCLUDED

//h solver is the solver with heuristics
class hSolver
{
    private:
        State *currentState;
        Goal goal;
        //vector to store previous moves
        vector<State> prevMoves;
        int steps;
    public:
        hSolver(State *, Goal);
        void solve();
        bool checkPrevMoves(State*);
        void getActions(State*, priority_queue<Action>& );
        int getHeuristic( State* tempState, int source, int destination);
        int getSteps(){return steps;}

};

hSolver::hSolver(State *s, Goal g)
{
    currentState = s;
    goal=g;
    solve();
}

void hSolver::solve()
{
    if(currentState->checkGoal(goal.getRow(),goal.getColumn(),goal.getBlock()))
        return;

    steps=0;

    while(steps<100)
    {
        if(currentState->checkGoal(goal.getRow(),goal.getColumn(),goal.getBlock()))
        {
            cout <<"goal ";
            goal.printGoal();
            cout<< " found at: "<<steps<<" steps"<<endl;
            currentState->printBoard();
            return;
        }
        priority_queue<Action> actionQueue;
        steps++;

        prevMoves.push_back(*currentState);
        getActions(currentState, actionQueue);

        if(!actionQueue.empty())
        {
            Action a = actionQueue.top();
            cout<<endl<<"chosen action:("<<a.getSource()<<", "<<a.getDestination()<<", "<<a.getHeuristic()<<")"<<endl;

            currentState->moveBlock(a.getSource(),a.getDestination());
            currentState->printBoard();
        }
        else
        {
            cout<<"no more actions";
            return;
        }

    }
}

void hSolver::getActions(State *s, priority_queue<Action>& actionQueue)
{
    cout <<"actions:";
    for(int x = 0; x<BOARDSIZE; x++ )
    {
        for(int y=0; y<BOARDSIZE;y++)
        {
            State *tempState = new State(*s);

            if(tempState->moveBlock(x,y))
            {
                int h = getHeuristic(tempState, x, y);
                Action a = Action(x,y,h);

                actionQueue.push(a);
                cout <<"("<<x<<", "<<y<<", "<<h<<")";
            }
        }
    }
}

bool hSolver::checkPrevMoves(State* s)
{
	for(unsigned int looker=0; looker<prevMoves.size(); looker++)
    {
        if (*s==prevMoves[looker])
            return true;
    }
	return false;
}



int hSolver::getHeuristic( State* tempState, int source, int destination)
{
    int h=0;
    if(tempState->checkGoal(goal.getRow(),goal.getColumn(),goal.getBlock()))
    {
        return 100;
    }

    if(checkPrevMoves(tempState))
    {
        return 0;
    }

    if(tempState->isBlockTop(goal.getBlock()))
        h+=50;

    if(tempState->goalPositionReady(goal.getRow(),goal.getColumn()))
        h+=40;

    if(tempState->removeBlockOnTopBlock(goal.getBlock(), source))
        h+=30;

    if(tempState->removeBlockOnTopGoal(goal.getRow(),goal.getColumn(), source)){
        h+=20;
    }
    if(tempState->addBlockUnderGoal(goal.getRow(),goal.getColumn(),destination)){
        h+=10;
    }
    return h;
 }


#endif // HhSolver_H_INCLUDED
