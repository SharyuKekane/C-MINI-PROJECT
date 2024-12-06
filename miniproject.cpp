/* Assignment No. 14
Mini Project:
Project Title: Visual representation of DIJKSTRAS Algoritm

Name : Sharyu Asha Sanjay Kekane 
R.NO : 27 
*/
// program :

#include <iostream>
#include <winbgim.h>
#include <graphics.h>
#include <cmath>
#include <limits.h>
using namespace std;

int nodesX[500], nodesY[500];
int nodeCount = 0;  
int startNode = -1;  
int endNode = -1;    
int adjMatrix[500][500];  // Adjacency matrix to store distances between nodes

const int INF = INT_MAX;  // Infinite distance

void drawNode(int x, int y, int color = BLUE) 
{
    setcolor(color);
    circle(x, y, 10);
    floodfill(x, y, color);  
}

void drawLine(int x1, int y1, int x2, int y2) 
{
    setcolor(RED);
    line(x1, y1, x2, y2);
}

bool isInsideNode(int x, int y, int nodeX, int nodeY) 
{
    int dx = x - nodeX;  
    int dy = y - nodeY;  
    return (dx * dx + dy * dy) <= (10 * 10);  
}

// Function to calculate  distance between two points
int calculateDistance(int x1, int y1, int x2, int y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// Dijkstra's algorithm to find the shortest path
void dijkstra(int startNode, int endNode) 
{
    int dist[500];  // Stores the shortest distances from startNode
    bool visited[500];  // Track visited nodes
    int parent[500];  // Stores the parent of each node to reconstruct the path

    // Initialize distances and visited status
    for (int i = 0; i < nodeCount; i++) 
    {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[startNode] = 0;  // Distance from startNode to itself is 0

    for (int count = 0; count < nodeCount - 1; count++) 
    {
        // Find the node with the minimum distance that has not been visited
        int minDist = INF, u;
        for (int i = 0; i < nodeCount; i++) 
        {
            if (!visited[i] && dist[i] <= minDist) 
            {
                minDist = dist[i];
                u = i;
            }
        }

        // Mark the selected node as visited
        visited[u] = true;

        // Update the distances of adjacent nodes
        for (int v = 0; v < nodeCount; v++) 
        {
            if (!visited[v] && adjMatrix[u][v] && dist[u] != INF && dist[u] + adjMatrix[u][v] < dist[v]) 
            {
                dist[v] = dist[u] + adjMatrix[u][v];
                parent[v] = u;  // Store parent to reconstruct the path
            }
        }
    }

    // Reconstruct the shortest path
    int currentNode = endNode;
    while (parent[currentNode] != -1) 
    {
        // Draw the shortest path line in green
        drawLine(nodesX[currentNode], nodesY[currentNode], nodesX[parent[currentNode]], nodesY[parent[currentNode]]);
        currentNode = parent[currentNode];
    }

    if (dist[endNode] == INF) 
    {
        outtextxy(250, 220,"No path exists between the start and end nodes");
    }
    else 
    {
        char buffer[50];
        sprintf(buffer, "Shortest distance: %d", dist[endNode]);
        outtextxy(250, 240, buffer);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);  

    // Initialize adjacency matrix to 0 (no edges)
    for (int i = 0; i < 500; i++) 
    {
        for (int j = 0; j < 500; j++) 
        {
            adjMatrix[i][j] = 0;
        }
    }

    outtextxy(250, 100, "Draw the graph:");
    outtextxy(250, 120, "Right click to add nodes, left click to draw lines");

    while (true) 
    {
        if (ismouseclick(WM_RBUTTONDOWN)) 
        {
            int x = mousex();
            int y = mousey();
            clearmouseclick(WM_RBUTTONDOWN);
            drawNode(x, y);   
            nodesX[nodeCount] = x; 
            nodesY[nodeCount] = y;  
            nodeCount++;  
        }

        if (ismouseclick(WM_LBUTTONDOWN)) 
        {
            int x = mousex();
            int y = mousey();
            clearmouseclick(WM_LBUTTONDOWN);

            for (int i = 0; i < nodeCount; i++) 
            {
                if (isInsideNode(x, y, nodesX[i], nodesY[i])) 
                {
                    if (startNode == -1) 
                    {
                        startNode = i;  
                    } 
                    else 
                    {
                        drawLine(nodesX[startNode], nodesY[startNode], nodesX[i], nodesY[i]);
                        // Add distance to adjacency matrix
                        int distance = calculateDistance(nodesX[startNode], nodesY[startNode], nodesX[i], nodesY[i]);
                        adjMatrix[startNode][i] = distance;
                        adjMatrix[i][startNode] = distance;  // Since it's an undirected graph
                        startNode = -1;  
                    }
                    break;
                }
            }
        }

        if (kbhit()) 
        {
            char key = getch();
            if (key == 13) 
            {
                outtextxy(250, 140, "Select the start node by clicking on it");
                while (true) 
                {
                    if (ismouseclick(WM_LBUTTONDOWN)) 
                    {
                        int x = mousex();
                        int y = mousey();
                        clearmouseclick(WM_LBUTTONDOWN);

                        for (int i = 0; i < nodeCount; i++) 
                        {
                            if (isInsideNode(x, y, nodesX[i], nodesY[i])) 
                            {
                                startNode = i;
                                drawNode(nodesX[i], nodesY[i], GREEN);  
                                outtextxy(250, 160, "Start node selected");
                                break;
                            }
                        }
                        if (startNode != -1) break;
                    }
                }
            }

            if (key == 13) 
            {
                outtextxy(250, 180, "Select the end node by clicking on it");
                while (true) 
                {
                    if (ismouseclick(WM_LBUTTONDOWN)) 
                    {
                        int x = mousex();
                        int y = mousey();
                        clearmouseclick(WM_LBUTTONDOWN);

                        for (int i = 0; i < nodeCount; i++) 
                        {
                            if (isInsideNode(x, y, nodesX[i], nodesY[i])) 
                            {
                                endNode = i;
                                drawNode(nodesX[i], nodesY[i], RED);  
                                outtextxy(250, 200, "End node selected");
                                break;
                            }
                        }
                        if (endNode != -1) break;
                    }
                }

                // Run Dijkstra's algorithm to find the shortest path
                dijkstra(startNode, endNode);
            }

            if (key == 27) break;  
        }

        delay(10);  
    }

    closegraph();  
    return 0;
}
