class ConcurrencyLimiter {
public:
    ConcurrencyLimiter(int maxConcurrent) 
    : _sem(maxConcurrent)
    {

    }

    void run(function<void()> task) {
        _sem.acquire();
        try {
            task();
        } catch(...) {
            _sem.release();
            throw;
        }
        _sem.release();
    }

private:
    static constexpr int MAX_CONCURRENT = 32;

    counting_semaphore<MAX_CONCURRENT> _sem;
};

/*
For reference, the judge creates and runs threads against your class
along these lines, with more threads that all start at the same time
to force contention. In an interview, you can write a driver like this
yourself to demonstrate the full picture:

int main() {
    ConcurrencyLimiter limiter(1);
    int counter = 0;

    auto worker = [&limiter, &counter]() {
        for (int i = 0; i < 500; i++) {
            limiter.run([&counter]() { counter++; });
        }
    };

    vector<thread> threads;
    for (int i = 0; i < 4; i++) {
        threads.emplace_back(worker);
    }
    for (thread& runner : threads) {
        runner.join();
    }

    // The single permit serializes every increment, so this always prints 2000.
    cout << counter << endl;
    return 0;
}
*/