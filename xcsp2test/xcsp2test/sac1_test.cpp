//#pragma once
//#include <sstream>
//#include <string>
//#include "Timer.h"
//#include <string>
//#include <windows.h>
//#include <io.h>  
//#include <string>
//#include <iostream>
//#include "XModel.h"
//#include "XBuilder.h"
//#include "../CCSolver/Network.h"
//#include "../CCSolver/Solver.h"
//using namespace cp;
//using namespace std;
//
//typedef unsigned long long u64;
//
//const string XPath = "BMPath.xml";
//const int64_t TimeLimit = 1800000;
//const string bmp_root = "E:\\Projects\\benchmarks\\";
//const string bmp_ext = ".xml";
//void getFilesAll(string path, vector<string>& files);
//
//int main(const int argc, char ** argv) {
//
//	if (argc <= 1) {
//		cout << "no argument" << endl;
//		return 0;
//	}
//
//	vector<string> files;
//	getFilesAll(bmp_root + argv[1], files);
//	vector<int64_t> sac_time;
//	vector<int64_t> build_time;
//	vector<IntVar*> x_ext;
//	sac_time.reserve(files.size());
//	build_time.reserve(files.size());
//
//	for (const auto f : files) {
//		cout << f << endl;
//		XBuilder builder(f, XRT_BM);
//		HModel* hm = new HModel();
//		builder.GenerateHModel(hm);
//		Network* n = new Network(hm);
//
//		Timer t0;
//		//SAC3 sac(n, AC_3bit, Heuristic::VRH_DOM_MIN, Heuristic::VLH_MIN);
//		SAC1 sac(n, AC_3bit);
//		sac.enforce(n->vars, 0);
//		sac_time.push_back(t0.elapsed());
//		Timer t1;
//
//		vector<bitSetVector> bd;
//		vector<vector<vector<bitSetVector>>> bitDoms_;
//		const int vs_size = n->vars.size();
//		bd.resize(vs_size, bitSetVector(n->max_bitDom_size(), 0));
//
//		vector<IntVar*> x_evt;
//		bitDoms_.resize(vs_size, vector<vector<bitSetVector>>(n->max_domain_size(), vector<bitSetVector>(n->vars.size(), bitSetVector(n->max_bitDom_size(), 0))));
//		for (auto v : n->vars) {
//			for (auto i : v->values()) {
//				if (v->have(i, 0)) {
//					auto a = GetBitIdx(i);
//					bd[v->id()][get<0>(a)][get<1>(a)] = true;
//					n->CopyLevel(0, 1);
//					v->ReduceTo(i, 1);
//					v->assign(true, 1);
//					x_evt.push_back(v);
//					sac.ac_->enforce(x_ext, 1);
//					x_evt.clear();
//					for (auto x : n->vars) {
//						for (auto j : x->values()) {
//							if (x->have(j, 1)) {
//								auto b = GetBitIdx(j);
//								bitDoms_[v->id()][i][x->id()][get<0>(b)][get<1>(b)] = true;
//							}
//						}
//					}
//					n->ClearLevel(1);
//				}
//
//			}
//		}
//		build_time.push_back(t1.elapsed());
//
//		//cout << "----------------------bitDom----------------------" << endl;
//		//for (auto v : bd)
//		//	if (v->id() == (v->size() - 1))
//		//		for (const auto a : v)
//		//			cout << a << " ";
//		//cout << endl;
//
//		//cout << "----------------------bitSubDom----------------------" << endl;
//		//for (int i = 0; i < bitDoms_.size(); i++) {
//		//	for (int j = 0; j < bitDoms_[i].size(); j++) {
//		//		if (bitDoms_[i][j][0][0].test(0) && j == i) {
//		//			printf("[%2d][%2d]: ", i, j);
//		//		}
//		//	}
//		//}
//		//cout << endl;
//
//
//		delete hm;
//		delete n;
//	}
//
//	cout << "---------------sac_time---------------" << endl;
//	for (auto i : sac_time)
//		cout << i << endl;
//	cout << "---------------build_time---------------" << endl;
//	for (auto i : build_time)
//		cout << i << endl;
//
//
//	return 0;
//}
//
//void getFilesAll(const string path, vector<string>& files) {
//	//文件句柄 
//	intptr_t  h_file;
//	//文件信息 
//	struct _finddata_t fileinfo;
//	string p;
//	if ((h_file = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
//		do {
//			if ((fileinfo.attrib & _A_SUBDIR)) {
//				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
//					getFilesAll(p.assign(path).append("\\").append(fileinfo.name), files);
//			}
//			else
//				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
//		} while (_findnext(h_file, &fileinfo) == 0);
//		_findclose(h_file);
//	}
//}