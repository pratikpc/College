#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
std::ostream& operator <<(std::ostream& os, const std::vector<T>& vec)
{
	os << "{ ";
	for (const T& val : vec)
		os << val << ',';
	os << '}';
	return os;
}
template<typename T>
std::ostream& operator <<(std::ostream& os, const std::vector<std::vector<T>>& vec)
{
	os << "{ \n";
	for (const std::vector<T>& val : vec)
		os << val << '\n';
	os << '}';
	return os;
}

template<typename List>
void sortAndUnique(List& p_list)
{
	std::sort(std::begin(p_list), std::end(p_list));
	p_list.erase(std::unique(std::begin(p_list), std::end(p_list)), std::end(p_list));
}

std::vector<int> inputVector()
{
	std::vector<int> inputVec;
	char ch;

	do
	{
		std::cout << "\nEnter value\t:";
		int i;
		std::cin >> i;
		inputVec.push_back(i);
		std::cout << "\nAdd other element(Y or N)?\t:";
		std::cin >> ch;
	} while (ch == 'y' || ch == 'Y');

	return inputVec;
}

std::vector<std::vector<int>> getPowerSet(const std::vector<int>& p_set)
{
	//Set must contain only unique values 
	//Before Power Set Calculated
	sortAndUnique(p_set);

	std::vector<std::vector<int>> power_set;
	// Initial Set has to be Null Set
	power_set.push_back(std::vector<int>{0});

	// Iterate over entire set
	for (std::vector<int>::size_type a = 0; a < std::size(p_set); ++a)
		for (std::vector<int>::size_type b = 0; b < std::size(p_set)-a; ++b)
		{
			std::vector<int> subset;
			for (std::vector<int>::size_type c = a; c < std::size(p_set) - b; ++c)
				subset.push_back(p_set[c]);
			power_set.push_back(subset);
		}

	return power_set;
}

int main()
{
	std::cout << "Enter Elements into Set\t:";
	const std::vector<int> set = inputVector();

	std::cout << "The Power Set is:\n";
	std::cout << getPowerSet(set);

	std::cin.get();
}

