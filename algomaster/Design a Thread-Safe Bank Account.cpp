class BankAccount {
public:
    BankAccount(long long initialBalance): _amount(initialBalance) {

    }

    void deposit(long long amount) {
       std::scoped_lock lock(_lock);
        _amount += amount;
    }

    bool withdraw(long long amount) {
        std::scoped_lock lock(_lock);
        bool enough = true;
        if(_amount >= amount)
            _amount -= amount;
        else
            enough = false;
        return enough;
    }

    long long getBalance() {
        std::scoped_lock lock(_lock);
        auto answer = _amount;
        return answer;
    }

private:
    long long _amount;
    std::mutex _lock;
};

/*
For reference, the judge creates and runs threads against your class
along these lines, with more threads that all start at the same time
to force contention. In an interview, you can write a driver like this
yourself to demonstrate the full picture:

int main() {
    BankAccount account(100000);

    auto customer = [&account]() {
        for (int i = 0; i < 1000; i++) {
            account.deposit(7);
            account.withdraw(5);
        }
    };

    thread first(customer);
    thread second(customer);

    first.join();
    second.join();

    // Each iteration adds 7 and removes 5, so this always prints 104000.
    cout << account.getBalance() << endl;
    return 0;
}
*/