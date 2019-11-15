#include <vector>
#include <algorithm>
#include <exception>
#include <queue>
#include <map>
#include <iostream>

template <typename V>
class Path
{
public:
    Path()
    {
        weight = 0;
    }
    void push(const V &vertex, int weight)
    {
        vertices.push_back(vertex);
        total_weight += weight;
    }
    int weight()
    {
        return total_weight;
    }

    bool operator==(const Path &p2)
    {
        return this->weight() == p2.weight();
    }
    bool operator!=(const Path &p2)
    {
        return this->weight() != p2.weight();
    }
    // comparisons are reversed - shorter path is higher priority
    bool operator<(const Path &p2)
    {
        return this->weight() > p2.weight();
    }
    bool operator>(const Path &p2)
    {
        return this->weight() < p2.weight();
    }
    bool operator<=(const Path &p2)
    {
        return this->weight() >= p2.weight();
    }
    bool operator>=(const Path &p2)
    {
        return this->weight() <= p2.weight();
    }

private:
    std::vector<V> vertices;
    int total_weight;
};



template <typename V>
class Graph
{
public:
    Graph()
    {
    }
    void add_vertex(const V &vertex)
    {
        vertices.push_back(vertex);

        // Now expand the existing adj rows to have a new entry
        // for this vertex - with no edge.
        // Careful not to use the for(auto v: adj) syntax, as it
        // makes v a COPY - we need to really use the iterators.
        for (auto i = adj.begin(); i < adj.end(); i++)
        {
            (*i).push_back(0);
        }

        // A a new "from" row, containing a list of "to" values for
        // each existing  vertex.
        std::vector<int> from(vertices.size());
        adj.push_back(from);
    }

    void add_edge(const V &start, const V &end, int weight = 1)
    {
        int _s = index_of_vertex(start);
        int _e = index_of_vertex(end);
        if (_s < 0 || _e < 0)
        {
            throw std::invalid_argument("Edge cannot be added, start or end vertices do not exist");
        }
        adj[_s][_e] = weight;
    }

    int get_edge(const V &start, const V &end)
    {
        int _s = index_of_vertex(start);
        int _e = index_of_vertex(end);
        if (_s < 0 || _e < 0)
        {
            throw std::invalid_argument("Edge cannot be added, start or end vertices do not exist");
        }
        return adj[_s][_e];
    }

    std::vector<V> adjacent(const V &start)
    {
        std::vector<V> a;
        int _s = index_of_vertex(start);
        if (_s < 0)
        {
            throw std::invalid_argument("Vertext does not exist");
        }
        int i = 0;
        for (auto weight : adj[_s])
        {
            std::cout << weight << std::endl;
            // A weight of 0 means no link between vertices.
            // Alternatively, we could have used -1, to allow
            // cost-free links.
            if (weight > 0)
            {
                a.push_back(vertices[i]);
            }
            i++;
        }
        return a;
    }

    Path<V> shortest_path(const V &start, const V &end)
    {
        std::priority_queue<Path<V>> container;
        auto insert = [&](const Path<V> &path) {
            container.push(path);
        };
        auto expand = [&]() -> V {
            V f = container.top();
            container.pop();
            return f;
        };
        auto is_empty = [&]() -> bool {
            return container.empty();
        };
        return has_path(start, end, insert, expand, is_empty);
    }
    bool depth_first(const V &start, const V &end)
    {

        std::stack<V> container;
        auto insert = [&](const V &v) {
            container.push(v);
        };
        auto expand = [&]() -> V {
            V f = container.top();
            container.pop();
            return f;
        };
        auto is_empty = [&]() -> bool {
            return container.empty();
        };
        return has_path(start, end, insert, expand, is_empty);
    }
    bool breadth_first(const V &start, const V &end)
    {
        std::queue<V> container;
        auto insert = [&](const V &v) {
            container.push(v);
        };
        auto expand = [&]() -> V {
            V f = container.front();
            container.pop();
            return f;
        };
        auto is_empty = [&]() -> bool {
            return container.empty();
        };
        return has_path(start, end, insert, expand, is_empty);
    }

private:
    std::vector<V> vertices;

    // 1 row for each "from" vertex.  Each column of a row is a "to" weight.
    // Ex. adj[3][4] is the cost of going from vertex 4 to vertex 5.
    std::vector<std::vector<int>> adj;

    template <typename Insert, typename Expand, typename Empty>
    bool has_path(const V &start, const V &end, Insert insert, Expand expand, Empty empty)
    {
        std::map<V, bool> visited;

        // initialize all vertices to unvisited.
        for (auto v : vertices)
            visited[v] = false;

        // seed frontier
        insert(start);

        while (!empty())
        {
            V next = expand();
            if (next == end)
                return true;
            else if (!visited[next])
            {
                visited[next] = true;
                // not visited, expand frontier.
                for (auto v : adjacent(next))
                {
                    insert(v);
                }
            }
        }
        return false;
    }

    int index_of_vertex(const V &vertex)
    {
        int i = 0;
        for (auto v : vertices)
        {
            if (v == vertex)
                return i;
            i++;
        }
        return -1;
    }
};