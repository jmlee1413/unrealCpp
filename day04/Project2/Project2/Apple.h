#pragma once
#include <string>

namespace jm // jm�� ������
{
	class Apple
	{
		//�⺻���� private�̶� �ٱ����� �����̾ȵȴ�.
	public:
		std::string Color;
		float weight;
		int quality;
		int calorie;

		void EatBy();
		void Calculate();
		inline int GetPrice() { return price; } //�Լ��� ȣ����ϰ� �� �ٷ� �ٲ�ġ���ؼ� �����̺���
		// �Լ��� ª����쿡 ���� ����

	private:
		int price;
	};
}
