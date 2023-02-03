#include <iostream>
#include <thread>
#include <vector>
#include "threadQueue.h"

using namespace std;

constexpr auto ITEMCOUNT = 5000;

/*ALGO SHCEDULING V CONCURRENCY DOES NOT WORK WITH TIMED MUTEXES */
//int global_counter = 0;
//std::mutex counter_mutex;


double timeThreadCounter(int numThreads) {
	threadQueue<int> q1;

	vector<thread> arrThread;

	int itemsPerThread = round(ITEMCOUNT / numThreads);

	std::chrono::high_resolution_clock::time_point time1 = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < numThreads; i++) {
		arrThread.push_back(thread([&]() { for (int i = 0; i < itemsPerThread; i++) { q1.enqueue(i + 1); }; }));
	}
	for (auto& x : arrThread) {
		x.join();
	}

	std::chrono::high_resolution_clock::time_point time2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(time2 - time1);

	cout << q1.size() << endl;
	cout << time_span.count() << endl;
	return time_span.count();
}


int main() {
	double holder[20];
	for (int i = 0; i < 20; i++) {
		holder[i] = timeThreadCounter(i + 1);
		cout << "number of threads: " << i + 1 << "; operation time: " << holder[i] << endl;
	}


	return 0;
}