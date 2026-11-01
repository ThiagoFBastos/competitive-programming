class ReadersWriters {
public:
    ReadersWriters() {

    }

    void read(function<void()> readAction) {
        shared_lock lock(_lock);
        _cv.wait(lock, [this]{ return !_has_writer; });

        {
            shared_lock lock(_lock);
            // readAction() performs one read. Do not change or remove this line.
            readAction();
        }
    }

    void write(function<void()> writeAction) {
        {
            _has_writer = true;
            unique_lock lock(_lock);
            // writeAction() performs one write. Do not change or remove this line.
            writeAction();
            _has_writer = false;
        }

        _cv.notify_all();
    }

private:
    shared_mutex _lock;
    condition_variable_any _cv;
    atomic<bool> _has_writer {};
};

/*
For reference, the judge creates and runs threads against your class
along these lines, with more threads that all start at the same time
to force contention. In an interview, you can write a driver like this
yourself to demonstrate the full picture:

int main() {
    ReadersWriters coordinator;
    int value = 0;

    auto writer = [&]() {
        for (int i = 0; i < 200; i++) {
            coordinator.write([&] { value++; });
        }
    };
    auto reader = [&]() {
        int seen = 0;
        for (int i = 0; i < 200; i++) {
            coordinator.read([&] { seen = value; });
        }
    };

    thread firstWriter(writer);
    thread secondWriter(writer);
    thread firstReader(reader);
    thread secondReader(reader);

    firstWriter.join();
    secondWriter.join();
    firstReader.join();
    secondReader.join();

    // Writers run exclusively, so no increment is lost and this always prints 400.
    cout << value << endl;
    return 0;
}
*/