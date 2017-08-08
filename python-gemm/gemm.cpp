#include <Eigen/Dense>
#include <iostream>
using namespace Eigen;
using namespace std;
int main(int argc, char* argv[])
{

    if (argc < 2) {
        printf("Usage : ./matrix width_of_square_matrix\n");
    }
    uint32_t width = atoi(argv[1]);

    MatrixXd m = MatrixXd::Random(width, width);
    m = (m + MatrixXd::Constant(width, width, 1.2)) * 50;
    //cout << "m =" << endl
    //     << m << endl;
    //cout << "m * m =" << endl
    //     << m * m << endl;
    m = m*m;
    return 0;
}
