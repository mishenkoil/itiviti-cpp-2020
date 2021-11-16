#include <iostream>
#include <algorithm>
#include "genome.h"
#include "graph.h"

namespace genome {

    std::string assembly(size_t k, const std::vector<std::string> &reads) {
        if (k == 0 || reads.empty())
            return "";

        Graph graph;
        for (const auto &read_tmp : reads) {
            std::string_view read = read_tmp;
            int step = 0;
            while (step + k != read.size()) {
                Edge edge(read.substr(step, k), read.substr(step + 1, k));
                step++;
                graph.add_edge(edge);

            }
        }
        std::vector<std::string_view> ans_vec = graph.find_euler_path(graph.get_start());
        std::reverse(ans_vec.begin(), ans_vec.end());
        std::string ans;
        for (size_t i = 0; i < ans_vec.size(); ++i) {
            if (i == 0) {
                ans = ans_vec[0];
                continue;
            }
            ans.push_back(ans_vec[i].back());
        }

        return ans;
    }
}
