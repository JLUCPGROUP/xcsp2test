#include <string>
#include <iostream>
#include "XModel.h"
#include "XBuilder.h"
using namespace std;
using namespace cp;
const string X_PATH = "BMPath.xml";
int main() {
	XBuilder builder(X_PATH);
	HModel* hm = new HModel();
	builder.GenerateHModel(hm);
	Network* n = new Network(hm);
	hm->show();
	delete hm;
	return 0;
}

