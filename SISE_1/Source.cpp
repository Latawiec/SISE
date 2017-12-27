#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;


void Info()
{
	cout << "Information:\n"
		<< "Available threads: " << std::thread::hardware_concurrency() << '\n';
}

void DFS()
{
	string data;
	cin >> data;

	cout << data;
}

void BFS()
{

}

void AStar()
{

}

vector<string> Parse(const string& aCommand) {
	size_t pos = 0;
	size_t lastPos = 0;
	vector<string> result{};
	while (pos != aCommand.size())
	{
		pos = aCommand.find(" ");
		result.push_back(aCommand.substr(lastPos, pos));
		lastPos = pos;
	}
	return result;
}

int main(int count, char ** args)
{
	Info();
	string input;
	cin >> input;

	while (input != "q")
	{
		if (input == "dfs")
		{
			DFS();
		}
		else if (input == "bfs")
		{

		}
		else if (input == "astr")
		{

		}


		cin >> input;
	}
}