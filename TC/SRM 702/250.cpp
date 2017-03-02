#include <stdio.h>
#include <algorithm>
using namespace std;
class TestTaking
{
public:
	int findMax(int questions,int guessed,int actual)
	{
		return min(guessed,questions)+min(questions-guessed,questions-actual);
	}
}
int main()
{
	
}
