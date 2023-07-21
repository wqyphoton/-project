#include <iostream>
#include "tree.h"
#include "sha256.h"
using namespace std;

int main()
{
	string check_str = "";
	cout << "���� Merkle Tree��Ҷ�ӽ������ݣ��ԡ�;����Ϊ������: " << endl;
	vector<string> v;

	while (1) //����Ҷ�ӽڵ�
	{
		string str;
		cin >> str;
		if (str != ";")
		{
			v.push_back(str);
		}
		else
		{
			break;
		}
	}

	tree ntree;
	ntree.buildBaseLeafes(v);
	cout << "����Merkle��:" << endl << endl;
	ntree.buildTree();

	cout << endl;
	cout << "����֤������: " << endl;
	cin >> check_str; //��������֤��Ҷ�ӽڵ�
	check_str = sha2::hash256_hex_string(check_str);

	cout << "����֤�����ݵĹ�ϣֵ: " << check_str << endl;

	if (ntree.verify(check_str))//��֤��������ڵ� �����޸ı�
	{
		cout << endl << endl;
		cout << "Merkle���ϴ�����֤�����ݵ�Ҷ�ӽ��" << endl;
	}
	else
	{
		cout << "Merkle���ϲ�������֤������" << endl;
	}
	return 0;
}
