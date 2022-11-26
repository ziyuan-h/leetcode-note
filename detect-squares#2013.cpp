// Store added points in a map, for every counted point, run throught the map and 
// find diagonals of the square. Since the point is new and repeated points are allowed,
// we need not consider the duplication of squares. 

// Notice we need to provide has function for pairs or vectors in order to use map.

class DetectSquares {
public:
    DetectSquares() {
        
    }
    
    void add(vector<int> point) {
        ++ map[make_pair(point[0], point[1])];
    }
    
    int count(vector<int> point) {
        int cnt{0};
        for (auto const& ptr: map) {
          auto& pt = ptr.first; 
          if (pt.first == point[0] || pt.second == point[1])
              continue;
          if (abs(pt.first - point[0]) != abs(pt.second - point[1]))
              continue;
          int cum{0};
          auto p1 = make_pair(point[0], pt.second);
          auto p2 = make_pair(pt.first, point[1]);
          if (map.find(p1) != map.end() && map.find(p2) != map.end()) {
            cum = map[p1]*map[p2]*ptr.second;
          }
          cnt += cum;
        }
      return cnt;
    }
  
private:
  // A hash function used to hash a pair of any kind
  struct hash_pair {
      template <class T1, class T2>
      size_t operator()(const pair<T1, T2>& p) const
      {
          auto hash1 = hash<T1>{}(p.first);
          auto hash2 = hash<T2>{}(p.second);

          if (hash1 != hash2) {
              return hash1 ^ hash2;             
          }

          // If hash1 == hash2, their XOR is zero.
            return hash1;
      }
  };
  
  unordered_map<pair<int, int>, size_t, hash_pair> map;

};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */
