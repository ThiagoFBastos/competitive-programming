class FooBar {
private:
    int n;
    binary_semaphore fooSem{1};
    binary_semaphore barSem{0};

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            fooSem.acquire();
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            barSem.release();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            barSem.acquire();
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            fooSem.release();
        }
    }
};