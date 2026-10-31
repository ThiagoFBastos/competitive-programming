class VersionedSignal {
public:
    VersionedSignal() 
    : _version(0)
    {

    }

    int currentVersion() {
        scoped_lock lk(_lock);
        return _version;
    }

    int awaitNext(int observedVersion) {
        unique_lock lk(_lock);
        _cv.wait(lk, [this, observedVersion] { return _version > observedVersion;});
        return _version;
    }

    void signal() {
        {
            scoped_lock lk(_lock);
            ++_version;
        }

        _cv.notify_all();
    }

private:
    condition_variable _cv;
    mutex _lock;
    int _version;
};

/*
For reference, the judge creates and runs threads against your class
along these lines, with more threads that all start at the same time
to force contention. In an interview, you can write a driver like this
yourself to demonstrate the full picture:

int main() {
    VersionedSignal signal;

    auto signaler = [&]() {
        for (int i = 0; i < 500; i++) {
            signal.signal();
        }
    };

    thread first(signaler);
    thread second(signaler);

    first.join();
    second.join();

    // All 1000 signals have committed, so awaitNext returns without
    // blocking and this always prints 1000.
    cout << signal.awaitNext(999) << endl;
    return 0;
}
*/