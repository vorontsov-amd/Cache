#include <fstream>

int main(int argc, char const *argv[])
{
    std::ofstream out("test.txt");

    out << "10 10000 ";

    for (int i = 0; i < 10000; i++)
    {
        out << int(rand() % 100) << "\n";
    }

    return 0;
}

