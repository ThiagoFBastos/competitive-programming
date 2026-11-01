class AtomicCounter {
public:
    AtomicCounter(int initialValue): _counter(initialValue) {

    }

    int incrementAndGet() {
        return ++_counter;
    }

    int addAndGet(int delta) {
        return _counter += delta;
    }

    int get() {
        return _counter;
    }

private:
    atomic<int> _counter;
};

/*
For reference, the judge creates and runs threads against your class
along these lines, with more threads that all start at the same time
to force contention. In an interview, you can write a driver like this
yourself to demonstrate the full picture:

int main() {
    AtomicCounter counter(0);

    auto worker = [&counter]() {
        for (int i = 0; i < 1000; i++) {
            counter.incrementAndGet();
            counter.addAndGet(4);
        }
    };

    thread first(worker);
    thread second(worker);

    first.join();
    second.join();

    // Each iteration adds 1 and then 4, so this always prints 10000.
    cout << counter.get() << endl;
    return 0;
}
*/