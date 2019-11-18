//A counting sort implementation
//By Elliott Nash, v0idx.com


//Include headers
#include <iostream>
#include <string>
#include <fstream>
#include <vector>


//Split a vector of strings into individual 'words' as denoted by a delimiter
std::vector<std::string> delimSplit(std::vector<std::string> strs, char delim) {
	std::string currBuff;
	std::vector<std::string> returnVector;
	
	for (std::string& str : strs) {
		for (char c : str) {
			if (c != delim) {
				currBuff += c;
			}
			else {
				returnVector.push_back(currBuff);
				currBuff.clear();
			}
		}
		returnVector.push_back(currBuff);
		currBuff.clear();
	}

	return returnVector;
}

//Get all lines from a user defined file
std::vector<std::string> getLines(std::string fileName) {
	std::fstream file(fileName);
	std::vector<std::string> returnVector;
	if (!file) {
		std::cerr << "Could not open " << fileName << std::endl;
		return returnVector;
	}

	std::string line;

	while (std::getline(file, line)) {
		if (line.size() > 0) {
			returnVector.push_back(line);
		}
	}

	file.close();
	return returnVector;

}

//Convert a string vector to an integer vector
std::vector<int> conStrToIntVec(std::vector<std::string> vec) {
	std::vector<int> returnVector;
	for (std::string& str : vec) {
		returnVector.push_back(std::stoi(str));
	}

	return returnVector;
}

//Find the maximum value in an integer vector
int findMax(std::vector<int> vec) {
	int max = 0;

	for (const int& i : vec) {
		if (i > max) {
			max = i;
		}
	}

	return max;
}

//Dynamically insert elements, resizing the array as needed to have duplicates
void insertAt(std::vector<int>& vec, int pos, int item) {
	if (vec[pos] == -1) {
		vec[pos] = item;
		return;
	}
	else {
		std::vector<int> tail;
		for (int i = pos+1; i < vec.size(); i++) {
			tail.push_back(vec[i]);
		}
		std::vector<int> returnVector;
		for (int i = 0; i <= pos; i++) {
			returnVector.push_back(vec[i]);
		}
		returnVector.push_back(item);
		for (int i : tail) {
			returnVector.push_back(i);
		}
		vec = returnVector;
	}
}

//Procedure to get all numbers in a file (seperated by commas)
std::vector<int> getNumbers(std::string fileName) {
	std::vector<std::string> lines = getLines(fileName);
	lines = delimSplit(lines, ',');
	std::vector<int> numbers = conStrToIntVec(lines);
	return numbers;
}

//Collapse a vector to remove clutter, all non-modified elements are removed
void collapseVec(std::vector<int>& vec) {
	std::vector<int> returnVector;
	for (int i : vec) {
		if (i != -1) {
			returnVector.push_back(i);
		}
	}

	vec = returnVector;
}

//Performs the counting sort
void countSort(std::vector<int>& vec) {
	int max = findMax(vec);
	std::vector<int> returnVector;
	for (int i = 0; i < max + 1; i++) {
		returnVector.push_back(-1);
	}
	for (int i : vec) {
		insertAt(returnVector, i, i);
	}

	collapseVec(returnVector);
	vec = returnVector;
}

//Template function to print any type of vector to a text file
template <typename T> void printVec(T vec, std::string fileName) {
	std::ofstream file(fileName);

	for (typename T::value_type x : vec) {
		file << x << ' ';
	};

	file.close();
}


int main(int argc, char *argv[]) {

	if ((argv[1] == "-h") || (argv[1] == "--help")) {
		std::cerr << "USEAGE: " << argv[0] << "UNSORTED NUM FILE" << "SORTED FILE NAME";
		return 1;
	};

	std::vector<int> nums = getNumbers(argv[1]);

	countSort(nums);

	printVec(nums, argv[2]);
	
	return 0;
}
