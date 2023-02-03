#ifndef threadQueue_h
#define threadQueue_h

#include <queue>
#include <mutex>
#include <thread>
#include <semaphore>

using namespace std;

template <typename T> class threadQueue {

private:
	timed_mutex a1;
	std::queue<typename T> q;

public:
	void enqueue(typename T element) {
		/*
		if (a1.try_lock_for(std::chrono::nanoseconds(20))) {
			q.push(element);
			std::this_thread::sleep_for(chrono::nanoseconds(10));
			a1.unlock();
		}
		*/
		a1.lock();
		q.push(element);
		a1.unlock();
	}

	typename T pop() {
		a1.lock();
		T retVal = q.front();
		q.pop();
		a1.unlock();
		return retVal;
	}

	int size() {
		a1.lock();
		int ret = q.size();
		a1.unlock();
		return ret;
	}

	bool empty() {
		if (q.size()) {
			return false;
		}
		return true;
	}
};


#endif // 
