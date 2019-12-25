#include <iostream>
#include "TList.h"

using namespace std;
void main() {
	try {
		TList<int> List;
		int size = 10, tmp;
		for (int i = 0; i < size; i++) {
			tmp = rand()%100;
			List.InsInOrder(tmp);
			cout << tmp << endl;
		}
		cout << "Ordered list:" << endl;
		for (List.Reset(); !List.IsEnd(); List.GoNext()) {
			cout << List.GetCurrEl()<<" | ";
		}
	}
	catch (char *s) {
		cout << s;
	}
	system("pause");
}