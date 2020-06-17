#include <cstring> 
#include <iostream>
#include "ArrayStack.h"
using namespace std;

void currentSpot( int* maze[], ArrayStack<node> v, int fx, int fy, int R, int C) {
	node a, b;
	if (v.isEmpty())
		return;
	else {
		v.pop(a);
		if (!v.isEmpty()) {
			v.pop(b);
			if (a.x + 1 < R && maze[a.x + 1][a.y] == 0 && (a.x + 1 != b.x || a.y != b.y))
				a.status++;
			if (a.x - 1 >= 0 && maze[a.x - 1][a.y] == 0 && (a.x - 1 != b.x || a.y != b.y))
				a.status++;
			if (a.y + 1 < C && maze[a.x][a.y + 1] == 0 && (a.x != b.x || a.y + 1 != b.y))
				a.status++;
			if (a.y - 1 >= 0 && maze[a.x][a.y - 1] == 0 && (a.x != b.x || a.y - 1 != b.y))
				a.status++;

			v.push(b);
			v.push(a);
		}
		else{
			if (a.x + 1 < R && maze[a.x + 1][a.y] == 0 )
				a.status++;
			if (a.x - 1 > 0 && maze[a.x - 1][a.y] == 0 )
				a.status++;
			if (a.y + 1 < C && maze[a.x][a.y + 1] == 0 )
				a.status++;
			if (a.y - 1 > 0 && maze[a.x][a.y - 1] == 0 )
				a.status++;

			v.push(a);
		}
	}


	cout << "The Mouse Now is at Spot ( " << a.x << " , " << a.y << " )";
	if (a.x == fx && a.y == fy) {
		cout << "Which Belongs to [Exit] Class" << endl;
		return;
	}
	if (a.status == -1) {
		cout << "Which Belongs to [Dead end] Class" << endl;
		return;
	}
	else if (a.status == 0) {
		cout << "Which Belongs to [Continuing] Class" << endl;
		return;
	}
	else {
		cout << "Which Belongs to [Intersection] Class" << endl;
		return;
	}

}

void printSolution(int* path[], int R, int C)
{
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cout << "    " << path[i][j];
		}
		cout << endl;
	}
}




bool mazeSolver(int* maze[], int* visitedspots[], int* path[], node start, int fx, int fy, int R, int C)
{
	int i = start.x , j = start.y;
	
	ArrayStack<node> s(R*C);

	ArrayStack<node> visited(R * C * R);


	node temp;
	temp.x = i;
	temp.y = j;
	visitedspots[i][j] = 1;
	path[i][j] = 0;
	visited.push(temp);
	currentSpot(maze, visited, fx, fy, R, C);

	s.push(temp);


	while (!s.isEmpty()) { 

		s.peek(temp);
		int d = temp.dir;
		i = temp.x;
		j = temp.y;
		temp.dir++;
		
		node t;
		s.pop(t);
		s.push(temp);


		if (i == fx && j == fy) {
			return true;
		}

		if (d == 0) {
			if (i - 1 >= 0 && maze[i - 1][j] == 0 && visitedspots[i - 1][j] == 0) {

				node temp1;
				temp1.x = i - 1;
				temp1.y = j;
				visitedspots[i - 1][j] = 1;
				path[i - 1][j] = 0;

				s.push(temp1);
				visited.push(temp1);
				currentSpot(maze, visited, fx, fy, R, C);

			}
		}

		else if (d == 1) {
			if (j - 1 >= 0 && maze[i][j - 1] ==0 && visitedspots[i][j - 1] ==0) {
				node temp1;
				temp1.x = i;
				temp1.y = j - 1;
				visitedspots[i][j - 1] = 1;
				path[i][j - 1] = 0;
				

				s.push(temp1);
				visited.push(temp1);
				currentSpot(maze, visited, fx, fy, R, C);

			}
		}

		// Checking the down direction 
		else if (d == 2) {
			if (i + 1 < R && maze[i + 1][j] == 0 && visitedspots[i + 1][j] ==0) {
				node temp1;
				temp1.x = i + 1;
				temp1.y = j ;
				visitedspots[i + 1][j] = 1;
				path[i + 1][j] = 0;

				s.push(temp1);
				visited.push(temp1);
				currentSpot(maze, visited, fx, fy, R, C);

			}
		}
		// Checking the right direction 
		else if (d == 3) {
			if (j + 1 < C && maze[i][j + 1] == 0 && visitedspots[i][j + 1] == 0) {
				node temp1;
				temp1.x = i;
				temp1.y = j + 1;
				visitedspots[i][j + 1] = 1;
				path[i][j + 1] = 0;

				s.push(temp1);
				visited.push(temp1);
				currentSpot(maze, visited, fx, fy, R, C);

			}
		}
		else {

			path[i][j] = 1;
			node t2;
			s.pop(t2);
			visited.pop(t2);

			currentSpot(maze, visited, fx, fy, R, C);

		}
	}
	return false;
}







int main()
{

	node start;
	

	int R = 10; int C = 12; int fx = 4; int fy = 11;


	int** visitedspot = new int* [R];
	for (int i = 0; i < R; ++i)
		visitedspot[i] = new int[C];
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			visitedspot[i][j] = 0;
		}
	}


	int** path = new int* [R];
	for (int i = 0; i < R; ++i)
		path[i] = new int[C];
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			path[i][j] = 1;
		}
	}

	int** maze = new int* [R];
	for (int i = 0; i < R; ++i)
		maze[i] = new int[C];

	maze[0][0] = 1; maze[0][1] = 1; maze[0][2] = 1; maze[0][3] = 1; maze[0][4] = 1; maze[0][5] = 1; maze[0][6] = 1; maze[0][7] = 1; maze[0][8] = 1; maze[0][9] = 1;  maze[0][10] = 1; maze[0][11] = 1;
	maze[1][0] = 1; maze[1][1] = 0; maze[1][2] = 0; maze[1][3] = 0; maze[1][4] = 1; maze[1][5] = 1; maze[1][6] = 0; maze[1][7] = 1; maze[1][8] = 0; maze[1][9] = 1;  maze[1][10] = 0; maze[1][11] = 1;
	maze[2][0] = 1; maze[2][1] = 1; maze[2][2] = 1; maze[2][3] = 0; maze[2][4] = 1; maze[2][5] = 0; maze[2][6] = 0; maze[2][7] = 0; maze[2][8] = 0; maze[2][9] = 0;  maze[2][10] = 0; maze[2][11] = 1;
	maze[3][0] = 1; maze[3][1] = 1; maze[3][2] = 0; maze[3][3] = 0; maze[3][4] = 0; maze[3][5] = 0; maze[3][6] = 1; maze[3][7] = 1; maze[3][8] = 1; maze[3][9] = 1;  maze[3][10] = 0; maze[3][11] = 1;
	maze[4][0] = 1; maze[4][1] = 1; maze[4][2] = 0; maze[4][3] = 1; maze[4][4] = 1; maze[4][5] = 1; maze[4][6] = 1; maze[4][7] = 1; maze[4][8] = 1; maze[4][9] = 1;  maze[4][10] = 0; maze[4][11] = 0;
	maze[5][0] = 1; maze[5][1] = 1; maze[5][2] = 0; maze[5][3] = 1; maze[5][4] = 0; maze[5][5] = 1; maze[5][6] = 1; maze[5][7] = 1; maze[5][8] = 1; maze[5][9] = 1;  maze[5][10] = 1; maze[5][11] = 1;
	
	maze[6][0] = 1; maze[6][1] = 1; maze[6][2] = 0; maze[6][3] = 0; maze[6][4] = 0; maze[6][5] = 1; maze[6][6] = 1; maze[6][7] = 1; maze[6][8] = 1; maze[6][9] = 1;  maze[6][10] = 1; maze[6][11] = 1;
	maze[7][0] = 1; maze[7][1] = 1; maze[7][2] = 1; maze[7][3] = 1; maze[7][4] = 0; maze[7][5] = 1; maze[7][6] = 1; maze[7][7] = 1; maze[7][8] = 0; maze[7][9] = 1;  maze[7][10] = 0; maze[7][11] = 1;
	maze[8][0] = 1; maze[8][1] = 1; maze[8][2] = 0; maze[8][3] = 0; maze[8][4] = 0; maze[8][5] = 0; maze[8][6] = 0; maze[8][7] = 1; maze[8][8] = 0; maze[8][9] = 0;  maze[8][10] = 0; maze[8][11] = 1;
	maze[9][0] = 1; maze[9][1] = 1; maze[9][2] = 1; maze[9][3] = 1; maze[9][4] = 1; maze[9][5] = 1; maze[9][6] = 1; maze[9][7] = 1; maze[9][8] = 1; maze[9][9] = 1;  maze[9][10] = 1; maze[9][11] = 1;
	cout << "Enter Coordinates of the starting point: ";
	cin >> start.x >> start.y;
	while (maze[start.x][start.y] == 1) {
		cout << "This is a black spot! Enter Another Start Spot: ";
		cin >> start.x >> start.y;
	}


	if (mazeSolver(maze, visitedspot, path, start, fx, fy, R, C))  {
		cout << "\n\nPath Found!" << '\n';
		printSolution(path, R, C);

	}
	else
		cout << "\n\nNo Path Found! Trapped!!!!!!" << '\n';


	return 0;
}











