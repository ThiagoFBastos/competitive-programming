class Foo {
public:
    Foo() {

    }

    void first(function<void()> printFirst) {
        _firstSem.acquire();
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        _secondSem.release();
    }

    void second(function<void()> printSecond) {
        _secondSem.acquire();
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        _thirdSem.release();
    }

    void third(function<void()> printThird) {
        _thirdSem.acquire();
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }

private:
    binary_semaphore _firstSem {1};
    binary_semaphore _secondSem {0};
    binary_semaphore _thirdSem {0};
};

/*
For reference, the judge creates one thread per method (first, second,
third) along these lines. In an interview, you can write a driver like
this yourself to demonstrate the full picture:

int main() {
    Foo foo;
    string output;

    thread third([&] { foo.third([&] { output += "third"; }); });
    thread second([&] { foo.second([&] { output += "second"; }); });
    thread first([&] { foo.first([&] { output += "first"; }); });

    third.join();
    second.join();
    first.join();

    // The synchronization enforces the order first, second, third,
    // so this always prints firstsecondthird.
    cout << output << endl;
    return 0;
}
*/