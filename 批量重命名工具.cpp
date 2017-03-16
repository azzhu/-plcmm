// 批量重命名工具.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace std;

void getAllFilesPath(string path, vector<string>& files)
{
	//文件句柄
	long   hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
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

//命令行参数：文件夹路径、图像格式；
int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 3)
	{
		cout << "命令行参数设置错误\n"
			<< "exe 文件夹路径 文件格式" << endl;
		return 0;
	}
	string path = argv[1];
	string gs = argv[2];
	vector<string> files;
	getAllFilesPath(path, files);
	string fntemp;
	cout << "共" << files.size() << "个文件" << endl;

	//第一次重命名
	vector<string>::iterator itb = files.begin(), ite = files.end();
	for (; itb != ite; itb++)
	{
		fntemp = *itb + "temp_";
		rename(itb->c_str(), fntemp.c_str());
	}

	//第二次重命名
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
	cout << "共处理" << files2.size() << "个文件" << endl;

	return 0;
}

