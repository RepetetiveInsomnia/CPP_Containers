#include <gtest/gtest.h>

#include <array>
#include <list>
#include <queue>
#include <vector>

#include "../s21_containers.h"
#include "../s21_containersplus.h"

// setTest
TEST(set, ConstructorDefaultSet) {
  s21::set<int> my_empty_set;
  std::set<int> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
}

TEST(set, ConstructorInitializerSet) {
  s21::set<int> mySet({'x', 'b', 'z', 'y'});
  std::set<int> origSet({'x', 'b', 'z', 'y'});
  EXPECT_EQ(mySet.size(), origSet.size());
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (; myIt != mySet.end(); ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(set, ConstructorInitializer2Set) {
  s21::set<int> mySet = {};
  std::set<int> origSet = {};
  EXPECT_EQ(mySet.size(), origSet.size());
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (; myIt != mySet.end(); ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(set, ConstructorCopySet) {
  const s21::set<int> mySet({1, 2, 3, 4, 5});
  const std::set<int> origSet({1, 2, 3, 4, 5});
  s21::set<int> mySetCopy = mySet;
  std::set<int> origSetCopy = origSet;
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (; myIt != mySetCopy.end(); ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(set, OperatorCopySet) {
  const s21::set<int> mySet({1, 2, 3, 4, 5});
  const std::set<int> origSet({1, 2, 3, 4, 5});
  s21::set<int> mySetCopy;
  std::set<int> origSetCopy;
  mySetCopy = mySet;
  origSetCopy = origSet;
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (; myIt != mySetCopy.end(); ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(set, ConstructorMoveSet) {
  s21::set<int> mySet({1, 2, 3, 4, 5});
  std::set<int> origSet({1, 2, 3, 4, 5});
  s21::set<int> mySetCopy = std::move(mySet);
  std::set<int> origSetCopy = std::move(origSet);
  EXPECT_EQ(mySet.size(), origSet.size());
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (; myIt != mySetCopy.end(); ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(set, OperatorMoveSet) {
  s21::set<int> mySet({1, 2, 3, 4, 5});
  std::set<int> origSet({1, 2, 3, 4, 5});
  s21::set<int> mySetCopy;
  std::set<int> origSetCopy;
  mySetCopy = std::move(mySet);
  origSetCopy = std::move(origSet);
  EXPECT_EQ(mySet.size(), origSet.size());
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (; myIt != mySetCopy.end(); ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(set, SetIteratorsSet) {
  s21::set<int> mySet({1, 2, 3, 4, 5});
  std::set<int> origSet({1, 2, 3, 4, 5});
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  EXPECT_TRUE(*origIt == *myIt);
}

TEST(set, CapacitySet) {
  s21::set<int> my_empty_set;
  std::set<int> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('b');
  orig_empty_set.insert('c');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(set, ClearSet) {
  s21::set<int> my_empty_set;
  std::set<int> orig_empty_set;
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('a');
  orig_empty_set.insert('b');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(set, InsertSet) {
  s21::set<int> mySet({1, 2, 3, 4, 5});
  std::set<int> origSet({1, 2, 3, 4, 5});
  auto myPr = mySet.insert(6);
  auto origPr = origSet.insert(6);
  EXPECT_TRUE(myPr.second == origPr.second);
  EXPECT_TRUE(*myPr.first == *origPr.first);
  myPr = mySet.insert(7);
  origPr = origSet.insert(7);
  EXPECT_TRUE(myPr.second == origPr.second);
  EXPECT_TRUE(*myPr.first == *origPr.first);
}

TEST(set, EraseSet) {
  s21::set<int> mySet({5, 4, 3, 2, 7, 8, 9});
  std::set<int> origSet({5, 4, 3, 2, 7, 8, 9});

  mySet.erase(mySet.begin());
  origSet.erase(origSet.begin());
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (; myIt != mySet.end(); ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(set, SwapSet) {
  s21::set<int> mySet({1});
  s21::set<int> mySwapSet({3, 4, 5});

  mySet.swap(mySwapSet);
  EXPECT_EQ(mySet.size(), 3ul);
  EXPECT_EQ(mySwapSet.size(), 1ul);
  EXPECT_EQ(mySet.size(), 3ul);
  EXPECT_EQ(mySwapSet.size(), 1ul);
  auto mySetIt = mySet.begin();
  auto mySwapSet_it = mySwapSet.begin();
  EXPECT_EQ(*mySetIt, 3);
  EXPECT_EQ(*mySwapSet_it, 1);
}

TEST(set, MergeSet) {
  s21::set<int> mySet({1});
  s21::set<int> myMergeSet({3, 4, 5});
  mySet.merge(myMergeSet);

  std::set<int> origSet({1});
  std::set<int> origMergeSet({3, 4, 5});
  origSet.merge(origMergeSet);
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (; myIt != mySet.end(); ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
  EXPECT_EQ(origSet.size(), mySet.size());
  EXPECT_EQ(myMergeSet.size(), origMergeSet.size());
}

TEST(set, FindSet) {
  s21::set<int> mySet({1, 2, 3, 4, 5});
  std::set<int> origSet({1, 2, 3, 4, 5});
  auto myIt = mySet.find(4);
  auto origIt = origSet.find(4);
  EXPECT_TRUE(*origIt == *myIt);
}

TEST(set, ContainsSet) {
  s21::set<int> mySet({1, 2, 3, 4, 5});
  EXPECT_FALSE(mySet.contains(8));
  EXPECT_TRUE(mySet.contains(2));
}

TEST(set, Find) {
  s21::set<int> s1({1, 2, 3});
  auto itEnd = s1.end();
  auto itAns = s1.begin();
  ++itAns;
  auto it1 = s1.find(2);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = s1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(set, ConstFind) {
  const s21::set<int> s1({1, 2, 3});
  auto itEnd = s1.end();
  auto itAns = s1.begin();
  ++itAns;
  auto it1 = s1.find(2);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = s1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(set, MaxSize) {
  s21::set<int> s1({1, 2, 3});
  s21::set<int> s2({1, 2, 3});
  EXPECT_EQ(s1.max_size(), s2.max_size());
}

TEST(set, InsertMany) {
  s21::set<int> s1({1, 2, 3});
  s1.insert_many(4, 5, 6);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));
}
// multisetTest
TEST(multiset, ConstructorDefaultSet) {
  s21::multiset<int> my_empty_set;
  std::multiset<int> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
}

TEST(multiset, ConstructorInitializerSet) {
  s21::multiset<int> mySet({6, 2, 2, 9, 9, 9, 7, 7, 7, 7});
  std::multiset<int> origSet({6, 2, 2, 9, 9, 9, 7, 7, 7, 7});
  EXPECT_EQ(mySet.size(), origSet.size());
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, ConstructorInitializer2Set) {
  s21::multiset<int> mySet = {};
  std::multiset<int> origSet = {};
  EXPECT_EQ(mySet.size(), origSet.size());
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, ConstructorCopySet) {
  const s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  const std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  s21::multiset<int> mySetCopy = mySet;
  std::multiset<int> origSetCopy = origSet;
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, OperatorCopySet) {
  const s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  const std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  s21::multiset<int> mySetCopy;
  std::multiset<int> origSetCopy;
  mySetCopy = mySet;
  origSetCopy = origSet;
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, ConstructorMoveSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  s21::multiset<int> mySetCopy = std::move(mySet);
  std::multiset<int> origSetCopy = std::move(origSet);
  EXPECT_EQ(mySet.size(), origSet.size());
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (size_t i = 0, n = origSetCopy.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, OperatorMoveSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  s21::multiset<int> mySetCopy;
  std::multiset<int> origSetCopy;
  mySetCopy = std::move(mySet);
  origSetCopy = std::move(origSet);
  EXPECT_EQ(mySet.size(), origSet.size());
  EXPECT_EQ(mySetCopy.size(), origSetCopy.size());
  auto myIt = mySetCopy.begin();
  auto origIt = origSetCopy.begin();
  for (size_t i = 0, n = origSetCopy.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, SetIteratorsSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  EXPECT_TRUE(*origIt == *myIt);
}

TEST(multiset, CapacitySet) {
  s21::multiset<int> my_empty_set;
  std::multiset<int> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('b');
  orig_empty_set.insert('c');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(multiset, ClearSet) {
  s21::multiset<int> my_empty_set;
  std::multiset<int> orig_empty_set;
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('a');
  orig_empty_set.insert('b');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(multiset, InsertSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto myIt = mySet.insert(6);
  auto origIt = origSet.insert(6);
  EXPECT_TRUE(*myIt.first == *origIt);
  EXPECT_TRUE(*myIt.first == *origIt);
  myIt = mySet.insert(7);
  origIt = origSet.insert(7);
  origIt = origSet.insert(7);
  EXPECT_TRUE(*myIt.first == *origIt);
}

TEST(multiset, EraseSet) {
  s21::multiset<int> mySet({5, 5, 4, 4, 4, 3, 2, 2, 7, 7, 7, 8, 9, 9});
  std::multiset<int> origSet({5, 5, 4, 4, 4, 3, 2, 2, 7, 7, 7, 8, 9, 9});

  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  for (size_t i = 0; i < 4; ++i, ++myIt, ++origIt)
    ;
  mySet.erase(myIt);
  origSet.erase(origIt);

  EXPECT_EQ(mySet.size(), origSet.size());
  myIt = mySet.begin();
  origIt = origSet.begin();
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt) {
    EXPECT_TRUE(*origIt == *myIt);
  }
}

TEST(multiset, SwapSet) {
  s21::multiset<int> mySet({1, 1, 1});
  s21::multiset<int> mySwapSet({3, 3, 3, 4, 4, 5});

  mySet.swap(mySwapSet);
  EXPECT_EQ(mySet.size(), 6ul);
  EXPECT_EQ(mySwapSet.size(), 3ul);
  EXPECT_EQ(mySet.size(), 6ul);
  EXPECT_EQ(mySwapSet.size(), 3ul);
  auto mySetIt = mySet.begin();
  auto mySwapSet_it = mySwapSet.begin();
  EXPECT_EQ(*mySetIt, 3);
  EXPECT_EQ(*mySwapSet_it, 1);
}

TEST(multiset, MergeSet) {
  s21::multiset<int> mySet({1, 1, 1});
  s21::multiset<int> myMergeSet({3, 3, 3, 4, 4, 5});
  mySet.merge(myMergeSet);

  std::multiset<int> origSet({1, 1, 1});
  std::multiset<int> origMergeSet({3, 3, 3, 4, 4, 5});
  origSet.merge(origMergeSet);

  auto myIt = mySet.begin();
  auto origIt = origSet.begin();
  EXPECT_EQ(myMergeSet.size(), origMergeSet.size());
  ASSERT_EQ(origSet.size(), mySet.size());
  for (size_t i = 0, n = origSet.size(); i < n; ++i, ++myIt, ++origIt)
    EXPECT_TRUE(*origIt == *myIt);
}

TEST(multiset, FindSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto myIt = mySet.find(4);
  auto origIt = origSet.find(4);
  EXPECT_TRUE(*origIt == *myIt);
}

TEST(multiset, ContainsSet) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  EXPECT_FALSE(mySet.contains(8));
  EXPECT_TRUE(mySet.contains(2));
}

TEST(multiset, Find) {
  s21::multiset<int> s1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itEnd = s1.end();
  auto itAns = s1.begin();
  for (size_t i = 0; i < 4; ++i, ++itAns)
    ;
  auto it1 = s1.find(3);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = s1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(multiset, ConstFind) {
  const s21::multiset<int> s1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itEnd = s1.end();
  auto itAns = s1.begin();
  for (size_t i = 0; i < 4; ++i, ++itAns)
    ;
  auto it1 = s1.find(3);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = s1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(multiset, Count) {
  s21::multiset<int> mySet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  std::multiset<int> origSet({1, 1, 1, 2, 3, 3, 4, 5, 5});
  EXPECT_EQ(mySet.count(1), origSet.count(1));
  EXPECT_EQ(mySet.count(2), origSet.count(2));
  EXPECT_EQ(mySet.count(3), origSet.count(3));
  EXPECT_EQ(mySet.count(4), origSet.count(4));
  EXPECT_EQ(mySet.count(5), origSet.count(5));
  EXPECT_EQ(mySet.count(8), origSet.count(8));
}

TEST(multiset, EqualRange_1) {
  const s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto range1 = ms1.equal_range(3);
  auto itAns1 = ms1.begin();
  for (size_t i = 0; i < 4; ++i, ++itAns1)
    ;
  auto itAns2 = ms1.begin();
  for (size_t i = 0; i < 6; ++i, ++itAns2)
    ;
  EXPECT_TRUE(range1.first == itAns1);
  EXPECT_TRUE(range1.second == itAns2);
}

TEST(multiset, EqualRange_2) {
  s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto range1 = ms1.equal_range(5);
  auto itAns1 = ms1.begin();
  for (size_t i = 0; i < 7; ++i, ++itAns1)
    ;
  EXPECT_TRUE(range1.first == itAns1);
  EXPECT_TRUE(range1.second == ms1.end());
}

TEST(multiset, EqualRange_3) {
  const s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto range1 = ms1.equal_range(1);
  auto itAns2 = ms1.begin();
  for (size_t i = 0; i < 3; ++i, ++itAns2)
    ;
  EXPECT_TRUE(range1.first == ms1.begin());
  EXPECT_TRUE(range1.second == itAns2);
}

TEST(multiset, LowerBound_1) {
  const s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itRes = ms1.lower_bound(3);
  auto itAns = ms1.begin();
  for (size_t i = 0; i < 4; ++i, ++itAns)
    ;
  EXPECT_TRUE(itRes == itAns);
}

TEST(multiset, LowerBound_2) {
  s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itRes = ms1.lower_bound(1);
  auto itAns = ms1.begin();
  EXPECT_TRUE(itRes == itAns);
}

TEST(multiset, UpperBound_1) {
  const s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itRes = ms1.upper_bound(3);
  auto itAns = ms1.begin();
  for (size_t i = 0; i < 6; ++i, ++itAns)
    ;
  EXPECT_TRUE(itRes == itAns);
}

TEST(multiset, UpperBound_2) {
  s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itRes = ms1.upper_bound(1);
  auto itAns = ms1.begin();
  for (size_t i = 0; i < 3; ++i, ++itAns)
    ;
  EXPECT_TRUE(itRes == itAns);
}

TEST(multiset, UpperBound_3) {
  s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  auto itRes = ms1.upper_bound(5);
  auto itAns = ms1.end();
  EXPECT_TRUE(itRes == itAns);
}

TEST(multiset, MaxSize) {
  s21::multiset<int> ms1({1, 1, 1, 2, 3, 3, 4, 5, 5});
  s21::multiset<int> ms2({1, 1, 1, 2, 3, 3, 4, 5, 5});
  EXPECT_EQ(ms1.max_size(), ms2.max_size());
}
// mapTest
TEST(map, ConstructorDefaultMap) {
  s21::map<int, int> my_empty_sap;
  std::map<int, int> origEmptyMap;
  EXPECT_EQ(my_empty_sap.empty(), origEmptyMap.empty());
}

TEST(map, ConstructorInitializerMap) {
  s21::map<int, int> myMap({{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}});
  std::map<int, int> origMap({{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}});
  EXPECT_EQ(myMap.size(), origMap.size());
  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(map, ConstructorInitializer2Map) {
  s21::map<int, int> myMap = {};
  std::map<int, int> origMap = {};
  EXPECT_EQ(myMap.size(), origMap.size());
  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(map, ConstructorCopyMap) {
  const s21::map<int, int> myMap({{1, 2}, {3, 4}, {5, 6}});
  const std::map<int, int> origMap({{1, 2}, {3, 4}, {5, 6}});
  s21::map<int, int> myMapCopy = myMap;
  std::map<int, int> origMapCopy = origMap;
  EXPECT_EQ(myMapCopy.size(), origMapCopy.size());
  auto myIt = myMapCopy.begin();
  auto origIt = origMapCopy.begin();
  for (; myIt != myMapCopy.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(map, ConstructorMoveMap) {
  s21::map<int, int> myMap({{1, 2}, {3, 4}, {5, 6}});
  std::map<int, int> origMap({{1, 2}, {3, 4}, {5, 6}});
  s21::map<int, int> myMapCopy = std::move(myMap);
  std::map<int, int> origMapCopy = std::move(origMap);
  EXPECT_EQ(myMap.size(), origMap.size());
  EXPECT_EQ(myMapCopy.size(), origMapCopy.size());
  auto myIt = myMapCopy.begin();
  auto origIt = origMapCopy.begin();
  for (; myIt != myMapCopy.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(map, MapOperator) {
  s21::map<int, int> myMap({{10, 1}, {20, 2}, {30, 3}});
  std::map<int, int> origMap({{10, 1}, {20, 2}, {30, 3}});
  myMap[10] = 11;
  origMap[10] = 11;
  origMap[20] = 22;
  EXPECT_TRUE(myMap[10] == origMap[10]);
  EXPECT_FALSE(myMap[20] == origMap[20]);
  EXPECT_TRUE(myMap[30] == origMap[30]);
}

TEST(map, MapAtOperatorException) {
  s21::map<int, int> myMap({{10, 1}, {20, 2}, {30, 3}});
  EXPECT_THROW(myMap.at('g') = 1, std::out_of_range);
}

TEST(map, MapAtOperator) {
  s21::map<int, int> myMap({{10, 1}, {20, 2}, {30, 3}});
  std::map<int, int> origMap({{10, 1}, {20, 2}, {30, 3}});
  myMap.at(10) = 11;
  origMap.at(10) = 11;
  origMap.at(20) = 22;
  EXPECT_TRUE(myMap[10] == origMap[10]);
  EXPECT_FALSE(myMap[20] == origMap[20]);
  EXPECT_TRUE(myMap[30] == origMap[30]);
}

TEST(map, MapAtConstOperator) {
  const s21::map<int, int> myMap({{10, 1}, {20, 2}, {30, 3}});
  const std::map<int, int> origMap({{10, 1}, {20, 2}, {30, 3}});
  EXPECT_TRUE(myMap.at(10) == origMap.at(10));
  EXPECT_TRUE(myMap.at(20) == origMap.at(20));
  EXPECT_TRUE(myMap.at(30) == origMap.at(30));
  EXPECT_ANY_THROW(myMap.at(40));
}

TEST(map, MapCapacity) {
  s21::map<int, int> myMap;
  std::map<int, int> origMap;
  EXPECT_TRUE(myMap.empty() == origMap.empty());
  myMap.insert(10, 1);
  EXPECT_FALSE(myMap.empty() == origMap.empty());
  EXPECT_EQ(myMap.size(), 1ul);
  EXPECT_EQ(myMap.size(), 1ul);
}

TEST(map, MapClear) {
  s21::map<int, int> myMap;
  std::map<int, int> origMap;
  myMap.clear();
  origMap.clear();
  EXPECT_EQ(myMap.empty(), origMap.empty());
  myMap.insert(std::make_pair(1, 1));
  origMap.insert(std::make_pair(1, 1));
  EXPECT_EQ(myMap.empty(), origMap.empty());
  myMap.clear();
  origMap.clear();
  EXPECT_EQ(myMap.empty(), origMap.empty());
}

TEST(map, MapInsert1) {
  s21::map<int, int> myMap;
  std::map<int, int> origMap;
  myMap.insert(std::make_pair(1, 'a'));
  myMap.insert(std::make_pair(2, 'a'));
  myMap.insert(std::make_pair(3, 'a'));
  origMap.insert(std::make_pair(1, 'a'));
  origMap.insert(std::make_pair(2, 'a'));
  origMap.insert(std::make_pair(3, 'a'));

  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }

  auto pr1 = myMap.insert(std::make_pair(1, 'a'));
  auto pr2 = origMap.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert2) {
  s21::map<int, int> myMap;
  std::map<int, int> origMap;
  myMap.insert(1, 'a');
  myMap.insert(2, 'a');
  myMap.insert(3, 'a');
  origMap.insert(std::make_pair(1, 'a'));
  origMap.insert(std::make_pair(2, 'a'));
  origMap.insert(std::make_pair(3, 'a'));

  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }

  auto pr1 = myMap.insert(1, 'a');
  auto pr2 = origMap.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert3) {
  s21::map<int, int> myMap;
  std::map<int, int> origMap;
  myMap.insert(1, 'a');
  myMap.insert(2, 'a');
  myMap.insert(3, 'a');
  origMap.insert(std::make_pair(1, 'a'));
  origMap.insert(std::make_pair(2, 'a'));
  origMap.insert(std::make_pair(3, 'a'));

  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }

  auto pr1 = myMap.insert_or_assign(1, 'b');
  auto i = origMap.begin();
  EXPECT_TRUE((*pr1.first).first == (*i).first);
  EXPECT_FALSE((*pr1.first).second == (*i).second);
}

TEST(map, MapInsert4) {
  s21::map<int, int> myMap;
  std::map<int, int> origMap;

  auto origPair = origMap.insert_or_assign(1, 'b');
  auto pr1 = myMap.insert_or_assign(1, 'b');

  EXPECT_TRUE(pr1.first->first == origPair.first->first);
  EXPECT_TRUE(pr1.first->second == origPair.first->second);
  EXPECT_TRUE(pr1.second == origPair.second);
}

TEST(map, MapErase_1) {
  s21::map<int, int> myMap({{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}});
  std::map<int, int> origMap({{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}});
  EXPECT_EQ(myMap.size(), origMap.size());
  myMap.erase(myMap.begin());
  origMap.erase(origMap.begin());
  EXPECT_EQ(myMap.size(), origMap.size());
  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(map, MapErase_2) {
  s21::map<int, int> myMap({{5, 50},
                            {7, 70},
                            {4, 40},
                            {3, 30},
                            {8, 80},
                            {1, 10},
                            {2, 20},
                            {6, 60},
                            {9, 90}});
  std::map<int, int> origMap({{5, 50},
                              {7, 70},
                              {4, 40},
                              {3, 30},
                              {8, 80},
                              {1, 10},
                              {2, 20},
                              {6, 60},
                              {9, 90}});
  EXPECT_EQ(myMap.size(), origMap.size());
  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (size_t i = 0; i < 4; ++i, ++myIt, ++origIt)
    ;
  myMap.erase(myIt);
  origMap.erase(origIt);
  EXPECT_EQ(myMap.size(), origMap.size());
  myIt = myMap.begin();
  origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(map, MapErase_3) {
  s21::map<int, int> myMap({{5, 50},
                            {7, 70},
                            {4, 40},
                            {3, 30},
                            {8, 80},
                            {1, 10},
                            {2, 20},
                            {6, 60},
                            {9, 90}});
  std::map<int, int> origMap({{5, 50},
                              {7, 70},
                              {4, 40},
                              {3, 30},
                              {8, 80},
                              {1, 10},
                              {2, 20},
                              {6, 60},
                              {9, 90}});
  EXPECT_EQ(myMap.size(), origMap.size());
  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (size_t i = 0; i < 8; ++i, ++myIt, ++origIt)
    ;
  myMap.erase(myIt);
  origMap.erase(origIt);
  EXPECT_EQ(myMap.size(), origMap.size());
  myIt = myMap.begin();
  origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(map, MapErase_4) {
  s21::map<int, int> myMap({{1, 10}, {3, 30}, {2, 20}});
  std::map<int, int> origMap({{1, 10}, {3, 30}, {2, 20}});
  EXPECT_EQ(myMap.size(), origMap.size());
  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (size_t i = 0; i < 2; ++i, ++myIt, ++origIt)
    ;
  myMap.erase(myIt);
  origMap.erase(origIt);
  EXPECT_EQ(myMap.size(), origMap.size());
  myIt = myMap.begin();
  origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(map, MapErase_5) {
  s21::map<int, int> myMap({{3, 30}, {1, 10}, {2, 20}});
  std::map<int, int> origMap({{3, 30}, {1, 10}, {2, 20}});
  EXPECT_EQ(myMap.size(), origMap.size());
  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (size_t i = 0; i < 2; ++i, ++myIt, ++origIt)
    ;
  myMap.erase(myIt);
  origMap.erase(origIt);
  EXPECT_EQ(myMap.size(), origMap.size());
  myIt = myMap.begin();
  origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
}

TEST(map, SwapMap) {
  s21::map<int, int> myMap({{1, 1}});
  s21::map<int, int> mySwapMap({{3, 3}, {4, 4}});

  myMap.swap(mySwapMap);
  EXPECT_EQ(myMap.size(), 2ul);
  EXPECT_EQ(mySwapMap.size(), 1ul);
  EXPECT_EQ(myMap.size(), 2ul);
  EXPECT_EQ(mySwapMap.size(), 1ul);
  auto x = myMap.begin();
  auto y = mySwapMap.begin();
  EXPECT_EQ((*x).first, 3);
  EXPECT_EQ((*y).first, 1);
}

TEST(map, MergeMap) {
  s21::map<int, int> myMap({{1, 1}, {4, 4}, {2, 2}});
  s21::map<int, int> myMapMerge({{3, 3}, {4, 4}});

  std::map<int, int> origMap({{1, 1}, {4, 4}, {2, 2}});
  std::map<int, int> origMapMerge({{3, 3}, {4, 4}});

  myMap.merge(myMapMerge);
  origMap.merge(origMapMerge);

  EXPECT_EQ(myMap.size(), origMap.size());
  EXPECT_EQ(myMapMerge.size(), origMapMerge.size());

  auto myIt = myMap.begin();
  auto origIt = origMap.begin();
  for (; myIt != myMap.end(); ++myIt, ++origIt) {
    EXPECT_TRUE((*myIt).first == (*origIt).first);
    EXPECT_TRUE((*myIt).second == (*origIt).second);
  }
  EXPECT_TRUE(myMapMerge.contains(4));
  EXPECT_FALSE(myMapMerge.contains(3));
}

TEST(map, ConstBegin) {
  const s21::map<int, int> myMap({{1, 2}, {3, 4}, {5, 6}});
  auto myIt = myMap.begin();
  EXPECT_EQ((*myIt).first, 1);
  EXPECT_EQ((*myIt).second, 2);
  ++myIt;
  ++myIt;
  EXPECT_EQ((*myIt).first, 5);
  EXPECT_EQ((*myIt).second, 6);
  --myIt;
  EXPECT_EQ((*myIt).first, 3);
  EXPECT_EQ((*myIt).second, 4);
}

TEST(map, OperatorCopy) {
  const s21::map<int, int> m1({{9, 10}, {7, 8}, {5, 6}, {3, 4}, {1, 2}});
  s21::map<int, int> m2;
  m2 = m1;
  auto myIt = m2.begin();
  EXPECT_EQ((*myIt).first, 1);
  EXPECT_EQ((*myIt).second, 2);
  ++myIt;
  ++myIt;
  EXPECT_EQ((*myIt).first, 5);
  EXPECT_EQ((*myIt).second, 6);
  --myIt;
  EXPECT_EQ((*myIt).first, 3);
  EXPECT_EQ((*myIt).second, 4);
  --myIt;
  EXPECT_EQ((*myIt).first, 1);
  EXPECT_EQ((*myIt).second, 2);
  auto myIt2 = m1.begin();
  EXPECT_EQ((*myIt2).first, 1);
  EXPECT_EQ((*myIt2).second, 2);
  ++myIt2;
  ++myIt2;
  EXPECT_EQ((*myIt2).first, 5);
  EXPECT_EQ((*myIt2).second, 6);
  --myIt2;
  EXPECT_EQ((*myIt2).first, 3);
  EXPECT_EQ((*myIt2).second, 4);
  --myIt2;
  EXPECT_EQ((*myIt2).first, 1);
  EXPECT_EQ((*myIt2).second, 2);
}

TEST(map, OperatorMove) {
  s21::map<int, int> m1({{9, 10}, {7, 8}, {5, 6}, {3, 4}, {1, 2}});
  s21::map<int, int> m2;
  m2 = std::move(m1);
  auto it1 = m2.begin();
  EXPECT_EQ((*it1).first, 1);
  EXPECT_EQ((*it1).second, 2);
  ++it1;
  ++it1;
  EXPECT_EQ((*it1).first, 5);
  EXPECT_EQ((*it1).second, 6);
  --it1;
  EXPECT_EQ((*it1).first, 3);
  EXPECT_EQ((*it1).second, 4);
  --it1;
  EXPECT_EQ((*it1).first, 1);
  EXPECT_EQ((*it1).second, 2);

  EXPECT_EQ(m1.size(), 0ul);
  EXPECT_EQ(m1.size(), 0ul);
}

TEST(map, Find) {
  s21::map<int, int> m1({{1, 2}, {3, 4}, {5, 6}});
  auto itEnd = m1.end();
  auto itAns = m1.begin();
  ++itAns;
  auto it1 = m1.find(3);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = m1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(map, ConstFind) {
  const s21::map<int, int> m1({{1, 2}, {3, 4}, {5, 6}});
  auto itEnd = m1.end();
  auto itAns = m1.begin();
  ++itAns;
  auto it1 = m1.find(3);
  EXPECT_FALSE(it1 == itEnd);
  EXPECT_TRUE(it1 == itAns);
  it1 = m1.find(6);
  EXPECT_TRUE(it1 == itEnd);
}

TEST(map, OperatorBracket) {
  s21::map<int, int> m1({{3, 4}, {5, 6}, {1, 2}});
  m1[8] = 80;
  EXPECT_EQ((*(m1.find(8))).second, 80);
}

TEST(map, MaxSize) {
  s21::map<int, int> m1({{1, 2}, {3, 4}, {5, 6}});
  s21::map<int, int> m2({{1, 2}, {3, 4}, {5, 6}});
  EXPECT_EQ(m1.max_size(), m2.max_size());
}

TEST(map, InsertMany) {
  s21::map<int, int> m1({{3, 30}, {5, 50}, {1, 10}});
  m1.insert_many(std::make_pair(2, 20), std::make_pair(4, 40));
  EXPECT_EQ(m1.contains(2), true);
  EXPECT_EQ(m1.contains(4), true);
}

// queueTest

TEST(QueueMemberFunctions, TestDefault) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(QueueMemberFunctions, TestInitializer) {
  s21::queue<int> s21_queue = {1, 2, 3, 4};
  EXPECT_EQ(s21_queue.front(), 1);
  EXPECT_EQ(s21_queue.back(), 4);
  EXPECT_EQ(s21_queue.size(), size_t(4));
  EXPECT_EQ(s21_queue.empty(), false);
}

TEST(QueueMemberFunctions, TestConstructorCopy) {
  s21::queue<char> s21_queue_1 = {'a', 'b', 'c', 'd'};
  s21::queue<char> s21_queue_2(s21_queue_1);

  EXPECT_EQ(s21_queue_1.size(), s21_queue_2.size());

  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_1.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_1.size(), s21_queue_2.size());
    s21_queue_1.pop(), s21_queue_2.pop();
  }
}

TEST(QueueMemberFunctions, TestConstructorMove) {
  s21::queue<char> s21_queue_1 = {'a', 'b', 'c', 'd'};
  s21::queue<char> s21_queue_2 = std::move(s21_queue_1);
  s21::queue<char> s21_queue_3 = {'a', 'b', 'c', 'd'};

  EXPECT_EQ(s21_queue_2.size(), s21_queue_3.size());
  EXPECT_EQ(s21_queue_1.size(), size_t(0));
  EXPECT_EQ(s21_queue_1.empty(), true);
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_3.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_3.size(), s21_queue_2.size());
    s21_queue_3.pop(), s21_queue_2.pop();
  }
}

TEST(QueueMemberFunctions, TestConstructorMove2) {
  s21::queue<int> s21_queue_1{1, 2, 3, 4};
  s21::queue<int> s21_queue_2(std::move(s21_queue_1));
  std::queue<int> s21_queue_3;
  s21_queue_3.push(1);
  s21_queue_3.push(2);
  s21_queue_3.push(3);
  s21_queue_3.push(4);
  std::queue<int> s21_queue_4(std::move(s21_queue_3));
  EXPECT_EQ(s21_queue_2.empty(), s21_queue_4.empty());
  EXPECT_EQ(s21_queue_2.size(), s21_queue_4.size());
  while (!s21_queue_2.empty()) {
    EXPECT_EQ(s21_queue_2.front(), s21_queue_4.front());
    s21_queue_2.pop();
    s21_queue_4.pop();
  }
}

TEST(Queue, InsertManyBack) {
  s21::queue<int> our_queue_int;
  our_queue_int.insert_many_back(1, 2, 3);
  EXPECT_EQ(our_queue_int.front(), 1);
  EXPECT_EQ(our_queue_int.back(), 3);
}

TEST(QueueElementAccess, TestFront) {
  s21::queue<int> s21_queue{11, 2, 4, 6, 8};
  std::initializer_list<int> il = {11, 1, 3, 5, 7};
  std::queue<int> std_queue{il};
  EXPECT_EQ(s21_queue.front(), std_queue.front());
}

TEST(QueueElementAccess, TestBack) {
  s21::queue<int> s21_queue{1, 2, 3, 4, 10};
  std::initializer_list<int> il = {15, 14, 13, 12, 11, 10};
  std::queue<int> std_queue{il};
  EXPECT_EQ(s21_queue.back(), std_queue.back());
}

TEST(QueueCapacity, TestEmpty) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
  s21_queue.push(123);
  std_queue.push(123);
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(QueueCapacity, TestSize) {
  s21::queue<int> s21_queue{1, 2, 3, 4, 5, 6, 7, 8};
  std::initializer_list<int> il = {1, 2, 3, 4, 5, 6, 7, 8};
  std::queue<int> std_queue{il};
  EXPECT_EQ(s21_queue.size(), std_queue.size());
}

TEST(QueueModifier, TestPush) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  s21_queue.push(5);
  s21_queue.push(0);
  std_queue.push(5);
  std_queue.push(0);
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(QueueModifiers, TestPop) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  s21_queue.push(5);
  s21_queue.push(0);
  std_queue.push(5);
  std_queue.push(0);
  s21_queue.pop();
  s21_queue.pop();
  std_queue.pop();
  std_queue.pop();
  s21_queue.push(15);
  s21_queue.push(10);
  std_queue.push(15);
  std_queue.push(10);
  s21_queue.pop();
  std_queue.pop();
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(QueueModifiers, TestSwap) {
  s21::queue<std::string> s21_queue_1 = {"a", "b", "c", "d"};
  s21::queue<std::string> s21_queue_2 = {"aa", "bb", "cc"};
  s21::queue<std::string> s21_queue_3 = {"a", "b", "c", "d"};
  s21::queue<std::string> s21_queue_4 = {"aa", "bb", "cc"};
  s21_queue_1.swap(s21_queue_2);

  EXPECT_EQ(s21_queue_1.size(), s21_queue_4.size());
  EXPECT_EQ(s21_queue_2.size(), s21_queue_3.size());
  for (auto i = 0; i < 4; i++) {
    EXPECT_EQ(s21_queue_3.front(), s21_queue_2.front());
    EXPECT_EQ(s21_queue_3.size(), s21_queue_2.size());
    s21_queue_3.pop(), s21_queue_2.pop();
  }
  for (auto i = 0; i < 3; i++) {
    EXPECT_EQ(s21_queue_1.front(), s21_queue_4.front());
    EXPECT_EQ(s21_queue_1.size(), s21_queue_4.size());
    s21_queue_1.pop(), s21_queue_4.pop();
  }
}

TEST(QueueModifiers, TestSwap2) {
  s21::queue<int> s21_queue_1{1, 2, 3};
  s21::queue<int> s21_queue_2{4, 5, 6};
  s21::queue<int> s21_queue_1_copy{s21_queue_1};
  s21::queue<int> s21_queue_2_copy{s21_queue_2};

  s21_queue_1.swap(s21_queue_2);

  EXPECT_EQ(s21_queue_1.size(), s21_queue_2_copy.size());
  EXPECT_EQ(s21_queue_2.size(), s21_queue_1_copy.size());
  EXPECT_EQ(s21_queue_1.front(), 4);
  EXPECT_EQ(s21_queue_1.back(), 6);
  EXPECT_EQ(s21_queue_2.front(), 1);
  EXPECT_EQ(s21_queue_2.back(), 3);

  s21_queue_2.swap(s21_queue_1);

  EXPECT_EQ(s21_queue_2.size(), s21_queue_1_copy.size());
  EXPECT_EQ(s21_queue_1.size(), s21_queue_2_copy.size());
  EXPECT_EQ(s21_queue_2.front(), 4);
  EXPECT_EQ(s21_queue_2.back(), 6);
  EXPECT_EQ(s21_queue_1.front(), 1);
  EXPECT_EQ(s21_queue_1.back(), 3);
}
// vectorTest

TEST(vectorMemberFunctions, TestDefault) {
  s21::vector<int> s21_vector;
  std::vector<int> std_vector;
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(vectorMemberFunctions, TestConstructorSize) {
  s21::vector<double> s21_vector(5);
  std::vector<double> std_vector(5);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(vectorMemberFunctions, TestInitializer) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};
  EXPECT_EQ(s21_vector.front(), std_vector.front());
  EXPECT_EQ(s21_vector.back(), std_vector.back());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(vectorMemberFunctions, TestCopy) {
  s21::vector<char> s21_vector_1 = {'a', 'b', 'c', 'd'};
  std::vector<char> std_vector_1 = {'a', 'b', 'c', 'd'};
  s21::vector<char> s21_vector_2 = s21_vector_1;
  std::vector<char> std_vector_2 = std_vector_1;

  EXPECT_EQ(s21_vector_1.size(), s21_vector_2.size());
  EXPECT_EQ(std_vector_1.size(), std_vector_2.size());
  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();
  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(vectorMemberFunctions, TtestMove) {
  s21::vector<char> s21_vector_1 = {'a', 'b', 'c', 'd'};
  std::vector<char> std_vector_1 = {'a', 'b', 'c', 'd'};
  s21::vector<char> s21_vector_2 = std::move(s21_vector_1);
  std::vector<char> std_vector_2 = std::move(std_vector_1);

  EXPECT_EQ(s21_vector_2.size(), std_vector_2.size());
  EXPECT_EQ(s21_vector_1.size(), std_vector_1.size());
  EXPECT_EQ(s21_vector_1.empty(), std_vector_1.empty());
  auto it1 = s21_vector_2.begin();
  auto it2 = std_vector_2.begin();
  while (it1 != s21_vector_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(vectorElementAccess, TestAt) {
  s21::vector<int> s21_vector = {1, 2, 3, 4, 5};
  std::vector<int> std_vector = {1, 2, 3, 4, 5};

  EXPECT_EQ(s21_vector.at(0), std_vector.at(0));
  EXPECT_EQ(s21_vector.at(1), std_vector.at(1));
  EXPECT_EQ(s21_vector.at(2), std_vector.at(2));
  EXPECT_EQ(s21_vector.at(3), std_vector.at(3));
  EXPECT_EQ(s21_vector.at(4), std_vector.at(4));
}

TEST(vectorElementAccess, TestBrackets) {
  s21::vector<int> s21_vector = {1, 2, 3};
  std::vector<int> std_vector = {1, 2, 3};
  EXPECT_EQ(s21_vector[0], std_vector[0]);
  EXPECT_EQ(s21_vector[1], std_vector[1]);
  EXPECT_EQ(s21_vector[2], std_vector[2]);
}

TEST(vectorElementAccess, TestFront) {
  s21::vector<int> s21_vector = {1, 2, 3};
  std::vector<int> std_vector = {1, 2, 3};
  EXPECT_EQ(s21_vector.front(), std_vector.front());
}

TEST(vectorElementAccess, TestBack) {
  s21::vector<int> s21_vector = {1, 2, 3};
  std::vector<int> std_vector = {1, 2, 3};
  EXPECT_EQ(s21_vector.back(), std_vector.back());
}

TEST(vectorElementAccess, TestData) {
  s21::vector<int> s21_vector = {1, 2, 3};
  std::vector<int> std_vector = {1, 2, 3};

  EXPECT_EQ(*s21_vector.data(), *std_vector.data());
}

TEST(vectorIterators, TestBegin) {
  s21::vector<int> s21_vector = {1, 2, 3};
  std::vector<int> std_vector = {1, 2, 3};

  EXPECT_EQ(*s21_vector.begin(), *std_vector.begin());
}

TEST(vectorCapacity, TestEmpty) {
  s21::vector<int> s21_vector = {1, 2, 3};
  std::vector<int> std_vector = {1, 2, 3};

  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(vectorCapacity, TestSize) {
  s21::vector<int> s21_vector = {1, 2, 3};
  std::vector<int> std_vector = {1, 2, 3};

  EXPECT_EQ(s21_vector.size(), std_vector.size());
}

TEST(vectorCapacity, TestReserve) {
  s21::vector<int> s21_vector;
  std::vector<int> std_vector;
  s21_vector.reserve(2);
  std_vector.reserve(2);

  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
}

TEST(vectorCapacity, TestCapacity) {
  s21::vector<int> s21_vector = {1, 2, 3};
  std::vector<int> std_vector = {1, 2, 3};

  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
}

TEST(vectorCapacity, TestShrinkToFit) {
  s21::vector<int> s21_vector = {1, 2, 3};
  std::vector<int> std_vector = {1, 2, 3};
  s21_vector.reserve(10);
  std_vector.reserve(10);
  s21_vector.shrink_to_fit();
  std_vector.shrink_to_fit();

  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
}

TEST(vectorModifiers, TestClear) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};
  s21_v.clear();
  std_v.clear();

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(vectorModifier, TestInsert) {
  s21::vector<int> s21_vector_1 = {'a', 'c', 'd'};
  s21::vector<int> s21_vector_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_vector_1.begin();
  ++it;
  s21_vector_1.insert(it, 'b');
  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();
  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_vector_1.size(), s21_vector_2.size());
  s21_vector_1.insert(s21_vector_1.end(), '5');
  EXPECT_EQ(s21_vector_1.back(), '5');
}

TEST(vectorModifier, TestErase) {
  s21::vector<int> s21_vector_1 = {'a', 'c', 'd'};
  s21::vector<int> s21_vector_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_vector_2.begin();
  ++it;
  s21_vector_2.erase(it);
  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();
  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_vector_1.size(), s21_vector_2.size());
}

TEST(vectorModifier, TestPush) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};
  s21_vector.push_back(5);
  std_vector.push_back(5);
  EXPECT_EQ(s21_vector.front(), std_vector.front());
  EXPECT_EQ(s21_vector.back(), std_vector.back());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  auto it1 = s21_vector.begin();
  auto it2 = std_vector.begin();
  while (it1 != s21_vector.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(vectorModifier, TestPop) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};
  s21_vector.pop_back();
  std_vector.pop_back();
  EXPECT_EQ(s21_vector.front(), std_vector.front());
  EXPECT_EQ(s21_vector.back(), std_vector.back());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  auto it1 = s21_vector.begin();
  auto it2 = std_vector.begin();
  while (it1 != s21_vector.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(vectorModifier, TestSwap) {
  s21::vector<char> s21_vector_1 = {'a', 'b', 'o', 'b', 'a'};
  s21::vector<char> s21_vector_2 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21::vector<char> s21_vector_3 = {'a', 'b', 'o', 'b', 'a'};
  s21::vector<char> s21_vector_4 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21_vector_1.swap(s21_vector_2);
  auto it1 = s21_vector_1.begin();
  auto it2 = s21_vector_2.begin();
  auto it3 = s21_vector_3.begin();
  auto it4 = s21_vector_4.begin();
  while (it1 != s21_vector_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_vector_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(s21_vector_1.size(), s21_vector_4.size());
  EXPECT_EQ(s21_vector_2.size(), s21_vector_3.size());
}

TEST(vectorTest, InsertMany) {
  s21::vector<int> vec({1, 2, 3, 7, 8});
  s21::vector<int>::const_iterator pos = vec.begin();
  ++pos;
  pos++;
  ++pos;

  vec.insert_many(pos, 4, 5, 6);
  EXPECT_EQ(vec.size(), 8ul);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
  EXPECT_EQ(vec[6], 7);
  EXPECT_EQ(vec[7], 8);
}

TEST(vectorTest, InsertManyBack) {
  s21::vector<int> vec({1, 2, 3});

  vec.insert_many_back(4, 5, 6);
  EXPECT_EQ(vec.size(), 6ul);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
}

TEST(vectorTest, AtExcept1) {
  s21::vector<int> vec;
  EXPECT_THROW(vec.at(4), std::out_of_range);
}

TEST(vectorTest, AtExcept2) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_THROW(vec.at(5), std::out_of_range);
}

// listTest
TEST(list, ConstructorDefault) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(list, ConstructorInitializerlist) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  EXPECT_EQ(std_list.front(), s21_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(list, ConstructorParameterized) {
  s21::list<double> s21_list(5);
  std::list<double> std_list(5);
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}
TEST(list, ConstructorCopy) {
  s21::list<char> s21_list_1 = {'a', 'b', 'c', 'd'};
  std::list<char> std_list_1 = {'a', 'b', 'c', 'd'};
  s21::list<char> s21_list_2 = s21_list_1;
  std::list<char> std_list_2 = std_list_1;

  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
  EXPECT_EQ(std_list_1.size(), std_list_2.size());
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}
TEST(list, ConstructorMove) {
  s21::list<char> s21_list_1 = {'a', 'b', 'c', 'd'};
  std::list<char> std_list_1 = {'a', 'b', 'c', 'd'};
  s21::list<char> s21_list_2 = std::move(s21_list_1);
  std::list<char> std_list_2 = std::move(std_list_1);

  EXPECT_EQ(s21_list_2.size(), std_list_2.size());
  EXPECT_EQ(s21_list_1.size(), std_list_1.size());
  EXPECT_EQ(s21_list_1.empty(), std_list_1.empty());
  auto it1 = s21_list_2.begin();
  auto it2 = std_list_2.begin();
  while (it1 != s21_list_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(list, ModifierInsert) {
  s21::list<int> s21_list_1 = {'a', 'c', 'd'};
  s21::list<int> s21_list_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_list_1.begin();
  ++it;
  s21_list_1.insert(it, 'b');
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(list, ModifierErase) {
  s21::list<int> s21_list_1 = {'a', 'c', 'd'};
  s21::list<int> s21_list_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_list_2.begin();
  ++it;
  s21_list_2.erase(it);
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(list, ModifierPush) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  s21_list.push_back(5);
  s21_list.push_front(0);
  std_list.push_back(5);
  std_list.push_front(0);
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(list, ModifierPop) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  s21_list.pop_back();
  s21_list.pop_front();
  std_list.pop_back();
  std_list.pop_front();
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(list, ModifierSwap) {
  s21::list<char> s21_list_1 = {'a', 'b', 'o', 'b', 'a'};
  s21::list<char> s21_list_2 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21::list<char> s21_list_3 = {'a', 'b', 'o', 'b', 'a'};
  s21::list<char> s21_list_4 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21_list_1.swap(s21_list_2);
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  auto it3 = s21_list_3.begin();
  auto it4 = s21_list_4.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_list_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_4.size());
  EXPECT_EQ(s21_list_2.size(), s21_list_3.size());
}

TEST(list, ModifierMerge) {
  s21::list<int> s21_list_1 = {1, 3, 7};
  s21::list<int> s21_list_2 = {-1, 0, 5, 8};
  std::list<int> std_list_1 = {1, 3, 7};
  std::list<int> std_list_2 = {-1, 0, 5, 8};
  s21_list_1.merge(s21_list_2);
  std_list_1.merge(std_list_2);
  auto it1 = s21_list_1.begin();
  auto it2 = std_list_1.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), std_list_1.size());
}

TEST(list, ModifierReverse) {
  s21::list<int> s21_list_1 = {1, 2, 3, 4};
  s21::list<int> s21_list_2 = {4, 3, 2, 1};
  s21_list_1.reverse();
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(list, ModifierUnique) {
  s21::list<int> s21_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  std::list<int> std_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  s21_list.unique();
  std_list.unique();
  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(list, ModifierSort) {
  s21::list<int> s21_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  std::list<int> std_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  s21_list.sort();
  std_list.sort();
  auto it1 = s21_list.begin();
  auto it2 = std_list.begin();
  while (it1 != s21_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(list, Splice) {
  s21::list<int> our_list_first({1});
  s21::list<int> our_list_second({2, 3, 4, 5});
  std::list<int> std_list_first({1});
  std::list<int> std_list_second({2, 3, 4, 5});
  s21::list<int>::const_iterator our_it = our_list_first.begin();
  std::list<int>::iterator std_it = std_list_first.begin();
  our_list_first.splice(our_it, our_list_second);
  std_list_first.splice(std_it, std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
}

TEST(list, ModifierSplice) {
  s21::list<int> s21_list1{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  std::list<int> std_list1{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  s21::list<int> s21_list2{10, 20, 30, 40, 50};
  std::list<int> std_list2{10, 20, 30, 40, 50};
  s21::list<int>::const_iterator s21_it = s21_list1.begin();
  std::list<int>::const_iterator std_it = std_list1.begin();
  s21_list1.splice(s21_it, s21_list2);
  std_list1.splice(std_it, std_list2);
  s21_it = s21_list1.begin();
  std_it = std_list1.begin();
  while (s21_it != s21_list1.end()) {
    EXPECT_EQ(*s21_it, *std_it);
    ++s21_it, ++std_it;
  }
}

TEST(list, Insert_Many) {
  s21::list<int> our_list({1, 2, 3, 4, 5});
  s21::list<int>::const_iterator our_it = our_list.begin();
  ++our_it;
  our_list.insert_many(our_it, 7, 8, 9);
  s21::list<int>::iterator our_it2 = our_list.begin();
  EXPECT_EQ(*our_it2, 1);
  ++our_it2;
  EXPECT_EQ(*our_it2, 7);
  ++our_it2;
  EXPECT_EQ(*our_it2, 8);
  ++our_it2;
  EXPECT_EQ(*our_it2, 9);
  ++our_it2;
  EXPECT_EQ(*our_it2, 2);
}

TEST(list, Insert_Many_Back) {
  s21::list<int> our_list({1, 2, 3, 4, 5});
  s21::list<int>::const_iterator our_it = our_list.begin();
  our_list.insert_many_back(6, 7, 8);
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
  ++our_it;
  EXPECT_EQ(*our_it, 3);
  ++our_it;
  EXPECT_EQ(*our_it, 4);
  ++our_it;
  EXPECT_EQ(*our_it, 5);
  ++our_it;
  EXPECT_EQ(*our_it, 6);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
}

TEST(list, Insert_Many_Front) {
  s21::list<int> our_list({1, 2, 3, 4, 5});
  our_list.insert_many_front(6, 7, 8);
  s21::list<int>::const_iterator our_it = our_list.begin();
  EXPECT_EQ(*our_it, 6);
  ++our_it;
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
  ++our_it;
  EXPECT_EQ(*our_it, 3);
  ++our_it;
  EXPECT_EQ(*our_it, 4);
  ++our_it;
  EXPECT_EQ(*our_it, 5);
}

// arrayTest

TEST(arrayTest, DefaultConstructor) {
  s21::array<int, 5> Myarr{};
  std::array<int, 5> NotMyarr{};
  EXPECT_EQ(Myarr.size(), NotMyarr.size());
  for (size_t i = 0; i < Myarr.size(); ++i) {
    EXPECT_EQ(Myarr[i], NotMyarr[i]);
  }
}

TEST(arrayTest, InitListConstructor) {
  s21::array<int, 5> arr({1, 2, 3, 4, 5});
  EXPECT_EQ(arr.size(), 5ul);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], static_cast<int>(i) + 1);
  }
}

TEST(arrayTest, CopyConstructor) {
  s21::array<int, 5> arr({1, 2, 3, 4, 5});
  s21::array<int, 5> arrCopy(arr);
  EXPECT_EQ(arrCopy.size(), 5ul);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arrCopy[i], arr[i]);
  }
}

TEST(arrayTest, MoveConstructor) {
  s21::array<int, 5> arr({1, 2, 3, 4, 5});
  s21::array<int, 5> arrMoved(std::move(arr));
  EXPECT_EQ(arrMoved.size(), 5ul);
  for (size_t i = 0; i < arrMoved.size(); ++i) {
    EXPECT_EQ(arrMoved[i], static_cast<int>(i) + 1);
  }
}

TEST(arrayTest, Begin) {
  s21::array<int, 5> arr({1, 2, 3, 4, 5});
  auto it = arr.begin();
  EXPECT_EQ(*it, 1);
  *it = 10;
  EXPECT_EQ(arr[0], 10);
}

TEST(arrayTest, End) {
  s21::array<int, 5> arr({1, 2, 3, 4, 5});
  auto it = arr.end();
  auto beginIt = arr.begin();
  EXPECT_EQ(it, beginIt + 5);
}

TEST(arrayTest, At_ValidIndex) {
  s21::array<int, 5> arr({1, 2, 3, 4, 5});
  int value = arr.at(2);
  EXPECT_EQ(value, 3);
}

TEST(arrayTest, At_OutOfBounds) {
  s21::array<int, 5> arr({1, 2, 3, 4, 5});
  EXPECT_THROW(arr.at(10), std::out_of_range);
}

TEST(arrayTest, Front) {
  s21::array<int, 5> arr({1, 2, 3, 4, 5});
  int value = arr.front();
  EXPECT_EQ(value, 1);
}

TEST(arrayTest, Back) {
  s21::array<int, 5> arr({1, 2, 3, 4, 5});
  int value = arr.back();
  EXPECT_EQ(value, 5);
}

TEST(arrayTest, Empty_NonEmptyarray) {
  s21::array<int, 5> arr({1, 2, 3, 4, 5});
  EXPECT_FALSE(arr.empty());
}

TEST(arrayTest, Empty_Emptyarray) {
  s21::array<int, 0> arr;
  EXPECT_TRUE(arr.empty());
}

TEST(arrayTest, Size_NonEmptyarray) {
  s21::array<int, 5> arr({1, 2, 3, 4, 5});
  EXPECT_EQ(arr.size(), 5ul);
}

TEST(arrayTest, Size_Emptyarray) {
  s21::array<int, 0> arr = {};
  EXPECT_EQ(arr.size(), 0ul);
}

TEST(arrayTest, MaxSize) {
  s21::array<int, 5> arr = {};
  EXPECT_EQ(arr.max_size(), 5ul);
}

TEST(arrayTest, Swap_1) {
  s21::array<int, 5> arr1({1, 2, 3, 4, 5});
  s21::array<int, 5> arr2({6, 7, 8, 9, 10});
  arr1.swap(arr2);
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], static_cast<int>(i) + 6);
  }
  for (size_t i = 0; i < arr2.size(); ++i) {
    EXPECT_EQ(arr2[i], static_cast<int>(i) + 1);
  }
}

TEST(arrayTest, Swap_2) {
  s21::array<int, 5> arr1({1, 2, 3, 4, 5});
  EXPECT_NO_THROW(arr1.swap(arr1));
}

TEST(arrayTest, Fill) {
  s21::array<int, 5> arr;
  arr.fill(10);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 10);
  }
}

TEST(arrayTest, MoveAssignmentOperator) {
  s21::array<int, 5> arr1({1, 2, 3, 4, 5});
  s21::array<int, 5> arr2({6, 7, 8, 9, 10});
  arr1 = std::move(arr2);
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], static_cast<int>(i) + 6);
  }
}

TEST(arrayTest, OperatorBracket) {
  s21::array<int, 5> arr({1, 2, 3, 4, 5});
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], static_cast<int>(i) + 1);
  }
  arr[2] = 10;
  EXPECT_EQ(arr[2], 10);
}

TEST(arrayTest, Data) {
  s21::array<int, 5> arr({1, 2, 3, 4, 5});
  auto iter = arr.data();
  for (auto i = 0, c = 0; i < 5; ++i) EXPECT_EQ(*(iter + i), ++c);
}

TEST(arrayTest, ConstData) {
  const s21::array<int, 5> arr({1, 2, 3, 4, 5});
  auto iter = arr.data();
  for (auto i = 0, c = 0; i < 5; ++i) EXPECT_EQ(*(iter + i), ++c);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}