#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//as described in problem
int N, M, P, L;
char instr[101];

bool moved[100][100][4];

signed char tab[100][100]; //map

#define BLOCKED (-1)
#define FREE (0)
#define POSSIBLE (1)

#define STAY -1
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

void dfs(int x, int y, int instr_ind, int mov_cnt );


void read_map()
{
	for (int i = 0; i < M; ++i)
	{
		for (int ii = 0; ii < N; ++ii)
		{
			int buf = getchar();
			tab[ii][i] = (buf=='#') ? BLOCKED : FREE;
		}
		getchar(); //eat the newline
	}
}

void print_map()
{
	for (int i = 0; i < M; ++i)
	{
		for (int ii = 0; ii < N; ++ii)
		{
			switch(tab[ii][i])
			{
				case BLOCKED:
					putchar('#');
				break;

				case FREE:
					putchar('.');
				break;

				case POSSIBLE:
					putchar('X');
				break;
			}
		}
		puts("");
	}
}

void move_wrapper(int x, int y, int instr_ind, int mov_cnt, char move)
{
	switch(move)
	{
		case 'S':
			dfs(x, y, instr_ind+1, mov_cnt );
		break;

		case 'G':

			if(moved[x][y][UP])
				return;

			moved[x][y][UP]=true;
			dfs(x, y-1, instr_ind+1, mov_cnt+1 );
			moved[x][y][UP]=false;

		break;

		case 'D':

			if(moved[x][y][DOWN])
				return;

			moved[x][y][DOWN]=true;
			dfs(x, y+1, instr_ind+1, mov_cnt+1 );
			moved[x][y][DOWN]=false;

		break;

		case 'L':

			if(moved[x][y][LEFT])
				return;

			moved[x][y][LEFT]=true;
			dfs(x-1, y, instr_ind+1, mov_cnt+1 );
			moved[x][y][LEFT]=false;

		break;

		case 'P':

			if(moved[x][y][RIGHT])
				return;

			moved[x][y][RIGHT]=true;
			dfs(x+1, y, instr_ind+1, mov_cnt+1 );
			moved[x][y][RIGHT]=false;

		break;
	}
}

void dfs(int x, int y, int instr_ind, int mov_cnt )
{
	if(x<0 || y<0 || x>= N || y>= M) //out of bounds
		return;

	if(tab[x][y] == BLOCKED) //inaccessible
		return;

	if(mov_cnt > P ) //too far
		return;

	//position is good iff dist is good and we performed every move
	//if instr_ind == L then there are no more instr left
	if(mov_cnt == P && instr_ind == L)
	{
		tab[x][y] = POSSIBLE;
		return;
		//no possible way to move from here, end it
	}

	switch(instr[instr_ind])
	{
		case '?':
			move_wrapper(x, y, instr_ind, mov_cnt, 'G');
			move_wrapper(x, y, instr_ind, mov_cnt, 'D');
			move_wrapper(x, y, instr_ind, mov_cnt, 'L');
			move_wrapper(x, y, instr_ind, mov_cnt, 'P');
			move_wrapper(x, y, instr_ind, mov_cnt, 'S');
		break;

		default:
			move_wrapper(x, y, instr_ind, mov_cnt, instr[instr_ind]);
	}

}


int main()
{
	scanf("%d %d ", &N, &M);
	read_map();
	scanf("%d %d ", &P, &L);
	scanf(" %s", (char*)instr);

	for (int i = 0; i < M; ++i)
		for (int ii = 0; ii < N; ++ii)
			dfs(ii, i, 0, 0);

	print_map();

	return 0;
}