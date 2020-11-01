#include <fstream> 
#include <iostream> 
#include<stdio.h> 
#include<string>
#include<sstream>
#include<vector>

using namespace std;

class Matrix
{
	int m_size;
	vector<vector<int>> values;
public:
	Matrix(int n);
	Matrix(int n, int diag);
	Matrix(const Matrix& orig);
	int size();
	bool operator==(const Matrix& next) const;
	Matrix operator*(const Matrix& next) const;
	Matrix operator*(int coef) const;
	Matrix operator+(const Matrix& next) const;
	Matrix operator-(const Matrix& next) const;
	Matrix& operator=(const Matrix& next);
	vector<int>& operator[](const int& i);
	void scan_Matrix(ifstream& inFile);
	Matrix trans();
	void print(string Path = "output.txt");
};

Matrix::Matrix(int n)
{
	m_size = n;
	values = vector<vector<int>>(n, vector<int>(n));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			values[i][j] = 0; //values[i][j] = rand()
		}
	}
}
Matrix::Matrix(int n, int diag)
{
	m_size = n;
	values = vector<vector<int>>(n, vector<int>(n));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				values[i][j] = diag;
			}
			else
			{
				values[i][j] = 0;
			}
		}
	}
}
Matrix::Matrix(const Matrix& orig)
{
	m_size = orig.m_size;
	values = vector<vector<int>>(m_size, vector<int>(m_size));
	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			values[i][j] = orig.values[i][j];
		}
	}
}
int Matrix::size()
{
	return m_size;
}
bool Matrix::operator==(const Matrix& next) const
{
	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			if (values[i][j] != next.values[i][j])
			{
				return false;
			}
		}
	}
	return true;
}
Matrix Matrix::operator*(const Matrix& next) const
{
	Matrix res(m_size, 0);
	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			for (int k = 0; k < m_size; k++)
			{
				res.values[i][j] += values[i][k] * next.values[k][j];
			}
		}
	}
	return res;
}
Matrix Matrix::operator*(int coef) const
{
	Matrix res(m_size, 0);
	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			res.values[i][j] = coef * values[i][j];
		}
	}
	return res;
}
Matrix Matrix::operator+(const Matrix& next) const
{
	Matrix res(m_size, 0);
	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			res.values[i][j] = values[i][j] + next.values[i][j];
		}

	}
	return res;
}
Matrix Matrix::operator-(const Matrix& next) const
{
	Matrix res(m_size, 0);
	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			res.values[i][j] = values[i][j] - next.values[i][j];
		}

	}
	return res;
}
Matrix& Matrix::operator=(const Matrix& next)
{
	if (m_size == next.m_size)
	{
		for (int i = 0; i < m_size; i++)
		{
			for (int j = 0; j < m_size; j++)
			{
				values[i][j] = next.values[i][j];
			}
		}
	}
	else
	{
		values.clear();
		values = vector<vector<int>>(m_size, vector<int>(m_size));
		for (int i = 0; i < m_size; i++)
		{
			for (int j = 0; j < m_size; j++)
			{
				values[i][j] = next.values[i][j];
			}
		}
	}
	return (*this);
}
vector<int>& Matrix::operator[](const int& i)
{
	if (i < m_size)
	{
		return values[i];
	}
	else
	{
		cout << "ERROR: Going Out Of Array";
		exit(1);
	}

}
void Matrix::scan_Matrix(ifstream& inFile)
{
	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			inFile >> values[i][j];
		}
	}
}
Matrix Matrix::trans()
{
	Matrix TR(m_size, 0);
	for (int i = 0; i < TR.m_size; i++)
	{
		for (int j = 0; j < TR.m_size; j++)
		{
			TR.values[i][j] = values[j][i];
		}

	}
	return TR;
}
void Matrix::print(string Path)
{
	ofstream out;
	out.open(Path);
	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			out << values[i][j] << " ";
		}
		out << endl;
	}
	out.close();
}


void Greeting()
{
	cout << "Tsibilev Oleg Dmitrievich" << "\n" <<
		"Novosibirsk State University, Mathematics and Mechanics department" << "\n" << "Group 20161" << "\n" << "Determining the Strongly Regular Graph" << "\n" << "\n";
}

// function that determines whether a graph is strongly regular by its adjacency matrix
bool SRGraph(Matrix& A)
{
	
	// check for empty graph
	Matrix O(A.size(), 0);
	if (A == O)
	{
		cout << "\n" << "The given Graph is Strongly Regular Empty Graph with parameters: " <<
			"(" << A.size() << ", " << 0 << ", " << 0 << ", " << 0 << ")\n";

		cout << "\n" << "The spectrum of the given Graph: " <<
			"sp(G) = [" << 0 << "^" << A.size() << "]\n";
		return true;
	}

	// check for complete graph
	int sum = 0;
	int number = 0;
	for (int i = 0; i < A.size(); i++)
	{
		sum = 0;
		for (int j = 0; j < A.size(); j++)
		{
			if (A[i][j] == 1)
			{
				sum++;
			}
		};
		if (sum != A.size() - 1)
		{
			break;
		}
		else
		{
			number++;
		}
	};
	if (number == A.size())
	{
		cout << "\n" << "The given Graph is Strongly Regular Complete Graph with parameters: " <<
			"(" << A.size() << ", " << A.size() - 1 << ", " << A.size() - 2 << ", " << 0 << ")\n";

		cout << "\n" << "Intersection Array of the given Graph: " <<
			"{" << A.size() - 1 << "; " << 1 << "}\n";

		cout << "\n" << "The spectrum of the given Graph: " <<
			"sp(G) = [" << A.size() - 1 << "^1" << ", " << -1 << "^" << A.size() - 1 << "]\n";
		return true;
	}

	int regularity = 0;
	for (int j = 0; j < A.size(); j++)
	{
		if (A[0][j] == 1)
		{
			regularity++;
		}
	};
	int k = 0;
	for (int i = 1; i < A.size(); i++) //k-regularity check
	{
		k = 0;
		for (int j = 0; j < A.size(); j++)
		{
			if (A[i][j] == 1)
			{
				k++;
			}
		};
		if (k != regularity)
		{
			cout << "\n" << "The given Graph is not Strongly Regular Graph\n";
			return false;
		}
	};
	// check disconnectedness????



	//continue calculations

	int lambda = 0;
	int v1 = 0;
	int v2 = 0;
	for (int j = 0; j < A.size(); j++) //found a vertex adjacent to v1 - v2 (from the sphere S1(v1) in the layered representation)
	{
		if (A[v1][j] == 1)
		{
			v2 = j;
			break;
		}
	};

	if (v2 == 0) // graph is disconnected
	{
		cout << "\n" << "The given Graph is not Strongly Regular Graph\n";
		return false;
	}

	//calculate lambda = a1
	for (int i = 0; i < A.size(); i++)
	{
		if ((A[v2][i] == 1) && (A[v1][i] == 1)) // the number of vertices adjacent to v1 and v2
		{
			lambda++;
		}
	};

	int mu = 0;
	int v3 = 0;
	for (int j = 0; j < A.size(); j++) //found a vertex adjacent to v2 and not adjacent to v1 - v3 (from the sphere S2(v1) in the layered representation)
	{
		if ((A[v2][j] == 1) && (A[v1][j] != 1) && (j != v1) && (j != v2))
		{
			v3 = j;
			break;
		}
	};

	if (v3 == 0) // graph is disconnected and k-regular => graph consists of Kn
	{
		cout << "\n" << "The given Graph is Strongly Regular Graph and it's Union of Complete Graphs K_" << regularity +1 << "\n";
		cout << "Parameters of the given Graph: " <<
			"(" << A.size() << ", " << regularity << ", " << regularity - 2 << ", " << 0 << ")\n";

		cout << "\n" << "Intersection Array of the given Graph: " <<
			"{" << regularity << "; " << 1 << "}\n";

		cout << "\n" << "The spectrum of the given Graph: " <<
			"sp(G) = [" << regularity << "^" << A.size()/(regularity + 1) << ", " << -1 << "^" << regularity * A.size() / (regularity + 1) << "]\n";
		return false;
	}

	//calculate mu = с2
	for (int i = 0; i < A.size(); i++)
	{
		if ((A[v1][i] == 1) && (A[i][v3] == 1)) // c2 = the number of vertices adjacent to v1 and v3
		{
			mu++;
		}
	};
	// check for parameters connection
	if (mu != 0)
	{
		if (A.size() != (1 + regularity + (regularity * (regularity - 1 - lambda)) / mu))
		{
			cout << "\n" << "The given Graph is not Strongly Regular Graph\n";
			return false;
		}
	}
	Matrix A2 = A * A;
	Matrix I(A.size(), 1);
	Matrix J(A.size(), 1);
	for (int i = 0; i < A.size(); i++)
	{
		for (int j = 0; j < A.size(); j++)
		{
			J[i][j] = 1;
		};
	};

	Matrix Right(A.size()); // = (A * (lambda - mu) + I * (regularity - mu) + J * mu);
	for (int i = 0; i < A.size(); i++)
	{
		for (int j = 0; j < A.size(); j++)
		{
			Right[i][j] = A[i][j] * (lambda - mu) + I[i][j] * (regularity - mu) + J[i][j] * mu;
		};
	};
	// 
	// theorem check: A^2 = (A * (lambda - mu) + I * (regularity - mu) + J * mu);
	//
	if (A2 == Right)
	{
		double eig_val1 = 0;
		double eig_val2 = 0;
		double m1 = 0;
		double m2 = 0;
		eig_val1 = (lambda - mu) / 2.0 + sqrt(((lambda - mu) * (lambda - mu) / 4.0 - (mu - regularity)));
		eig_val2 = (lambda - mu) / 2.0 - sqrt(((lambda - mu) * (lambda - mu) / 4.0 - (mu - regularity)));
		m2 = (((A.size() - 1) * eig_val1 + regularity) / (eig_val1 - eig_val2));
		m1 = A.size() - 1 - m2;
		cout << "\n" << "The given Graph is Strongly Regular Graph with parameters: " <<
			"(" << A.size() << ", " << regularity << ", " << lambda << ", " << mu << ")\n";

		cout << "\n" << "Intersection Array of the given Graph: " <<
			"{" << regularity << ", " << regularity - lambda - 1 << "; " << 1 << ", " << mu << "}\n";

		cout << "\n" << "The spectrum of the given Graph: " <<
			"sp(G) = [" << regularity << "^1" << ", " << eig_val1 << "^"  <<m1<< ", " << eig_val2 << "^" << m2 << "]\n";

		return true;
	}
	else
	{
		cout << "\n" << "The given Graph is not Strongly Regular Graph\n";
		return false;
	}
}

// function for generating data for function SRGraph
void Strongly_Regular_Graph()
{
	cout << "\nGraph generation:" << "\n";
	cout << "Enter entry_ID:" << "\n" << " 1 - to put Graph as adjacency matrix" << "\n";
	cout << " 2 - to put Graph as adjacency list" << "\n";
	cout << " 3 - to exit" << "\n";
	char entry_id;
	cout << "\n";
	cout << "entry_ID = ";
	cin >> entry_id;
	cout << "\n";
	switch (entry_id)
	{
	case '1': // case of input Graph as adjacency matrix
	{
		char id;
		cout << "Enter ID:" << "\n" << " 1 - to put matrix from file" << "\n";
		cout << " 2 - to put matrix by yourself" << "\n";
		cout << " 3 - to exit" << "\n";
		cout << "\n";
		cout << "ID = ";
		cin >> id;
		switch (id)
		{
		case '1': 
		{
			ifstream in;
			while (true)
			{
				cout << "Enter File name: " << "\n";
				string path;
				cin >> path;
				in.open(path);
				if (in.is_open())
				{
					break;
				}
				else
				{
					cout << "ERROR: File not found, try again\n";
				}
			}

			int N;
			in >> N;
			Matrix A(N);
			A.scan_Matrix(in);  // read matrix from file "path"
			in.close();
			SRGraph(A);
			break;
		}
		case '2':
		{
			int N;
			cout << "Enter number of vertices: " << "\n";
			cin >> N;
			Matrix A(N);
			for (int i = 0; i < N; i++)  // read matrix from console
			{
				for (int j = 0; j < N; j++)
				{
					if (i < j)
					{
						cout << "A[" << i + 1 << "]" << "[" << j + 1 << "] = ";
						cin >> A[i][j];
					}
					else
					{
						if (i == j)
						{
							A[i][j] = 0;
						}
						else
						{
							A[i][j] = A[j][i];
						};
					};
				};
			};
			SRGraph(A);
			break;
		}
		case '3':
		{
			exit(1);
		}
		default:
			cout << "ERROR: Unknown symbol recieved, try again\n";
			break;
		}
		break;
	}
	case '2':  // case of input Graph as adjacency list
	{
		char id;
		cout << "Enter ID:" << "\n" << " 1 - to put list from file" << "\n";
		cout << " 2 - to put list by yourself" << "\n";
		cout << " 3 - to exit" << "\n";
		cout << "\n";
		cout << "ID = ";
		cin >> id;
		switch (id)
		{
		case '1':
		{
			ifstream in;
			while (true)
			{
				cout << "Enter File name: " << "\n";
				string path;
				cin >> path;
				in.open(path);
				if (in.is_open())
				{
					break;
				}
				else
				{
					cout << "ERROR: File not found, try again\n";
				}
			}

			int N;
			in >> N;
			Matrix A(N);
			while (!in.eof())   // read list from file "path"
			{
				int node1 = 0, node2 = 0;
				in >> node1;
				in >> node2;
				A[node1 - 1][node2 - 1] = 1;
				A[node2 - 1][node1 - 1] = 1;
				//cout << node1 << " - " << node2 << endl;
			}
			in.close();
			SRGraph(A);
			break;
		}
		case '2':
		{
			int N;
			cout << "Enter number of vertices: " << "\n";
			cin >> N;
			Matrix A(N);
			cout << "Enter the adjacency list: " << "\n";
			int node1 = 0, node2 = 0;
			while (true)  // read list from console
			{				
				cin >> node1;
				if (node1 == 0)
				{
					break;
				}
				cin >> node2;
				A[node1 - 1][node2 - 1] = 1;
				A[node2 - 1][node1 - 1] = 1;
				//cout << node1 << " - " << node2 << endl;
			}
			//A.print("output_L2.txt");
			SRGraph(A);
			break;
		}
		case '3':
		{
			exit(1);
		}
		default:
			cout << "ERROR: Unknown symbol recieved, try again\n";
			break;
		}
		break;
	}
	case '3':
	{
		exit(1);
	}
	default:
		cout << "ERROR: Unknown symbol recieved, try again";
		break;
	}
}


int main()
{
	Greeting();
	while (true)
	{
		Strongly_Regular_Graph();
	}
	
	return 0;
}