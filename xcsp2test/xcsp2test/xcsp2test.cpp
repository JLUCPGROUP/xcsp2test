#include <string>
#include <iostream>
#include "XModel.h"
#include "XBuilder.h"
using namespace std;
using namespace cp;
const string X_PATH = "BMPath.xml";
int main() {
	XBuilder builder(X_PATH);
	XModel* xm = new XModel();
	builder.GenerateXModelFromXml(xm);
	xm->show();
	delete xm;
	cout << "234" << endl;
	return 0;
}

