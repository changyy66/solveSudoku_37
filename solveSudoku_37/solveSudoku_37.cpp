// solveSudoku_37.cpp : 定义控制台应用程序的入口点。
//
/*
编写一个程序，通过已填充的空格来解决数独问题。

一个数独的解法需遵循如下规则：

数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
空白格用 '.' 表示。



一个数独。



答案被标成红色。

Note:

给定的数独序列只包含数字 1-9 和字符 '.' 。
你可以假设给定的数独只有唯一解。
给定数独永远是 9x9 形式的。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sudoku-solver
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<bool>> row(9, vector<bool>(9, false));
vector<vector<bool>> col(9, vector<bool>(9, false));
vector<vector<bool>> matrix(9, vector<bool>(9, false));

bool isEnd = false;
void fill(int n, int i, int j)
{
	row[i][n] = true;
	col[j][n] = true;
	matrix[(i / 3) * 3 + j / 3][n] = true;
}

void remove(int n,int i, int j)
{
	row[i][n] = false;
	col[j][n] = false;
	matrix[(i / 3) * 3 + j / 3][n] = false;
}
bool isValidSudoku(vector<vector<char>>& board) {
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int n;
			switch (board[i][j])
			{
			case '.':
				continue;
			default:
				n = board[i][j] - '1';
			}
			if (row[i][n] || col[j][n] || matrix[(i / 3) * 3 + j / 3][n])
			{
				return false;
			}
			else
			{
				fill(n, i, j);
			}
		}
	}
	return true;
}

//根据三张表，查询[i,j]处可以填充的数字n
bool couldNotFill(int i, int j,int n)
{
	return row[i][n] || col[j][n] || matrix[(i / 3) * 3 + j / 3][n];
}

void backTrack(vector<vector<char>>& board,int i, int j)
{
	if (i==8&&j==9)
	{
		isEnd = true;
		return ;
	}
	if (j==9)
	{
		i++;
		j = 0;
	}
	if (board[i][j]=='.')
	{
		for (size_t n = 0; n < 9; n++)
		{
			if (!couldNotFill(i,j,n))
			{
				fill(n, i, j);
				board[i][j] = n + '1';
				backTrack(board,i,j + 1);
				if (isEnd)return;
				remove(n, i, j);
				board[i][j] = '.';
			}
		}
	}
	else
	{
		backTrack(board, i, j + 1);
	}

}

void solveSudoku(vector<vector<char>>& board) {
	if (!isValidSudoku(board))
	{
		return;
	}
	backTrack(board, 0, 0);
	
	return;
}

int main()
{
	vector<vector<char>> board = {
		{ '.','.','9','7','4','8','.','.','.' },
		{ '7','.','.','.','.','.','.','.','.' },
		{ '.','2','.','1','.','9','.','.','.' },
		{ '.','.','7','.','.','.','2','4','.' },
		{ '.','6','4','.','1','.','5','9','.' },
		{ '.','9','8','.','.','.','3','.','.' },
		{ '.','.','.','8','.','3','.','2','.' },
		{ '.','.','.','.','.','.','.','.','6' },
		{ '.','.','.','2','7','5','9','.','.' }
	};
	solveSudoku(board);
	for each (auto var in board)
	{
		for each (auto it in var)
		{
			cout << it << "|";
		}
		cout << "\r\n";
		cout << "__________________\r\n";
	}
    return 0;
}

