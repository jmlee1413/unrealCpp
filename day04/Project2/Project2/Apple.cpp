#include "Apple.h"
#include <iostream>

namespace jm  // ��� ���������� ���⵵
{
	void Apple::EatBy() // Apple �� ���Ե� �Լ���¶�
	{
		std::cout << "������";
	}

	void Apple::Calculate()
	{
		price = weight * quality;
	}

}