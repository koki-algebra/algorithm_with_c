#include <iostream>
#include <list>

using namespace std;

int main() {
	list<char> L;

	L.push_front('b');
	L.push_back('c');
	L.push_front('a');

	cout << L.front();
	cout << L.back();

	L.pop_front();
	L.push_back('d');

	cout << L.front();
	cout << L.back() << endl;

	return 0;
}
