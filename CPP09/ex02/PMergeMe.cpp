#include "PMergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe& to_copy)
{
    *this = to_copy;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& to_copy)
{
	(void)to_copy;
	return *this;
}

PmergeMe::~PmergeMe()
{
}

unsigned int ft_stou(const std::string& str)
{
	unsigned int num;
	std::stringstream isstr(str);

	isstr >> num;
	return num;
}

static void printVec(const std::vector<unsigned int>& vec)
{
    for (std::vector<unsigned int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

static void printList(const std::list<unsigned int>& lst)
{
    for (std::list<unsigned int>::const_iterator it = lst.begin(); it != lst.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

static std::vector<unsigned int> mergeVecs(std::vector<unsigned int>& left, std::vector<unsigned int>& right)
{
    std::vector<unsigned int> result;
    while (!left.empty() && !right.empty()) {
        result.push_back((left.front() <= right.front()) ? left.front() : right.front());
        (left.front() <= right.front()) ? left.erase(left.begin()) : right.erase(right.begin());
    }
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return result;
}

static std::vector<unsigned int> mergeInsertVec(std::vector<unsigned int>& vec)
{
    if (vec.size() <= 1) return vec;
    int mid = vec.size() / 2;
    std::vector<unsigned int> left(vec.begin(), vec.begin() + mid);
    std::vector<unsigned int> right(vec.begin() + mid, vec.end());
    left = mergeInsertVec(left);
    right = mergeInsertVec(right);
    return mergeVecs(left, right);
}

void PmergeMe::sortVec(int argc, char **argv)
{
    std::vector<unsigned int> storage;
    for (int i = 1; i < argc; ++i) storage.push_back(ft_stou(argv[i]));

    std::cout << "<vec>Before: ";
    printVec(storage);

    std::clock_t start = std::clock();
    storage = mergeInsertVec(storage);
    double time_taken = static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC * 1e6;

    std::cout << "<vec>After: ";
    printVec(storage);

    std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector<unsigned int>: " << time_taken << " µs" << std::endl;
}

static std::list<unsigned int> mergeLists(std::list<unsigned int>& left, std::list<unsigned int>& right)
{
    std::list<unsigned int> result;
    while (!left.empty() && !right.empty()) {
        result.push_back((left.front() <= right.front()) ? left.front() : right.front());
        (left.front() <= right.front()) ? left.erase(left.begin()) : right.erase(right.begin());
    }
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return result;
}

static std::list<unsigned int> mergeInsertList(std::list<unsigned int>& lst)
{
    if (lst.size() <= 1) return lst;
    int mid = lst.size() / 2;
    std::list<unsigned int> left, right;
    for (int i = 0; i < mid; ++i) { left.push_back(lst.front()); lst.pop_front(); }
    right = lst;
    left = mergeInsertList(left);
    right = mergeInsertList(right);
    return mergeLists(left, right);
}

void PmergeMe::sortList(int argc, char **argv)
{
    std::list<unsigned int> storage;
    for (int i = 1; i < argc; ++i) storage.push_back(ft_stou(argv[i]));

    std::cout << "<list>Before: ";
    printList(storage);

    std::clock_t start = std::clock();
    storage = mergeInsertList(storage);
    double time_taken = static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC * 1e6;

    std::cout << "<list>After: ";
    printList(storage);

    std::cout << "Time to process a range of " << argc - 1 << " elements with std::list<unsigned int>: " << time_taken << " µs" << std::endl;
}

const char* PmergeMe::wrong_input_exception::what() const throw()
{
    return "PmergeMe exception: invalid element";
}
