// STEP1: find the best place to interpolate the new interval; STEP2: discuss what intervals 
// to erase and where to insert the new interval. There are several cases listed as
// "CASE" in the script. Assume every interval is in the form ["start", "end"].

vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
  // trivial case
  if (intervals.empty()) return {newInterval};
  auto orderStart = [](const vector<int>& left, const vector<int>& right) {
    return left[0] < right[0];
  };
  auto orderEnd = [](const vector<int>& left, const vector<int>& right) {
    return left[1] < right[1];
  };

  // find the first interval whose "start" is larger than that of "newInterval"
  auto first_iter = lower_bound(intervals.begin(), intervals.end(), 
                                newInterval, orderStart);
  // find the first interval whose "end" is larger than that of "newInterval"
  auto last_iter = lower_bound(intervals.begin(), intervals.end(),
                                newInterval, orderEnd);
  // "first_iter" and "last_iter" are candidates of elimination, need to refine
  // according to the discussions below.
  
  // CASE: the start "newInterval" is larger than "starts" of all other intervals.
  if (first_iter == intervals.end()) {
    if (intervals.back()[1] < newInterval[0]) {
      intervals.push_back(newInterval);
    } else {
      intervals.back()[1] = max(intervals.back()[1], newInterval[1]);
    }
      return intervals;
  } 
  
  // CASE: the start of "newInterval" is smaller than the "start" of "first_iter"
  // but also smaller than the "end" of "first_iter-1". Thus, we have to deduct 
  // "first_iter" by 1 and re-assign the "start" of "newInterval" by the "start" of
  // "first_iter".
  if (first_iter != intervals.begin() && 
      (*(first_iter - 1))[1] >= newInterval[0]) {
      newInterval[0] = min(newInterval[0], (*(first_iter - 1))[0]);
      --first_iter;
  }
  
    // CASE: the end of "newInterval" is smaller than the "end" of "last_iter"
  // but also larger than latter's "start". Thus, we have to increase 
  // "last_iter" by 1 and re-assign the "end" of "newInterval" by the "end" of
  // "last_iter".
  if (last_iter != intervals.end() &&
     (*(last_iter))[0] <= newInterval[1]) {
    newInterval[1] = max(newInterval[1], (*last_iter)[1]);
    ++last_iter;
  } 
  auto pos = intervals.erase(first_iter, last_iter);
  intervals.insert(pos, newInterval);
  return intervals;
  }
