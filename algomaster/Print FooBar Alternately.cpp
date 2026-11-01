class FooBar {
private:
    int n;

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            _fooSem.acquire();
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            _barSem.release();
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            _barSem.acquire();
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            _fooSem.release();
        }
    }

private:
    binary_semaphore _fooSem {1};
    binary_semaphore _barSem {0};
};

/*
For reference, the judge creates one thread per method (foo and bar)
along these lines. In an interview, you can write a driver like this
yourself to demonstrate the full picture:

int main() {
    FooBar fooBar(2);

    thread fooThread([&]() { fooBar.foo([]() { cout << "foo"; }); });
    thread barThread([&]() { fooBar.bar([]() { cout << "bar"; }); });

    fooThread.join();
    barThread.join();

    // The handoff enforces strict alternation, so this always
    // prints foobarfoobar.
    cout << endl;
    return 0;
}
*/