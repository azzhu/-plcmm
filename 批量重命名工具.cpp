// ��������������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

using namespace std;

void getAllFilesPath(string path, vector<string>& files)
{
	//�ļ����
	long   hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮
			//�������,�����б�
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getAllFilesPath(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

//�����в������ļ���·����ͼ���ʽ��
int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 3)
	{
		cout << "�����в������ô���\n"
			<< "exe �ļ���·�� �ļ���ʽ" << endl;
		return 0;
	}
	string path = argv[1];
	string gs = argv[2];
	vector<string> files;
	getAllFilesPath(path, files);
	string fntemp;
	cout << "��" << files.size() << "���ļ�" << endl;

	//��һ��������
	vector<string>::iterator itb = files.begin(), ite = files.end();
	for (; itb != ite; itb++)
	{
		fntemp = *itb + "temp_";
		rename(itb->c_str(), fntemp.c_str());
	}

	//�ڶ���������
	vector<string> files2;
	getAllFilesPath(path, files2);
	vector<string>::iterator itb2 = files2.begin(), ite2 = files2.end();
	int ind = 1;
	for (; itb2 != ite2; itb2++)
	{
		fntemp = path + "/" + to_string(ind) + gs;
		rename(itb2->c_str(), fntemp.c_str());
		ind++;
		cout << ind << endl;
	}
	cout << "������" << files2.size() << "���ļ�" << endl;

	return 0;
}

