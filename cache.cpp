#include "cache.h"

int main()
{
    std::priority_queue<int> q;
    q.push(5);
    q.push(4);
    q.push(3);
    q.push(2);
    q.push(1);
    q.push(11);
    q.push(3);

    while (!q.empty())
    {
        std::cout << q.top() << " ";
        q.pop();
    }
}