
void extendedEuclid(long long A, long long B, long long &d, long long &x, long long &y) {
    if(B == 0) {
        d = A;
        x = 1;
        y = 0;
    }
    else {
        extendedEuclid(B, A%B);
        long long temp = x;
        x = y;
        y = temp - (A/B)*y;
    }
}

long long modInverse(long long A, long long M)
{
    long long d, x, y;
    extendedEuclid(A, M, d, x, y);
    return (x%M+M)%M;    //x may be negative
}
