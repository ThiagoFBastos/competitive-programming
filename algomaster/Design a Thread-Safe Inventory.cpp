class ThreadSafeInventory {
public:
    ThreadSafeInventory(int initialStock): _stock(initialStock) {

    }

    bool tryPurchase(int quantity, function<void()> onPurchased) {
        _lock.lock();
        bool enough = _stock >= quantity;

        if(enough) {
            _stock -= quantity;
            _lock.unlock();
            onPurchased();
        } else
            _lock.unlock();

        return enough;
    }

    void restock(int quantity) {
        std::scoped_lock lock(_lock);
        _stock += quantity;
    }

    int available() {
        std::scoped_lock lock(_lock);
        return _stock;
    }

private:
    int _stock;
    std::mutex _lock;
};

/*
For reference, the judge creates and runs threads against your class
along these lines, with more threads that all start at the same time
to force contention. In an interview, you can write a driver like this
yourself to demonstrate the full picture:

int main() {
    ThreadSafeInventory inventory(1000);
    vector<int> callbackCalls(2, 0);

    vector<thread> buyers;
    for (int t = 0; t < 2; t++) {
        buyers.emplace_back([&inventory, &callbackCalls, t] {
            for (int i = 0; i < 500; i++) {
                inventory.restock(3);
                inventory.tryPurchase(2, [&callbackCalls, t] { callbackCalls[t]++; });
            }
        });
    }
    for (thread& buyer : buyers) {
        buyer.join();
    }

    // Each thread restocks 3 units before purchasing 2, so no purchase is
    // ever rejected and this always prints 1000.
    cout << callbackCalls[0] + callbackCalls[1] << endl;

    // Each iteration adds 3 units and removes 2, so this always prints 2000.
    cout << inventory.available() << endl;
    return 0;
}
*/