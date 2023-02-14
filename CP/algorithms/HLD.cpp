int N, R, P; // R = root, P = number of paths
    vector<int> par;
    vector< vector<int> > G; // sons
    vector< pair<int, int> > interval_renumbering;
    vector<int> v_from_interval_id;
    vector<int> subtree_size;
    vector< vector<int> > paths;
    vector<int> path_id, path_pos; // paths[path_id[i]][path_pos[i]] == i
    vector< vector< vector< pair<int, int> > > > down_edges; // light edges (child, index in tree) + dummy self-loops
    vector<int> down_edge_id;
    vector< vector<int> > last_down_edge; // largest index of light edge from (parent) + 1
 
    vector<wgt> W;
    IntervalTree max_dist_down;
    vector<IntervalTree> tree_over_path;
 
    void DFS_construct(int v, const vector< vector< pair<int, wgt> > > & G_) {
        interval_renumbering[v].second = interval_renumbering[v].first+1;
        v_from_interval_id[interval_renumbering[v].first] = v;
        subtree_size[v] = 1;
        int max_subtree_size = 0, son_in_path = -1;
        for(auto p : G_[v]) if(par[p.first] == -1) {
            int w = p.first;
            par[w] = v;
            G[v].push_back(w);
            W[w] = p.second;
            interval_renumbering[w].first = interval_renumbering[v].second;
            DFS_construct(w, G_);
            interval_renumbering[v].second = interval_renumbering[w].second;
            max_dist_down.add(interval_renumbering[w].first, interval_renumbering[w].second, p.second);
            subtree_size[v] += subtree_size[w];
            if(subtree_size[w] > max_subtree_size) {
                max_subtree_size = subtree_size[w];
                son_in_path = w;
            }
        }
        if(son_in_path == -1) {
            path_id[v] = P++;
            paths.push_back({});
        }
        else path_id[v] = path_id[son_in_path];
        paths[path_id[v]].push_back(v);
    }
