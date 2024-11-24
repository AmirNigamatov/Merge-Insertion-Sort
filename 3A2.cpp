#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

void insertionSort(std::vector<int> &a) {
    for (int i = 1; i < a.size(); i++) {
        for (int j = i - 1; j > -1; j--) {
            if (a[j + 1] < a[j]) {
                std::swap(a[j], a[j + 1]);
            }
        }
    }
}

void insertionMergeSort(std::vector<int> &a) {
    if (a.size() > 15) {
        std::vector<int> b;
        std::vector<int> c;
        for (int i = 0; i < a.size() / 2; i++) {
            b.push_back(a[i]);
        }
        for (int i = a.size() / 2; i < a.size(); i++) {
            c.push_back(a[i]);
        }
        insertionMergeSort(b);
        insertionMergeSort(c);
        int ind1 = 0;
        int ind2 = 0;
        int ind = 0;
        while (ind < a.size()) {
            if (ind1 == b.size()) {
                a[ind++] = c[ind2++];
            } else if (ind2 == c.size()) {
                a[ind++] = b[ind1++];
            } else {
                if (b[ind1] <= c[ind2]) {
                    a[ind++] = b[ind1++];
                } else {
                    a[ind++] = c[ind2++];
                }
            }
        }
    } else {
        insertionSort(a);
    }
}

void mergeSort(std::vector<int> &a) {
    if (a.size() > 1) {
        std::vector<int> b;
        std::vector<int> c;
        for (int i = 0; i < a.size() / 2; i++) {
            b.push_back(a[i]);
        }
        for (int i = a.size() / 2; i < a.size(); i++) {
            c.push_back(a[i]);
        }
        mergeSort(b);
        mergeSort(c);
        int ind1 = 0;
        int ind2 = 0;
        int ind = 0;
        while (ind < a.size()) {
            if (ind1 == b.size()) {
                a[ind++] = c[ind2++];
            } else if (ind2 == c.size()) {
                a[ind++] = b[ind1++];
            } else {
                if (b[ind1] <= c[ind2]) {
                    a[ind++] = b[ind1++];
                } else {
                    a[ind++] = c[ind2++];
                }
            }
        }
    }
}

class ArrayGenerator {
public:
    std::vector<int> getRandomArray() {
        std::vector<int> a(10000);
        for (int i = 0; i < 10000; i++) {
            a[i] = rand() % 6001;
        }
        return a;
    }
    std::vector<int> getSortedArray() {
        std::vector<int> a(10000);
        a[0] = 0;
        for (int i = 1; i < 10000; i++) {
            if (a[i - 1] < 6000) {
                a[i] = a[i - 1] + rand() % 2;
            } else {
                a[i] = a[i - 1];
            }
        }
        return a;
    }
    std::vector<int> getAlmostSortedArray() {
        std::vector<int> a(10000);
        a[0] = 0;
        for (int i = 1; i < 10000; i++) {
            if (a[i - 1] < 6000) {
                a[i] = a[i - 1] + rand() % 2;
            } else {
                a[i] = a[i - 1];
            }
        }
        for (int i = 0; i < 5; i++) {
            std::swap(a[rand() % 10000], a[rand() % 10000]);
        }
        return a;
    }
};

class SortTester {
public:
    std::vector<long long> TesterMerge(std::vector<int> &a) {
        std::vector<int> b;
        std::vector<long long> c;
        for (int i = 500; i < 10000; i += 100) {
            b = {};
            for (int j = 0; j < i; j++) {
                b.push_back(a[j]);
            }
            auto start = std::chrono::high_resolution_clock::now();
            mergeSort(b);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            double msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            c.push_back(msec);
        }
        return c;
    }
    std::vector<long long> TesterInsertionMerge(std::vector<int> &a) {
        std::vector<int> b;
        std::vector<long long> c;
        for (int i = 500; i < 10000; i += 100) {
            b = {};
            for (int j = 0; j < i; j++) {
                b.push_back(a[j]);
            }
            auto start = std::chrono::high_resolution_clock::now();
            insertionMergeSort(b);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            double msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            c.push_back(msec);
        }
        return c;
    }
};

void print(std::vector<long long> a) {
    for (int i = 0; i < a.size(); i++){
        std::cout << a[i] << ", ";
    }
    std::cout << "\n";
}

int main() {
    ArrayGenerator generator;
    SortTester tester;
    std::vector<int> a = generator.getRandomArray();
    std::vector<long long> b = tester.TesterMerge(a);
    std::vector<long long> c = tester.TesterInsertionMerge(a);
    print(b);
    print(c);
    a = generator.getSortedArray();
    b = tester.TesterMerge(a);
    c = tester.TesterInsertionMerge(a);
    print(b);
    print(c);
    a = generator.getAlmostSortedArray();
    b = tester.TesterMerge(a);
    c = tester.TesterInsertionMerge(a);
    print(b);
    print(c);
}
