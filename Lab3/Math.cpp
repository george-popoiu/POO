#include "Math.h"
#include <string.h>
#include <algorithm>

using namespace std;

struct BigNumber {
    int cifre[100] = {};
    int nrCifre = 0;
};

char* Math::Add(const char* s1, const char* s2) {
    BigNumber a;
    a.nrCifre = strlen(s1);
    for (int i = 0; i < a.nrCifre; ++i) {
        a.cifre[i] = s1[a.nrCifre - i - 1] - '0';
    }
    BigNumber b;
    b.nrCifre = strlen(s2);
    for (int i = 0; i < b.nrCifre; ++i) {
        b.cifre[i] = s2[b.nrCifre - i - 1] - '0';
    }
    
    BigNumber c;
    int carry = 0;
    for (; c.nrCifre < max(a.nrCifre, b.nrCifre); ++c.nrCifre) {
        int val = a.cifre[c.nrCifre] + b.cifre[c.nrCifre] + carry;
        c.cifre[c.nrCifre] = val % 10;
        carry = val / 10;
    }
    if (carry) {
        c.cifre[c.nrCifre++] = carry;
    }
    
    char* res = new char[c.nrCifre + 1];
    memset(res, 0, c.nrCifre + 1);
    for (int i = 0; i < c.nrCifre; ++i) {
        res[i] = c.cifre[c.nrCifre - i - 1] + '0';
    }
    return res;
}

char* Math::Mul(const char* s, int x) {    
    BigNumber a;
    a.nrCifre = strlen(s);
    for (int i = 0; i < a.nrCifre; ++i) {
        a.cifre[i] = s[a.nrCifre - i - 1] - '0';
    }
    BigNumber b;
    int carry = 0;
    for (; b.nrCifre < a.nrCifre; b.nrCifre++) {
        carry += a.cifre[b.nrCifre] * x;
        b.cifre[b.nrCifre] = carry % 10;
        carry /= 10;
    }
    while (carry) {
        b.cifre[b.nrCifre++] = carry % 10;
        carry /= 10;
    }

    char* res = new char[b.nrCifre + 1];
    memset(res, 0, b.nrCifre + 1);
    for (int i = 0; i < b.nrCifre; ++i) {
        res[i] = b.cifre[b.nrCifre - i - 1] + '0';
    }

    return res;
}

char* Math::Sub(const char* s1, const char* s2) {
    bool neg = false;
    if (strlen(s2) > strlen(s1)) {
        neg = true;
    } else if (strlen(s2)==strlen(s1) && strcmp(s2, s1) > 0) {
        neg = true;
    }
    if (neg) {
        const char* aux = s1;
        s1 = s2;
        s2 = aux;
    }
    BigNumber a;
    a.nrCifre = strlen(s1);
    for (int i = 0; i < a.nrCifre; ++i) {
        a.cifre[i] = s1[a.nrCifre - i - 1] - '0';
    }
    BigNumber b;
    b.nrCifre = strlen(s2);
    for (int i = 0; i < b.nrCifre; ++i) {
        b.cifre[i] = s2[b.nrCifre - i - 1] - '0';
    }
    for (int i = 0; i < a.nrCifre; ++i) {
        if (a.cifre[i] >= b.cifre[i]) {
            a.cifre[i] -= b.cifre[i];
            continue;
        }
        int j = i + 1;
        for (; a.cifre[j] == 0; ++j) {
            a.cifre[j] = 9;
        }
        a.cifre[j] -= 1;
        a.cifre[i] += 10 - b.cifre[i];
    }
    while (a.nrCifre > 1 && a.cifre[a.nrCifre - 1] == 0) {
        a.nrCifre--;
    }
    char* res = new char[a.nrCifre + 1 + neg];
    memset(res, 0, a.nrCifre + 1 + neg);
    for (int i = 0; i < a.nrCifre; ++i) {
        res[i + neg] = a.cifre[a.nrCifre - i - 1] + '0';
    }
    if (neg) {
        res[0] = '-';
    }
    return res;
}