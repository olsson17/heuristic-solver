//stores and checks if goal is complete
#ifndef GOAL_H_INCLUDED
#define GOAL_H_INCLUDED

class Goal
{
    private:
        int row;
        int column;
        int block;
    public:
        Goal(){};
        void getGoal()
        {
            cout<<"Input a goal in the format (block, row, col):"<<endl;
            cout<<"Block (1 - 6): ";
            cin>>block;
            while(block>6 || block<1)
            {
                cout<<block<<" not valid enter block between 1 and 6";
                cin>>block;
            }
            cout<<"Row (0 - 2 bottom-up): ";
            cin>>row;
            while(row>2 || row<0)
            {
                cout<<row<<" not valid enter row between 0 and 2";
                cin>>row;
            }
            cout<<"Column (0 - 2 left-right): ";
            cin>>column;

            while(column>2 || column<0)
            {
                cout<<column<<" not valid enter column between 0 and 2";
                cin>>column;
            }
        }
        bool operator==(Goal g) 
        {
            if(g.block == block)
                return true;
            if(g.row==row &&g.column==column)
                return true;
            return false;
        }


        void printGoal()
        {
            cout <<"("<<block<<", "<<row<<", "<<column<<")"; 
        }

        int getRow()    {return row;}
        int getColumn() {return column;}
        int getBlock()  {return block;}
};


#endif // GOAL_H_INCLUDED
