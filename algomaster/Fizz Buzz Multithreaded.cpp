class FizzBuzz {
private:
    int n;
    binary_semaphore fizzBuzzSem {0};
    binary_semaphore fizzSem {0};
    binary_semaphore buzzSem {0};
    binary_semaphore numberSem {1};

public:
    FizzBuzz(int n) {
        this->n = n;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        for(int i : views::iota(1, n + 1) | views::filter([](int i) { return i % 3 == 0 && i % 5;})) {
            fizzSem.acquire();
            printFizz();
            numberSem.release();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        for(int i : views::iota(1, n + 1) | views::filter([](int i) { return i % 5 == 0 && i % 3;})) {
            buzzSem.acquire();
            printBuzz();
            numberSem.release();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        for(int i : views::iota(1, n + 1) | views::filter([](int i) { return i % 15 == 0;})) {
            fizzBuzzSem.acquire();
            printFizzBuzz();
            numberSem.release();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        for(int i : views::iota(1, n + 1)) {
            numberSem.acquire();
            if(i % 3 && i % 5) {
                printNumber(i);
                numberSem.release();
            } else if(i % 15 == 0)
                fizzBuzzSem.release();
            else if(i % 3 == 0)
                fizzSem.release();
            else
                buzzSem.release();
        }
    }
};

/*
For reference, the judge creates one thread per method (fizz, buzz,
fizzbuzz, and number) along these lines. In an interview, you can write
a driver like this yourself to demonstrate the full picture:

int main() {
    FizzBuzz fizzBuzz(15);

    thread fizzThread([&]() { fizzBuzz.fizz([]() { cout << "fizz" << endl; }); });
    thread buzzThread([&]() { fizzBuzz.buzz([]() { cout << "buzz" << endl; }); });
    thread fizzbuzzThread([&]() { fizzBuzz.fizzbuzz([]() { cout << "fizzbuzz" << endl; }); });
    thread numberThread([&]() { fizzBuzz.number([](int value) { cout << value << endl; }); });

    fizzThread.join();
    buzzThread.join();
    fizzbuzzThread.join();
    numberThread.join();

    // The turn protocol fixes the order, so this always prints
    // 1 2 fizz 4 buzz fizz 7 8 fizz buzz 11 fizz 13 14 fizzbuzz,
    // one token per line.
    return 0;
}
*/