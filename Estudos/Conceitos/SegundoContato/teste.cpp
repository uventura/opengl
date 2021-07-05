#include <iostream>
#include <vector>

struct aba
{
	unsigned int m_id;

	aba(int id)
	{
		m_id = id;
	}
};

aba foo()
{
	return aba(5);
}

int main()
{
	aba teste = foo();
	std::cout << teste.m_id << "\n";
}