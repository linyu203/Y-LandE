#include <iostream>
using namespace std;

typedef unsigned long long ULL;

const ULL MAX_NUM = 2000000;
const ULL MIN_NUM = 1;
const ULL MAX_EVER_NUM = 1111111110;
const ULL MAX_EVER_NUM_9 = 9999999999;

ULL count1num(ULL ull)
{
	ULL count =0;
	ULL factors = 1;
	ULL CurrntNum = 0;
	ULL LowerNum = 0;
	ULL HigherNum = 0;
	while(ull>=factors)
	{
		LowerNum = ull - (ull / factors)*factors;
		CurrntNum = (ull / factors)%10;
		HigherNum = ull / (factors * 10);
		switch (CurrntNum)
		{
		case 0:
			count += HigherNum * factors;
			break;
		case 1:
			count += HigherNum * factors + LowerNum + 1;
			break;
		default:
			count += (HigherNum + 1) * factors;
			break;
		}
		factors *= 10;
	}
	return count;
}

void main()
{
	ULL l = 0;
	cout<< MAX_EVER_NUM << " has 1 num : "<<  count1num(MAX_EVER_NUM)<<endl;
	cout<< MAX_EVER_NUM_9 << " has 1 num : "<<  count1num(MAX_EVER_NUM_9)<<endl;
	cout<< MIN_NUM << " has 1 num : "<<  count1num(MIN_NUM)<<endl;
	cout<< MAX_NUM << " has 1 num : "<<  count1num(MAX_NUM)<<endl;
	ULL max = MAX_NUM;
	ULL min = MIN_NUM;
	//ULL mid = (max+min)/2;
	//l = mid;
	for(l = min; l <= max; l++)
	{
		if(l == count1num(l))
			cout<< l << endl;
	}
	system("pause");
}