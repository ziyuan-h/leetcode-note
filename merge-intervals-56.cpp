// STEP1: sort the intervals by the starting number; STEP2: merge the intervals sequentially.
// Every interval pulled out of "intervals" in STEP2 should have starting number less than the starting number of "meged.back()".

vector<vector<int>> merge(vector<vector<int>>& intervals) {
  // sorting order
  auto order = [](const vector<int>& left, const vector<int>& right)->bool{
    return left[0] < right[0];
  };
  sort(intervals.begin(), intervals.end(), order);
  // result vector
  vector<vector<int>> merged{};
  merged.push_back(intervals.front());
  for (int i{1}; i < intervals.size(); ++ i) {
    auto& cur_intv = intervals[i];
    if (cur_intv[0] > merged.back()[1]) {
      merged.push_back(cur_intv);
    } else if (cur_intv[1] > merged.back()[1]) {
      merged.back()[1] = cur_intv[1]; 
    }
  }
  return merged;
}
