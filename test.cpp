#include "test.h"

Test::Test(string files_name) {
	this->files_name = files_name;
}

Test::~Test() {}

Mat Test::readOpticalFlow() {
	Mat_<Point2f> flow;
    ifstream file(files_name.c_str(), ios_base::binary);
    if (!file.good())
        return flow; // no file - return empty matrix

    float tag;
    file.read((char*) &tag, sizeof(float));
    if (tag != FLOW_TAG_FLOAT)
        return flow;

    int width, height;

    file.read((char*) &width, 4);
    file.read((char*) &height, 4);

    flow.create(height, width);

    for (int i = 0; i < flow.rows; i++)
    {
        for (int j = 0; j < flow.cols; j++)
        {
            Point2f u;
            file.read((char*) &u.x, sizeof(float));
            file.read((char*) &u.y, sizeof(float));
            if (!file.good())
            {
                flow.release();
                return flow;
            }

            flow(i, j) = u;
        }
    }
    file.close();
	return flow;
}

void Test::run(double **vx, double **vy, int width, int height) {
	Mat groundT = readOpticalFlow();
	double err = 0.0;
	double mmax = -10, mmin = 1100;
	for(int i = 0; i < groundT.rows; i++) {
		for(int j = 0; j < groundT.cols; j++) {
			Point2f val = groundT.at<Point2f>(i, j);
			Point2f verr;

			if(fabs(val.x) > 1000 || fabs(val.y) > 1000)
				continue;

			verr.x = val.x - (vx[i][j]);
			verr.y = val.y - (vy[i][j]);
			double eact = sqrt(verr.x * verr.x + verr.y * verr.y);
			mmax = max(mmax, eact);
			mmin = min(mmin, eact);
			err += eact;
		}
	}

	printf("Error total: %g p/f\n", err);
	printf("Error promedio: %g p/f\n", err / (double)(width * height));
	printf("Máximo: %g p/f\n", mmax);
	printf("Mínimo: %g p/f\n", mmin);
}