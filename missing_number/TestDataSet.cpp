#include "TestDataSet.h"

/* generates sequence [M,N] with random number missing */
TestDataSet::TestDataSet(int M, int N) {
    int size = N-M-1;

    /* RNG seed */
    srand((unsigned)time(0));
    /* Get random number between (M,N) */
    int x = (rand()%size)+M+1;

    generate(M, N, x);
    expected = x;
}

/* generates sequence [M,N] with number x missing */
TestDataSet::TestDataSet(int M, int N, int x) {
    generate(M, N, x);
    expected = x;
}

void TestDataSet::generate(int M, int N, int x) {
    /* generate only once */
    if (valid) {
        return;
    }

    for (int i = M; i <= N; i++) {
        if (i != x) {
            data_set.push_back(i);
        }
    }

    valid = true;
}
