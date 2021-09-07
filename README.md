# heuristic-solver  
SHRDLU was created in the late 1960s by Terry Wingrad. It was used to demonstrate how AI technologies could be used in natural language processing.   
Mini-SHRDLU was inspired by SHRDLU, it is a game designed by Google deepmind for testing for their AI algorithms.  
  * This version of the game contains 6 numbered blocks(1-6) on a 3x3 board.   
  * All blocks have to be distributed on along the columns of the board, their can only be space on the top of the columns.  
  * Blocks on the top of a column can be moved from its column to the top of another column if space is available.  
  * At the beginning the board is randomly configured this is the *initial state*  
  * The game is given a goal or a set of goals were a certain block has to reach a certain position  
  * When the game is at a configuration with all goals achieved this is the *goal state*  
The following is an example of a board in the *initial state* and another in a *goal state* with the goal of block:2 row:0 column:0   

initial state:  
```
 |   | 4 |   |  
 | 6 | 3 |   |  
 | 1 | 5 | 2 |  
  --- --- ---
```
goal state:  
```
 |   |   | 1 |  
 |   | 3 | 6 |  
 | 2 | 5 | 4 |  
  --- --- ---  
 ```
