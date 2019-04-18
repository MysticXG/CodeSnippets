#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
/*
 * This class generates a data set containing a sequence
 * of numbers, with exactly one number missing in the sequence.
 * The missing number is recorded in variable 'expected'
 * after generation of dataset.
 */

using namespace std;

class TestDataSet {
public:
    /* generates sequence [M,N] with random number missing */
    TestDataSet(int M, int N);

    /* generates sequence [M,N] with number x missing */
    TestDataSet(int M, int N, int x);

    /* get dataset if generated */
    vector<int> get_dataset() {
        return (data_set);
    }

    /* get expected value */
    int get_expected() {
        return (expected);
    }

private:
    vector<int> data_set;
    bool valid = false; /* dataset valid after generated */
    int expected; /* expected result from dataset */

    void generate(int M, int N, int x);
};
