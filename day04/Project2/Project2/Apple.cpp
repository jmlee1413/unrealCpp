#include "Apple.h"
#include <iostream>

namespace jm  // 헤더 묶어줬으니 여기도
{
	void Apple::EatBy() // Apple 에 포함된 함수라는뜻
	{
		std::cout << "먹혔다";
	}

	void Apple::Calculate()
	{
		price = weight * quality;
	}

}