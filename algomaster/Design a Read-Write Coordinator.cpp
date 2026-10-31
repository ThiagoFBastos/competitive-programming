class ReadWriteCoordinator {
public:
    ReadWriteCoordinator() {

    }

    void read(function<void()> readTask) {
        shared_lock lk(_lock);

        // readTask() performs one read. Do not change or remove this line.
        readTask();
    }

    void write(function<void()> writeTask) {
        unique_lock lk(_lock);
        // writeTask() performs one write. Do not change or remove this line.
        writeTask();
    }

private:
    shared_mutex _lock;
};

/*
For reference, the judge creates and runs threads against your class
along these lines, with more threads that all start at the same time
to force contention. In an interview, you can write a driver like this
yourself to demonstrate the full picture:

int main() {
    ReadWriteCoordinator coordinator;
    int value = 0;

    auto writer = [&]() {
        for (int i = 0; i < 500; i++) {
            coordinator.write([&]() { value++; });
        }
    };
    auto reader = [&]() {
        for (int i = 0; i < 500; i++) {
            coordinator.read([&]() { int snapshot = value; });
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

    // Each of the 1000 writes adds 1, so this always prints 1000.
    cout << value << endl;
    return 0;
}
*/