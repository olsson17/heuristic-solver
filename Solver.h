#ifndef SOLVER_H_INCLUDED
#define SOLVER_H_INCLUDED
#include "action.h"

//solver just solves by making legitimate actions and not repeating states
class Solver
{
    private:
        //creates object of State to store current state
        State *currentState;
        //creates an object of goal to store the goal
        Goal goal;
        //vector to store all previous states
        vector<State> prevMoves;
    public:
        //constructor to take a state and a goal
        Solver(State *, Goal);
        //function to solve from the state and the goal
        void solve();
        //function to check previous moves
        bool checkPrevMoves(State*);
        //function to get the actions possibe
        void getActions(State*, queue<Action>& );
};
//construtor
Solver::Solver(State *s, Goal g)
{
    currentState = s;
    goal=g;
    solve();
}

//solver
void Solver::solve()
{
    //checks if goal has already been achived
    if(currentState->checkGoal(goal.getRow(),goal.getColumn(),goal.getBlock()))
        return;
    //records number of steps
    int steps=0;
    //while loop to solve and keep under 100 steps
    while(steps<100)
    {
    //checks if goal state has been achieved
        if(currentState->checkGoal(goal.getRow(),goal.getColumn(),goal.getBlock()))
        {
            cout <<"goal ";
            goal.printGoal();
            cout<< " found at: "<<steps<<" steps"<<endl;
            currentState->printBoard();
            return;
        }
        //actiion queue to store all possible actions in next step
        queue<Action> actionQueue;
        //adds step
        steps++;
        //adds current state to prevmoves vector
        prevMoves.push_back(*currentState);
        //gets actions for next step
        getActions(currentState, actionQueue);
        //if theirs more actions next action in the queue will be used otherwise return
        if(!actionQueue.empty())
        {
            Action a = actionQueue.front();
            cout<<endl<<a.getSource()<<", "<<a.getDestination()<<endl;
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

//function to get possible actions for the current state without using a previous state
void Solver::getActions(State *s, queue<Action>& actionQueue)
{
    cout <<"actions:";
    for(int x = 0; x<BOARDSIZE; x++ )
    {
        for(int y=0; y<BOARDSIZE;y++)
        {
            State *tempState = new State(*s);

            if(tempState->moveBlock(x,y))
            {
                if(!checkPrevMoves(tempState))
                {
                Action a = Action(x,y);
                actionQueue.push(a);
                cout <<"("<<x<<", "<<y<<")";
                }
            }
        }
    }
}

//function to check all previous moves to the current state
bool Solver::checkPrevMoves(State* s)
{
	for(unsigned int looker=0; looker<prevMoves.size(); looker++) 
    {
        if (*s==prevMoves[looker])
            return true;
    }
	return false;
}
#endif // SOLVER_H_INCLUDED
