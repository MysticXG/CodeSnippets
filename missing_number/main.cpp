#include <iostream>
#include <vector>
#include <chrono> /* for measuring function execution time */

#include "TestDataSet.h"

using namespace std;
using namespace std::chrono;

/*
 * XOR Search
 *
 * Finds missing number in a sequence by XOR-ing all values
 * in sequence without missing number, then XOR-ing that with
 * the XOR total of the provided list.  The result would be
 * the missing number.
 *
 * This works due to the characteristic of XOR such that
 * 
 * (a ^ a) == 0
 *
 * So, (a ^ b ^ c) ^ (a ^ c) == b
 */
int xor_search(vector<int>& nums) {
    /* Invalid List */
    if (nums.empty()) {
        return (-1);
    }
    
    int m = nums.front();
    int n = nums.back();
    int expected = 0;
    int actual = 0;

    /* Calculate expected XOR total of sequence [m,n] */
    for (int i = m; i <= n; i++) {
        expected ^= i;
    }

    /* Calculate actual XOR total of provided sequence */
    for (int num : nums) {
        actual ^= num;
    }

    return (expected ^ actual);
}

/*
 * Iterative Search
 *
 * Finds missing number in a sequence by incrementally
 * checking each number in sequence from beginning.
 */
int iter_search(vector<int>& nums) {
    /* Invalid List */
    if (nums.empty()) {
        return (-1);
    }
    int current = nums[0];
    int expected = current + 1;

    /*
     * Iterate through list of numbers, and compare
     * to the calculated expected number.  If it doesn't
     * match, then the expected number is our missing
     * number.
     */
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] != expected) {
            /* Missing number found */
            return (expected);
        } else {
            /* Calculate next expected number */
            current = nums[i];
            expected = current + 1;
        }
    }

    /* Missing number not found */
    return (-1);
}

/* Recursive helper function for Binary Search */
int bs_helper(vector<int>& nums, int first, int last) {
    int size = (last - first) + 1;
    int result = -1;

    /*
     * If number is missing, then the difference between
     * the last number and first number in nums, plus one,
     * would be different than the actual size of list.
     */
    if (size == ((nums[last] - nums[first])+1)) {
        /* no missing number in this list, return -1 */
        return (-1);
    }

    /* divide list in two */
    int mid = first + (last - first)/2;

    /* check if missing number is in between two lists */
    if (nums[mid] + 1 != nums[mid+1]) {
        /* missing number found */
        result = nums[mid]+1;
    }

    /* check left list if missing number not found */
    if (result < 0) {
        result = bs_helper(nums, first, mid);
    }

    /* check right list if missing number not found */
    if (result < 0) {
        result = bs_helper(nums, mid+1, last);
    }

    return (result);
}

/*
 * Binary Search
 *
 * Uses binary search algorithm to find missing number in
 * a sequence.
 *
 * Checks whether there is missing number in each half of
 * divided sequence by comparing actual size of sequence to
 * the expected size.
 *
 * e.g.
 *
 * Actual sequence: 1 2 3 5
 * Actual sequence size: 4
 * Expected sequence: 1 2 3 4 5
 * Expected sequence size: 5
 *
 * Expected sequence size is calculated using:
 * (last number - first number) + 1
 *
 * e.g. (5 - 1) + 1 = 5
 *
 */
int binary_search(vector<int>& nums) {
    /* Invalid List */
    if (nums.empty()) {
        return (-1);
    }

    return (bs_helper(nums, 0, nums.size()-1));
}

int main() {
    vector<TestDataSet> tests;
    high_resolution_clock::time_point start_time;
    high_resolution_clock::time_point end_time;

    cout << "Generating Test Data..." << endl;

    tests.push_back(TestDataSet(1,10));
    tests.push_back(TestDataSet(1,100));
    tests.push_back(TestDataSet(1,1000));
    tests.push_back(TestDataSet(1,10000));
    tests.push_back(TestDataSet(1,100000));
    tests.push_back(TestDataSet(1,1000000));
    tests.push_back(TestDataSet(1,10000000));
    tests.push_back(TestDataSet(1,100000000));

    for (int i = 0; i < tests.size(); i++) {
        vector<int> test = tests[i].get_dataset();
        int expected = tests[i].get_expected();
        int actual = -1;

        cout << "###################################" << endl;
        cout << "# Test #" << i+1 << endl;
        cout << "###################################" << endl;
        cout << "Expected:                 " << expected << endl;
        cout << "==========================" << endl;

        /* XOR Search */
        start_time = high_resolution_clock::now();
        actual = xor_search(test);
        end_time = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end_time - start_time).count();
        cout << "XOR Missing Number:       " << ((actual == expected) ? "PASS" : "FAIL") << endl;
        cout << "Execution Time:           " << duration << " ms" << endl;
        cout << "==========================" << endl;

        /* Iterative Search */
        start_time = high_resolution_clock::now();
        actual = iter_search(test);
        end_time = high_resolution_clock::now();
        duration = duration_cast<microseconds>(end_time - start_time).count();
        cout << "Iterative Missing Number: " << ((actual == expected) ? "PASS" : "FAIL") << endl;
        cout << "Execution Time:           " << duration << " ms" << endl;
        cout << "==========================" << endl;

        /* Binary Search */
        start_time = high_resolution_clock::now();
        actual = binary_search(test);
        end_time = high_resolution_clock::now();
        duration = duration_cast<microseconds>(end_time - start_time).count();
        cout << "BSearch Missing Number:   " << ((actual == expected) ? "PASS" : "FAIL") << endl;
        cout << "Execution Time:           " << duration << " ms" << endl << endl;
    }

    return (0);
}
