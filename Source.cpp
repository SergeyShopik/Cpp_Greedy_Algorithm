#include<iostream>
using namespace std;
struct tochka
{
    int source;
    bool flag;
};
const int Size = 5;
void init(tochka* a)
{
    for (int i = 0; i < Size; i++)
    {
        a[i].flag = false;
    }
}
int mincost(tochka* array, int graph[][Size], int searchindex)
{
    int min = INT_MAX;
    int index = -1;
    for (size_t i = 0; i < Size; i++)
    {
        if (graph[searchindex][i] != 0 && array[i].flag == 0)
        {
            if (graph[searchindex][i] < min)
            {
                index = i;
                min = graph[searchindex][i];
            }
        }
    }
    return index;
}
int cost(int start, int  graph[][Size], tochka array[])
{
    int cost = 0;

    int index, count = 0;

    while (count < Size)
    {
        for (size_t i = 0; i < Size; i++)
        {
            if (array[i].source == start)
            {
                index = i;
            }
        }
        cost += graph[array[index].source][index];
        start = index;
        count++;
    }

    return cost;
}
void printroad(tochka array[], int start)
{
    int index, count = 0;

    while (count < Size)
    {
        for (size_t i = 0; i < Size; i++)
        {
            if (array[i].source == start)
            {
                index = i;
            }
        }
        cout << "(" << start << "," << index << ")";
        start = index;
        count++;
    }
}
void greedy(int graph[][Size], int start, tochka array[])
{
    array[start].flag = 1;
    int  step = mincost(array, graph, start);
    int start1 = start;
    while (step != -1)
    {
        array[step].source = start;
        start = step;
        array[start].flag = 1;

        step = mincost(array, graph, start);
    }
    array[start1].source = start;
}
void localSearch(int graph[][Size], int start, tochka solution[], int rep)
{
    int globstart = start;
    tochka NewSolution[Size];
    int help[3];

    for (size_t i = 0; i < rep; i++)
    {
        for (size_t i = 0; i < Size; i++)
        {
            NewSolution[i] = solution[i];
        }
        int index, count = 0;
        int temp = start;
        int j = 0;
        while (count < 3)
        {
            for (size_t i = 0; i < Size; i++)
            {
                if (NewSolution[i].source == start)
                {
                    index = i;
                    help[j++] = index;
                }
            }
            start = index;
            count++;
        }
        NewSolution[help[1]].source = temp;
        NewSolution[help[0]].source = help[1];
        NewSolution[index].source = help[0];

        printroad(NewSolution, globstart);
        cout << cost(globstart, graph, NewSolution) << endl;
        if (cost(temp, graph, NewSolution) < cost(temp, graph, solution))
        {
            for (size_t i = 0; i < Size; i++)
            {
                solution[i] = NewSolution[i];
            }
        }

        for (size_t i = 0; i < Size; i++)
        {
            if (solution[i].source == temp)
            {
                start = i;
            }
        }
    }
}

int main()
{
    int  graph[Size][Size] = {
      {0,10,25,25,10},
      {1,0,10,15,2},
      {8,9,0,20,10},
      {14,10,24,0,15},
      {10,8,25,27,0},

    };
    tochka array[Size];
    init(array);
    greedy(graph, 0, array);
    printroad(array, 0);
    cout << cost(0, graph, array) << endl;
    localSearch(graph, 0, array, 10);

    tochka array1[Size];
    init(array1);
    greedy(graph, 1, array1);
    printroad(array1, 1);
    cout << cost(1, graph, array1) << endl;


    system("pause");
    return 0;
}