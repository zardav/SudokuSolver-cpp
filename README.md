# SudokuSolver-cpp
Sudoku Solver written with c++, without gui.
## Usage
### Just solve
```sh
solve rows
```
Where `rows` is sudoku board printed in one line without spaces, row by row. For empty slots any char that is not between '1' and '9' and not white space is acceptable.
For example:
```sh
solve 123456789456789---78912345-------------------------------------------------------
```
The result is written to standard output in the same format of input.
### Solve with animation
```sh
animate rows
```
Here the result is all the operations of solving, line by line, in the format `(row, column, value)` 
