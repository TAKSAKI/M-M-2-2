#include<iostream>
using namespace std;
#include<cmath>
#include<stdlib.h>
#include <algorithm>
#include<fstream>
#define END_TIME 1000//終了時刻を1000に設定
#define try 200//客が単位時間平均に訪れる回数の最大値設定
double rnd_exp(double ramda) {  //指数分布の乱数生成
	double a = (rand() + 0.5) / (RAND_MAX + 1);
	return -log(1 - a) / ramda;
}
int main() {
	ofstream ofs("第三回ver2.csv");//データをエクセルファイルで保存
	double customramda = 1;
	double server1ramda = 10;//サーバ２つ共に単位時間平均処理回数を10にする
	double server2ramda = 10;
	for (int i = 0; i < try; i++) {//客が単位時間平均に訪れる回数を１から200までとしどれくらいロスが出るか実験
		double cusnum = 0;//時刻の初期設定
		double lossnum = 0;
		double customtime = 0;
		double server1time = 0;
		double server2time = 0;
		double ave = 0;
		while (true) {
			double x = rnd_exp(customramda);
			customtime += x;//時刻の更新
			if (customtime > END_TIME) {//END_TIMEの時の処理
				customtime -= x;
				break;
			}
			cusnum += 1;
			double minit = min(server1time, server2time);
			if (customtime < minit) lossnum += 1;//客の到着時刻がどのサーバーの利用終了時刻よりも小さい場合利用できないのでロスの数を追加
			else if (customtime >= minit&&minit == server1time) {
				server1time = customtime + rnd_exp(server1ramda);
				if (server2time < customtime) server2time = customtime;//もしどちらも利用可能だった場合お客の時刻に更新
				
			}
			else if (customtime >= minit && minit == server2time) {
				server2time = customtime + rnd_exp(server2ramda);
				if (server1time < customtime) server1time = customtime;
				
			}
		}
		ofs <<customramda<<","<< lossnum / cusnum << endl;
		customramda += 1;
	}
}
