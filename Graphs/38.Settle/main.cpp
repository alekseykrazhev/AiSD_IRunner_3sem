#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <cfloat> // for DBL_MAX
#include <cmath>  // for fabs()

void step5(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns,
           bool *coveredRows, int nOfRows, int nOfColumns, int minDim);
void step2b(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns,
            bool *coveredRows, int nOfRows, int nOfColumns, int minDim);

void computeassignmentcost(const int *assignment, double *cost, const double *distMatrix, int nOfRows)
{
    int row, col;

    for (row = 0; row<nOfRows; row++)
    {
        col = assignment[row];
        if (col >= 0)
            *cost += distMatrix[row + nOfRows*col];
    }
}

void step2a(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns,
            bool *coveredRows, int nOfRows, int nOfColumns, int minDim)
{
    bool *starMatrixTemp, *columnEnd;
    int col;

    /* cover every column containing a starred zero */
    for (col = 0; col<nOfColumns; col++)
    {
        starMatrixTemp = starMatrix + nOfRows*col;
        columnEnd = starMatrixTemp + nOfRows;
        while (starMatrixTemp < columnEnd){
            if (*starMatrixTemp++)
            {
                coveredColumns[col] = true;
                break;
            }
        }
    }

    /* move to step 3 */
    step2b(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
}

void step4(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns,
           bool *coveredRows, int nOfRows, int nOfColumns, int minDim, int row, int col)
{
    int n, starRow, starCol, primeRow, primeCol;
    int nOfElements = nOfRows*nOfColumns;

    /* generate temporary copy of starMatrix */
    for (n = 0; n<nOfElements; n++)
        newStarMatrix[n] = starMatrix[n];

    /* star current zero */
    newStarMatrix[row + nOfRows*col] = true;

    /* find starred zero in current column */
    starCol = col;
    for (starRow = 0; starRow<nOfRows; starRow++)
        if (starMatrix[starRow + nOfRows*starCol])
            break;

    while (starRow<nOfRows)
    {
        /* unstar the starred zero */
        newStarMatrix[starRow + nOfRows*starCol] = false;

        /* find primed zero in current row */
        primeRow = starRow;
        for (primeCol = 0; primeCol<nOfColumns; primeCol++)
            if (primeMatrix[primeRow + nOfRows*primeCol])
                break;

        /* star the primed zero */
        newStarMatrix[primeRow + nOfRows*primeCol] = true;

        /* find starred zero in current column */
        starCol = primeCol;
        for (starRow = 0; starRow<nOfRows; starRow++)
            if (starMatrix[starRow + nOfRows*starCol])
                break;
    }

    /* use temporary copy as new starMatrix */
    /* delete all primes, uncover all rows */
    for (n = 0; n<nOfElements; n++)
    {
        primeMatrix[n] = false;
        starMatrix[n] = newStarMatrix[n];
    }
    for (n = 0; n<nOfRows; n++)
        coveredRows[n] = false;

    /* move to step 2a */
    step2a(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
}

void step3(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns,
           bool *coveredRows, int nOfRows, int nOfColumns, int minDim)
{
    bool zerosFound;
    int row, col, starCol;

    zerosFound = true;
    while (zerosFound)
    {
        zerosFound = false;
        for (col = 0; col<nOfColumns; col++)
            if (!coveredColumns[col])
                for (row = 0; row<nOfRows; row++)
                    if ((!coveredRows[row]) && (fabs(distMatrix[row + nOfRows*col]) < DBL_EPSILON))
                    {
                        /* prime zero */
                        primeMatrix[row + nOfRows*col] = true;

                        /* find starred zero in current row */
                        for (starCol = 0; starCol<nOfColumns; starCol++)
                            if (starMatrix[row + nOfRows*starCol])
                                break;

                        if (starCol == nOfColumns) /* no starred zero found */
                        {
                            /* move to step 4 */
                            step4(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns,
                                  coveredRows, nOfRows, nOfColumns, minDim, row, col);
                            return;
                        }
                        else
                        {
                            coveredRows[row] = true;
                            coveredColumns[starCol] = false;
                            zerosFound = true;
                            break;
                        }
                    }
    }

    /* move to step 5 */
    step5(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
}

void buildassignmentvector(int *assignment, const bool *starMatrix, int nOfRows, int nOfColumns)
{
    int row, col;

    for (row = 0; row<nOfRows; row++)
        for (col = 0; col<nOfColumns; col++)
            if (starMatrix[row + nOfRows*col])
            {
#ifdef ONE_INDEXING
                assignment[row] = col + 1; /* MATLAB-Indexing */
#else
                assignment[row] = col;
#endif
                break;
            }
}

void step2b(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns,
            bool *coveredRows, int nOfRows, int nOfColumns, int minDim)
{
    int col, nOfCoveredColumns;

    /* count covered columns */
    nOfCoveredColumns = 0;
    for (col = 0; col<nOfColumns; col++)
        if (coveredColumns[col])
            nOfCoveredColumns++;

    if (nOfCoveredColumns == minDim)
    {
        /* algorithm finished */
        buildassignmentvector(assignment, starMatrix, nOfRows, nOfColumns);
    }
    else
    {
        /* move to step 3 */
        step3(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
    }

}

void assignmentoptimal(int *assignment, double *cost, double *distMatrixIn, int nOfRows, int nOfColumns)
{
    double *distMatrix, *distMatrixTemp, *distMatrixEnd, *columnEnd, value, minValue;
    bool *coveredColumns, *coveredRows, *starMatrix, *newStarMatrix, *primeMatrix;
    int nOfElements, minDim, row, col;

    /* initialization */
    *cost = 0;
    for (row = 0; row<nOfRows; row++)
        assignment[row] = -1;

    /* generate working copy of distance Matrix */
    /* check if all matrix elements are positive */
    nOfElements = nOfRows * nOfColumns;
    distMatrix = (double *)malloc(nOfElements * sizeof(double));
    distMatrixEnd = distMatrix + nOfElements;

    for (row = 0; row<nOfElements; row++)
    {
        value = distMatrixIn[row];
        distMatrix[row] = value;
    }


    /* memory allocation */
    coveredColumns = (bool *)calloc(nOfColumns, sizeof(bool));
    coveredRows = (bool *)calloc(nOfRows, sizeof(bool));
    starMatrix = (bool *)calloc(nOfElements, sizeof(bool));
    primeMatrix = (bool *)calloc(nOfElements, sizeof(bool));
    newStarMatrix = (bool *)calloc(nOfElements, sizeof(bool)); /* used in step4 */

    /* preliminary steps */
    if (nOfRows <= nOfColumns)
    {
        minDim = nOfRows;

        for (row = 0; row<nOfRows; row++)
        {
            /* find the smallest element in the row */
            distMatrixTemp = distMatrix + row;
            minValue = *distMatrixTemp;
            distMatrixTemp += nOfRows;
            while (distMatrixTemp < distMatrixEnd)
            {
                value = *distMatrixTemp;
                if (value < minValue)
                    minValue = value;
                distMatrixTemp += nOfRows;
            }

            /* subtract the smallest element from each element of the row */
            distMatrixTemp = distMatrix + row;
            while (distMatrixTemp < distMatrixEnd)
            {
                *distMatrixTemp -= minValue;
                distMatrixTemp += nOfRows;
            }
        }

        /* Steps 1 and 2a */
        for (row = 0; row<nOfRows; row++)
            for (col = 0; col<nOfColumns; col++)
                if (fabs(distMatrix[row + nOfRows*col]) < DBL_EPSILON)
                    if (!coveredColumns[col])
                    {
                        starMatrix[row + nOfRows*col] = true;
                        coveredColumns[col] = true;
                        break;
                    }
    }
    else /* if(nOfRows > nOfColumns) */
    {
        minDim = nOfColumns;

        for (col = 0; col<nOfColumns; col++)
        {
            /* find the smallest element in the column */
            distMatrixTemp = distMatrix + nOfRows*col;
            columnEnd = distMatrixTemp + nOfRows;

            minValue = *distMatrixTemp++;
            while (distMatrixTemp < columnEnd)
            {
                value = *distMatrixTemp++;
                if (value < minValue)
                    minValue = value;
            }

            /* subtract the smallest element from each element of the column */
            distMatrixTemp = distMatrix + nOfRows*col;
            while (distMatrixTemp < columnEnd)
                *distMatrixTemp++ -= minValue;
        }

        /* Steps 1 and 2a */
        for (col = 0; col<nOfColumns; col++)
            for (row = 0; row<nOfRows; row++)
                if (fabs(distMatrix[row + nOfRows*col]) < DBL_EPSILON)
                    if (!coveredRows[row])
                    {
                        starMatrix[row + nOfRows*col] = true;
                        coveredColumns[col] = true;
                        coveredRows[row] = true;
                        break;
                    }
        for (row = 0; row<nOfRows; row++)
            coveredRows[row] = false;

    }

    /* move to step 2b */
    step2b(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);

    /* compute cost and remove invalid assignments */
    computeassignmentcost(assignment, cost, distMatrixIn, nOfRows);

    /* free allocated memory */
    free(distMatrix);
    free(coveredColumns);
    free(coveredRows);
    free(starMatrix);
    free(primeMatrix);
    free(newStarMatrix);
}

double Solve(std::vector <std::vector<double> >& DistMatrix, std::vector<int>& Assignment)
{
    unsigned int nRows = DistMatrix.size();
    unsigned int nCols = DistMatrix[0].size();

    auto *distMatrixIn = new double[nRows * nCols];
    int *assignment = new int[nRows];
    double cost = 0.0;

    // Fill in the distMatrixIn. Mind the index is "i + nRows * j".
    // Here the cost matrix of size MxN is defined as a double precision array of N*M elements.
    // In the solving functions matrices are seen to be saved MATLAB-internally in row-order.
    // (i.e. the matrix [1 2; 3 4] will be stored as a vector [1 3 2 4], NOT [1 2 3 4]).
    for (unsigned int i = 0; i < nRows; i++)
        for (unsigned int j = 0; j < nCols; j++)
            distMatrixIn[i + nRows * j] = DistMatrix[i][j];

    // call solving function
    assignmentoptimal(assignment, &cost, distMatrixIn, nRows, nCols);

    Assignment.clear();
    for (unsigned int r = 0; r < nRows; r++)
        Assignment.push_back(assignment[r]);

    delete[] distMatrixIn;
    delete[] assignment;
    return cost;
}

void step5(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows,
           int nOfRows, int nOfColumns, int minDim)
{
    double h, value;
    int row, col;

    /* find smallest uncovered element h */
    h = DBL_MAX;
    for (row = 0; row<nOfRows; row++)
        if (!coveredRows[row])
            for (col = 0; col<nOfColumns; col++)
                if (!coveredColumns[col])
                {
                    value = distMatrix[row + nOfRows*col];
                    if (value < h)
                        h = value;
                }

    /* add h to each covered row */
    for (row = 0; row<nOfRows; row++)
        if (coveredRows[row])
            for (col = 0; col<nOfColumns; col++)
                distMatrix[row + nOfRows*col] += h;

    /* subtract h from each uncovered column */
    for (col = 0; col<nOfColumns; col++)
        if (!coveredColumns[col])
            for (row = 0; row<nOfRows; row++)
                distMatrix[row + nOfRows*col] -= h;

    /* move to step 3 */
    step3(assignment, distMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
}


void departmentFill (std::ifstream& in, std::vector<int>& dep) {
    std::string numb;
    int temp;
    std::getline(in, numb);
    std::istringstream iss (numb);
    while (iss >> temp) {
        dep.emplace_back(temp);
    }
}

void resize_matrix(std::vector<std::vector<double>> &matrix, const unsigned int& n){
    matrix.resize(n);
    for (auto& i : matrix) {
        for (int j = 0; j < n; ++j) {
            i.push_back(0);
        }
    }
}

void create_cost_matrix(std::vector<int>& group_1, std::vector<int>& group_2, std::vector<std::vector<double>>& a, const unsigned int&n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (group_1.size() == n) {
                if (group_2.size() <= j) {
                    a[i][j] = group_1[i];
                } else {
                    a[i][j] = abs(group_1[i] - group_2[j]) * 2;
                }
            }
            else {
                if (group_1.size() <= j) {
                    a[i][j] = group_2[i];
                } else {
                    a[i][j] = abs(group_1[j] - group_2[i]) * 2;
                }
            }
        }
    }
}

int main() {
    std::ifstream in ("input.txt");
    std::ofstream out ("output.txt");

    std::vector<int> department1;
    std::vector<int> department2;
    std::vector<std::vector<double>> a;
    std::vector<int> a1;

    departmentFill(in, department1);
    departmentFill(in, department2);
    in.close();

    unsigned int max_size = std::max(department1.size(), department2.size());
    resize_matrix(a, max_size);
    create_cost_matrix(department1, department2, a, max_size);
    /*
    for (const auto& i : a) {
        for (auto j : i){
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }*/
    double ans = Solve(a, a1);
    ans /= 2;
    out << std::fixed << std::setprecision(1) << ans;
    out.close();
    return 0;
}
