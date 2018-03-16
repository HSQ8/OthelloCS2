#Othello AI

Caltech CS2 Assignment 9: Othello

See [assignment9_part1.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/othello/blob/master/assignment9_part1.html) and [assignment9_part2.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/othello/blob/master/assignment9_part2.html)


Contribution by group member
Hongsen Qin:
Implemented a semi working version of minimax
Worked with daniel to fix errors in minimax
Made changes to java files and implemented test script so we can run
massive amounts of experiments and acquire bot statistics

Implemented Heuristics:
Ring weight
corner cases
Mobility
Potential Mobility

Fined tuned heuristics used in minimax.



Daniel Neamati:
Split board heuristics and move heuristics.
Fine tuned heuristic catagories.
Worked with Hongsen to implement the random move and simple move functions.
Worked with Hongsen to implement the heuristic functions.

Implemented Heuristics:
Basic score
Stability
Number of pieces flipped
Adjusted heuristic weights and board location weights

Debugged Minimax to compare board states
Implemented alpha-beta pruning

Made the bot time-aware



Improvements to group's AI to make it competition worthy:
    Our group implemented Alpha Beta Pruning to make deep search possible.
Our bot currently sees 7 moves ahead (depending on the time). We also adjusted
and implemented a powerful heuristics that can beat Constant Time player 
without any minimax tree search. Our bot is able to keep track of time to 
maximize the depth it searches without exceeding the time limit. 

