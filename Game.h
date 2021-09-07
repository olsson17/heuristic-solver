#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <iostream>
#include <vector>
#include <stdio.h>
#include "State.h"
#include "Goal.h"
#include "Solver.h"
#include "hSolver.h"

//the class game runs the game and asks what sover you want to run
class Game
{
    private:

    public:
        //constructor
        Game() {}
        //function to play the game
        void playGame();
        //checks for the same goal used with multiple goals
        bool checkForSame(Goal, vector<Goal>);
};

//function to play game
void Game::playGame()
{
    int n;
    //asks what solver to run
    cout<<"choose a level to run:"<<endl<<"1. Single goal solver without heuristics"<<endl
        <<"2. Single goal solver with heuristics"<<endl<<"3. Disjunctive goal solver"<<endl<<
        "4. Conjunctive goal solver"<<endl<</*"5. n*n board and 'x' blocks with conjunctive goal Solver"<<endl<<*/
        "7. Quit"<<endl;
    //gets input of what solver to run
    cin>>n;


    //switch statement to use the input from the user to get the right solver
    switch (n)
    {

        //solver that takes a single goal and solves it without heuristics by not using previous moves
        case 1:
        {
            //gets initial game state
            State *s = new State();
            //prints initial game state
            cout<< "first state: "<<endl;
            s->printBoard();
            //gets goal
            Goal g;
            g.getGoal();
            //print goal
            cout<< "search for goal";
            g.printGoal();
            //solves goal
            Solver solve(s, g);
            //returns
            return;
        }

        //solves a single goal with heurstics
        case 2:
        {
            //gets initial game state
            State *s = new State();
            //prints initial game state
            cout<< "first state: "<<endl;
            s->printBoard();
            //gets goal
            Goal g;
            g.getGoal();
            //print goal
            cout<< "search for goal";
            g.printGoal();
        //solves goal
            hSolver solve(s, g);
            return;
        }

        //solves disjunctive goals gets multiple goals from the user and trys to solve one
        case 3:
        {

            //gets initial game state
            State *s = new State();
            //prints initial game state
            cout<< "first state: "<<endl;
            s->printBoard();
            //gets goal
            vector<Goal> disjunctive;

            //loop to get multiple goals
            char more='y';
            while (more == 'y')
            {
                //initializersan object of goal g
                Goal g;
                //calls function get goal from user
                g.getGoal();
                //checks if goal has been used before
                if (checkForSame(g, disjunctive))
                {
                    //adds to goal vector
                    disjunctive.push_back(g);
                    cout<<"if you want to enter another goal enter y or just press any letter"<<endl;
                }
                else
                {
                    cout<<"goal used the same block or position as previous goal press y to add another or any letter to search for goal"<<endl;
                }
                cin >> more;
            }
            //print goals
            cout<< "search for goal(s): "<<endl;
            for(unsigned int i= 0; i<disjunctive.size(); i++)
            {
                disjunctive[i].printGoal();
            }
            cout<<endl;

            //solves goals when one is successful the program stops
            for(unsigned int i= 0; i<disjunctive.size(); i++)
            {
                hSolver solve(s, disjunctive[i]);
                if(s->checkGoal(disjunctive[i].getRow(),disjunctive[i].getColumn(), disjunctive[i].getBlock()))
                {
                    cout<<"found at "<< solve.getSteps()<<"steps";
                    return;
                }
            }
        }
        //solves conjunctive goals gets multiple goals from the user then solves them till their all solved in one state
        case 4:
        {

            //gets initial game state
            State *s = new State();
            //prints initial game state
            cout<< "first state: "<<endl;
            s->printBoard();
            //gets goal
            vector<Goal> conjunctive;

            //loop to get multiple goals
            char more='y';
            while (more == 'y')
            {
                //initializersan object of goal g
                Goal g;

                //calls function get goal from user
                g.getGoal();

                //checks if goal has been used before
                if (checkForSame(g, conjunctive))
                {
                    //adds to goal vector
                    conjunctive.push_back(g);
                    cout<<"if you want to enter another goal enter y or just press any letter"<<endl;
                }
                else
                {
                    cout<<"goal used the same block or position as previous goal press y to add another or any letter to search for goal"<<endl;
                }
                cin >> more;
            }
            
            //print goals
            cout<< "search for goal(s): "<<endl;
            for(unsigned int i= 0; i<conjunctive.size(); i++)
            {
                conjunctive[i].printGoal();
            }
            cout<<endl;
            //stores total steps
            int conTotSteps=0;
            //stores if all goals are found
            bool allFound= false;
            //loop to solve goals that stops when all goals are achieved
            while (!allFound)
            {
                //integer to store how many goals are found
                unsigned int goalsFound=0;

                //loop to solve all goals in the goal vector
                for(unsigned int i= 0; i<conjunctive.size(); i++)
                {
                    //call to solver to solve goal i int the vector
                    hSolver solve(s, conjunctive[i]);

                    //counts steps that have taken
                    conTotSteps+=solve.getSteps();
                    //if over 100 steps have been taken the loop breaks
                    if(conTotSteps>=100)
                    {
                        break;
                    }
                }
                //loop to check if all goals have been satisfied in the single state
                for(unsigned int i= 0; i<conjunctive.size(); i++)
                {
                    //calls the state function check goal to see if the goal is right
                    if(s->checkGoal(conjunctive[i].getRow(),conjunctive[i].getColumn(), conjunctive[i].getBlock()))
                    {
                        goalsFound+=1;
                    }
                }

                //if to many steps have been taken the loop breaks
                if(conTotSteps>=100)
                {
                    break;
                }
                //if int goals found equals the amount of goals their are all found is set true
                if(goalsFound== conjunctive.size())
                    allFound=true;
            }

            //if all found equlas true prints message and how many steps
            if(allFound == true)
            {
                cout<<"found all goals: ";
                for(unsigned int i= 0; i<conjunctive.size(); i++)
                {
                    conjunctive[i].printGoal();
                }
                cout<< " at "<< conTotSteps <<" steps";

            }
            else
            {
                cout<<"couldnt find goals before 100 steps";
            }
            return;
        }
    }
}
bool Game::checkForSame(Goal g, vector<Goal> conjun)
{
    for(unsigned int i = 0; i<conjun.size(); i++)
    {
        if(g==conjun[i])
            return false;
    }
    return true;
}
#endif // GAME_H_INCLUDED
