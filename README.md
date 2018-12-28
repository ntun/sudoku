# Solving sudoku using constraint elimination

This program attempts to solve a 9x9 well-formed sudoku puzzle using purely ''constraint elimination''. By well-formed, I mean that there is only one unique solution for the puzzle, with [at least 16 clues given](https://en.wikipedia.org/wiki/Mathematics_of_Sudoku#Maximum_number_of_givens). Norvig has also written this method in Python, and he rather calls it as [constraint propagation](http://norvig.com/sudoku.html).

There are two types of constraints that I look for in this program. They are:
- lone constraint
- can-only-fit-in-one (COFIO) constraint

This program is still not yet complete, in a sense that it cannot solve all Sudoku puzzles. It can only solve "easy" to "medium" sudoku puzzles since harder puzzles require more advanced techniques (without a naive backtracking solution).

# Basics of Sudoku

Sudoku is a game involving so many constraints. A sudoku puzzle involves 9 rows, 9 columns, and 9 subsquares. There are are total of 81 blocks, and a player has to fill a number of 1 to 9 in all of those blocks without any repetition of numbers appearing in their corresponding row, column, or subsquare. See [Simple Wiki's Sudoku article](https://simple.wikipedia.org/wiki/Sudoku) for more information.

# Motivation

Why am I building this whole 9x9 Sudoku-solver program when I can just easily hard-code backtracking algorithm? Yes, that would give me a solution but that's not how a person would normally solve. The golden rule of solving Sudoku by hand is to __never guess__ and backtracking does a lot of guessing. If I am to apply backtracking with pencil and paper, I would have to erase so many times on a sheet of paper. That's not what I want. My goal is to solve Sudoku puzzle without making a single guess or erase. I am trying to write a program that will solve a 9x9 sudoku puzzle like a pro, not in a naive brute-force way. 

# Constraint elimination

Each (empty) block has constraints in the form of numbers that appear in the same row, column, and subsquare. We can eliminate those numbers among the choices of numbers to fill in that empty block. We will call the row, column, and subsquare that a particular block belongs to as its __domain__.

For instance, an empty block would originally have numbers 1 to 9 to fill in as an option. If number 1 appears somewhere in its domain, then, the options would be 2-9 only because 1 cannot be filled in the block anymore as per the Sudoku rules. We will apply such ''constraint elimination'' rules throughout this program.

## Lone Constraint

When solving any puzzles, we should always look for an "easy" or "obvious" answers first, and for Sudoku, those are lone constraints.

Lone constraints are the empty blocks which only have a single choice to fill in. For instance, if numbers 1-8 has already appeared in the domain of the empty block, the only option left for the block is 9. Thus, 9 must be the empty block's value. If we consider a constraint for each empty block as a set, then, we are looking for empty blocks whose constraint size is one. Throughout this program, we searched for lone constraints first to solve the easier parts of the Sudoku puzzle.

## COFIO Constraint

In contrast to lone constraints, can-only-fit-in-one constraints refer to comparing multiple constraints of empty blocks within the same domain and searching for a __single__ constraint that belong in only one empty block. In other words, if we consider constraints for each empty block as a set, we are looking for a __single__ non-intersecting constraint within the same domain.

To give an example, let there be 3 empty block, A, B, C in a particular domain. Block A has {2, 3, 4} has its constraints; block B has {2, 3}; block C has {2, 3}. Here, we cannot apply lone constraints because the size of all constraint sets in the domain are greater than one. But here, we can see that 4 appears only in block A's constraint once. Thus, we know that 4 must appear only in block A, for it cannot appear in any remaining empty blocks within the domain.

Of course, COFIO constraint method does not work when there are more than one non-intersecting constraints. If block A's constraint set was {2, 3, 4, 5}, this wouldn't have worked since A would still be left with 2 options {4, 5} after "elimination" of constraints by COFIO method. Again, the golden rule of sudoku puzzle is to _never guess_, unless we are employing backtracking algorithm, which is not the case for this program. For dealing with multiple constraints choices like this, more advanced techniques such as X-Wing, XY-Wing, Swordfish, etc can be used to apply more "constraint elimination".

## Nested Elimination

The aforementioned two methods can be used in order to "trigger" more eliminations.


### Nested lone constraint

Consider the scenerio where there are three empty blocks A, B, C in a particular domain. Block A's constraint set is {2, 3, 4}; B's is {2, 3}; C's is {2}. The program searches for lone constraints first, and it finds one for C. Thus, C's value is 2. This eliminates 2 from constraint sets of A and B. Thus, A's constraint set is now {3, 4}; B's is {3}. B has a lone constraint now, and B value must be 3. This gives arise to another lone constraint when A's constraint set becomes just {4}. Therefore, solving one lone constraint can solve multiple lone constraints.

### Nested COFIO

Consider the scenario where there are four empty blocks A, B, C, D in a particular domain. Block A's constraint set is {2, 3, 5}; B's is {2, 3, 4}; C's is {2, 4}; D's is {2, 4}. The program will search for lone constraints first, and there is none in this case. So, COFIO method is applied. We found 5 as a COFIO constraint, and thus, A's value is 5. This results in just B, C, D as empty blocks in the domain. This rises in another COFIO constraint in B. Therefore, we can see solving one COFIO could potentially create another COFIO.

### Upper bound for nested operations

If these nested operations can give arise to multiple subsolutions of the puzzle (which is what this program is doing), I wonder about the upper bound fo the number of iterations needed in order to fully solve the puzzle. I am not able to come up with such an upper bound, but I suspect it would require some deep mathematical analysis. It could be a research topic that anyone interested in Sudoku could take on.

# Future Contributions

I plan to add more non-naive "solve-by-hand" techniques such as X-Wing, XY-Wing, Swordfish, etc into the solver so that it solves __all__ well-formed Sudoku puzzles.

# Contact

If anyone has question or feedback, feel free to reach out to me at ntun@iwu.edu.
