#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>


class directedGraph {
    std::vector<std::vector<int>> adjacency;
public:
    void addNode(int a); //construieste si/sau modifica lista de adiacenta
    void addEdge(int source, int target); //construieste si/sau modifica lista de adiacenta
    bool hasEdge(int source, int target); // return 1 daca exista muchie
    void BFS(int startNode); //afiseaza nodurile; folosind o coada; puteti folosi librarii
    void DFS(int startNode); //afiseaza nodurile; folosind o recursie e ok
    int twoCycles(); //numara si intoarce cate 2-cicluri sunt in graf; [3->5 , 5->3] este un 2-ciclu
};

void directedGraph::addNode(int node) {
    while (adjacency.size() < static_cast<unsigned>(node+1)) {
        adjacency.push_back(std::vector<int>());
    }
}

void directedGraph::addEdge(int source, int target) {
    if (adjacency.size() > static_cast<unsigned>(source) and adjacency.size() > static_cast<unsigned>(target)) {
        std::vector<int>::iterator it;
        for (it = adjacency[source].begin(); it != adjacency[source].end(); it++) {
            if (*it > target) {
                break;
            }
        }
        adjacency[source].insert(it, target);
    }
}

bool directedGraph::hasEdge(int source, int target) {
    if (adjacency.size() > static_cast<unsigned>(source) and adjacency.size() > static_cast<unsigned>(target)) {
        int left = 0, right = adjacency[source].size()-1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (mid == target) {
                return 1;
            } else if (mid < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return 0;
}

void directedGraph::BFS(int startNode) {
    std::queue<int> queue;
    std::vector<bool> visited(adjacency.size());
    queue.push(startNode);
    while (!queue.empty()) {
        int node = queue.front();
        if (visited[node] == false) {
            std::cout << node << " ";
            visited[node] = true;
            for (std::vector<int>::iterator it = adjacency[node].begin(); it != adjacency[node].end(); it++) {
                if (visited[*it] == false) {
                    queue.push(*it);
                }
            }
        }
        queue.pop();
    }
}

void directedGraph::DFS(int startNode) {
    std::stack<int> stack;
    std::vector<bool> visited(adjacency.size());
    stack.push(startNode);
    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();
        if (visited[node] == false) {
            std::cout << node << " ";
            visited[node] = true;
            for (std::vector<int>::reverse_iterator it = adjacency[node].rbegin(); it != adjacency[node].rend(); it++) {
                if (visited[*it] == false) {
                    stack.push(*it);
                }
            }
        }
    }
}

int directedGraph::twoCycles() {
    int cycles = 0;
    for (int node = 0; static_cast<unsigned>(node) < adjacency.size(); node++) {
        for (std::vector<int>::iterator it = adjacency[node].begin(); it != adjacency[node].end(); it++) {
            if (*it > node and hasEdge(node, *it) and hasEdge(*it, node)) {
                cycles++;
            }
        }
    }
    return cycles;
}

int main()
{
    directedGraph graf;
    graf.addNode(6);
    graf.addEdge(0, 1);
    graf.addEdge(0, 6);
    graf.addEdge(1, 2);
    graf.addEdge(2, 0);
    graf.addEdge(2, 3);
    graf.addEdge(2, 4);
    graf.addEdge(3, 4);
    graf.addEdge(4, 2);
    graf.addEdge(4, 5);
    graf.addEdge(5, 0);
    graf.addEdge(6, 4);
    graf.BFS(0); std::cout << "\n\n";
    graf.DFS(2); std::cout << "\n\n";
    std::cout << graf.twoCycles();
    

    return 0;
}

