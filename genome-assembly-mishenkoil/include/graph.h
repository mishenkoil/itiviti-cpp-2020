#pragma once

#include <list>
#include <string_view>
#include <vector>
#include <unordered_map>

namespace genome {

// one possible starting point
//
    using Node = std::string_view;

    class Edge {
    public:
        Edge(Node from, Node to);

        const auto &from() const { return m_from; }

        const auto &to() const { return m_to; }

    private:
        Node m_from;
        Node m_to;
    };

    class Graph {
    private:
        struct node_info {
            size_t in;
            std::vector<std::string_view> out_vec;
        };

        std::unordered_map<std::string_view, node_info> adjacency_list;

        void find_path(std::string_view, std::vector<std::string_view> &);

    public:
        void add_edge(Edge edge);

        void print_graph();

        std::string_view get_start();

        std::vector<std::string_view> find_euler_path(std::string_view);
    };

} // namespace genome
