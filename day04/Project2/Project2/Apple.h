#pragma once
#include <string>

namespace jm // jm이 만든사과
{
	class Apple
	{
		//기본값이 private이라 바깥에서 접근이안된다.
	public:
		std::string Color;
		float weight;
		int quality;
		int calorie;

		void EatBy();
		void Calculate();
		inline int GetPrice() { return price; } //함수를 호출안하고 이 줄로 바꿔치기해서 실행이빠름
		// 함수가 짧은경우에 쓰기 괜찮

	private:
		int price;
	};
}
