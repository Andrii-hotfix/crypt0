/* Лабораторная работа №4
 * Дегтярёв А
 * Зади Ю
 * ФБ-52
 */

#include "registry.h"
#include <thread>
#include <mutex>

using namespace std;

vector<int64_t> findKeysL1(int64_t fillings, int NL, int CL, vector<int> zSeq)
{    
    vector<int64_t> result;
    L1 reg1;
    #pragma omp parallel for private(reg1)
    for (int64_t i = 1; i < fillings; i++) {
        reg1.state = i;
        vector<int> sequence;
        for (int j = 0; j < NL; j++) {            
            sequence.push_back(reg1.shiftL1());
        }
        int sum = 0;
        for (int j = 0; j < NL; j++) {            
            if (sequence[j] != zSeq[j]) {
                sum++;
            }
        }
        if (sum < CL) {
            #pragma omp critical (Res1)
            { result.push_back(i); }
        }
    }
    return result;
}

vector<int64_t> findKeysL2(int64_t fillings, int NL, int CL, vector<int> zSeq)
{    
    vector<int64_t> result;
    L2 reg2;
    #pragma omp parallel for private(reg2)
    for (int64_t i = 1; i < fillings; i++) {
        reg2.state = i;
        vector<int> sequence;
        for (int j = 0; j < NL; j++) {            
            sequence.push_back(reg2.shiftL2());
        }
        int sum = 0;
        for (int j = 0; j < NL; j++) {            
            if (sequence[j] != zSeq[j]) {
                sum++;
            }
        }
        if (sum < CL) {
            #pragma omp critical (Res2)
            { result.push_back(i); }
        }
    }
    return result;
}

bool filter(vector<int64_t> comb, vector<int> zSeq)
{
    L1 reg1;
    reg1.state = comb[0];
    L2 reg2;
    reg2.state = comb[1];
    for (auto z: zSeq) {
        int x = reg1.shiftL1();
        int y = reg2.shiftL2();
        if (x == 0 && y == 0 && z == 1) {
            return false;
        } else if (x == 1 && y == 1 && z == 0) {
            return false;
        }
    }
    return true;
}

bool check(int x, int y, int s, int z)
{
    if (s == 1) {
        if (z == x) {
            return true;
        }
    } else if (s == 0) {
        if (z == y) {
            return true;
        }
    }
    return false;
}