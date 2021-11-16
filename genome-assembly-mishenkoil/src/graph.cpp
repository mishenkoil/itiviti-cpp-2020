#include <iostream>
#include "graph.h"

namespace genome {

    Edge::Edge(Node from, Node to) : m_from(from), m_to(to) {
    }

    void Graph::add_edge(Edge edge) {
        if (adjacency_list.find(edge.from()) == adjacency_list.end()) {
            adjacency_list[edge.from()] = {0, std::vector<std::string_view>(0)};
        }
        if (adjacency_list.find(edge.to()) == adjacency_list.end()) {
            adjacency_list[edge.to()] = {0, std::vector<std::string_view>(0)};
        }
        adjacency_list[edge.from()].out_vec.push_back(edge.to());
        adjacency_list[edge.to()].in++;
    }

    void Graph::print_graph() {
        for (const auto &node : adjacency_list) {
            std::cout << node.first << ": ";
            for (auto connected_node : node.second.out_vec) {
                std::cout << connected_node << " ";
            }
            std::cout << std::endl;
            std::cout << "IN: " << node.second.in << " OUT: " << node.second.out_vec.size() << std::endl;
        }
    }

    std::string_view Graph::get_start() {
        for (const auto &node : adjacency_list) {
            if (node.second.in < node.second.out_vec.size()) {
                return node.first;
            }
        }
        return "some-useless-text";
    }

    void Graph::find_path(std::string_view start, std::vector<std::string_view> &path) {
        auto element = adjacency_list.find(start);
        while (!element->second.out_vec.empty()) {
            auto temp = element->second.out_vec.back();
            element->second.out_vec.pop_back();
            element = adjacency_list.find(temp);
            path.push_back(element->first);
        }
    }

    std::vector<std::string_view> Graph::find_euler_path(std::string_view start) {
        std::vector<std::string_view> path;
        std::vector<std::string_view> euler_path;
        auto element = adjacency_list.find(start);
        path.push_back(element->first);

        while (!path.empty()) {
            element = adjacency_list.find(path.back());
            if (element->second.out_vec.empty()) {
                euler_path.push_back(element->first);
                path.pop_back();
            } else {
                find_path(element->first, path);
            }
        }
        return euler_path;
    }

} // namespace genome
