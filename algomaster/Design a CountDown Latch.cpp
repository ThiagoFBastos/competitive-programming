class CountDownLatch {
public:
    CountDownLatch(int initialCount)
    : _count(initialCount)
    {

    }

    void countDown() {
        unique_lock lock(_lock);
        if(_count == 0)
            return;
        else if(--_count == 0)
            _cv.notify_all();
    }

    void await() {
        unique_lock lock(_lock);
        _cv.wait(lock, [this] { return _count == 0; });
    }

    int getCount() {
        unique_lock lock(_lock);
        return _count;
    }

private:
    int _count;
    mutex _lock;
    condition_variable _cv;
};

/*
For reference, the judge creates and runs threads against your class
along these lines, with more threads that all start at the same time
to force contention. In an interview, you can write a driver like this
yourself to demonstrate the full picture:

int main() {
    CountDownLatch latch(4);
    int results[4] = {0, 0, 0, 0};

    vector<thread> workers;
    for (int i = 0; i < 4; i++) {
        workers.emplace_back([&latch, &results, i]() {
            results[i] = (i + 1) * 10;
            latch.countDown();
        });
    }

    latch.await();

    int sum = results[0] + results[1] + results[2] + results[3];

    // await returns only after all four countDown calls, so this always prints 100.
    cout << sum << endl;

    for (thread& worker : workers) {
        worker.join();
    }
    return 0;
}
*/