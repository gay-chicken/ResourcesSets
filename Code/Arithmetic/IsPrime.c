int isPrimeEx(int num) {
    if (num == 2 || num == 3) return 1;
    if (num % 6 != 1 && num % 6 != 5) return 0;
    int tmp = sqrt(num);
    for (int i = 5; i <= tmp; i += 6)
        if (num % i == 0 || num % (i+2) == 0) return 0;
    return 1;
}

int isPrimeLow(int num) {
    if (num <= 2) return 0;

    int tmp = num -1;
    for (int i = 2; i <= tmp; ++i)
        if (num % i == 0) return 0;
    return 1;
}

int isPrime(int num) {
    if (num < 2) return 0;

    int tmp = sqrt(num);
    for (int i = 2; i <= tmp; ++i)
        if (num % i == 0) return 0;
    return 1;
}