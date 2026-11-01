class ZeroEvenOdd {
private:
    int n;
    binary_semaphore zeroSem {1};
    binary_semaphore evenSem {0};
    binary_semaphore oddSem {0};
public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    void zero(function<void(int)> printNumber) {
        for(int i = 1; i <= n; ++i) {
            zeroSem.acquire();
            printNumber(0);

            if(i % 2 == 1)
                oddSem.release();
            else
                evenSem.release();
        }
        // printNumber(x) outputs "x", where x is an integer.
    }

    void even(function<void(int)> printNumber) {
        for(int i = 2; i <= n; i += 2) {
            evenSem.acquire();
            printNumber(i);
            zeroSem.release();
        }
        // printNumber(x) outputs "x", where x is an integer.
    }

    void odd(function<void(int)> printNumber) {
        for(int i = 1; i <= n; i += 2) {
            oddSem.acquire();
            printNumber(i);
            zeroSem.release();
        }
        // printNumber(x) outputs "x", where x is an integer.
    }
};

/*
For reference, the judge creates one thread per method (zero, even, odd)
along these lines. In an interview, you can write a driver like this
yourself to demonstrate the full picture:

int main() {
    ZeroEvenOdd zeroEvenOdd(5);
    string output;
    auto printNumber = [&](int value) { output += to_string(value); };

    thread zero([&] { zeroEvenOdd.zero(printNumber); });
    thread even([&] { zeroEvenOdd.even(printNumber); });
    thread odd([&] { zeroEvenOdd.odd(printNumber); });

    zero.join();
    even.join();
    odd.join();

    // The handoff protocol fixes the callback order,
    // so this always prints 0102030405.
    cout << output << endl;
    return 0;
}
*/