#include <contest.h>

/* Practice problem: Compute the diameter of a set
   
   A very similar problem occurred in the 2010 contest.  This problem
   has these differences:
   - The number of elements in each set is not bounded
   - Multiple sets are given, one per line
   - The desired accuracy is given as two decimal places rather than
     as a percentage.

   These differences are rather annoying.  Here I simply use some
   fixed-length buffers and hope that they are big enough.  The input
   format is a mix of line-oriented and token-oriented, which is
   annoying to deal with.  Unfortunately the contest environment
   doesn't allow the use of a modern "getline()" function.  
 */
const double inf = 1.0/0.0;

double coords[2][1024];

double diameter(int n) {
  double max_diameter = -inf;

  for (double angle=0; angle <= M_PI/2; angle += M_PI/180.0) {
    
    // find the min and max x-coordinate in this orientation
    double min =  inf;
    double max = -inf;
    int min_i, max_i;

    for (int i=0; i<n; i++) {
      double coord = coords[0][i]*cos(angle) - coords[1][i]*sin(angle);
      if (coord < min) {
	min = coord;
	min_i = i;
      }
      if (coord > max) {
	max = coord;
	max_i = i;
      }
    }
    double diameter = sqrt(pow(coords[0][max_i]-coords[0][min_i], 2) + 
			   pow(coords[1][max_i]-coords[1][min_i], 2));

    if (diameter > max_diameter) 
      max_diameter = diameter;
  }
  return max_diameter;
}

#define D if (0)

int main(int argc, char **argv) {
  
  char *s = (char *)calloc(1024*1024, sizeof(char)); // ridiculously large 

  char whitespace[] = " \n\r\t";
  int m = 0; 

  while (gets(s)) {
    printf("Set #%d: ", ++m);

    int n = 0;

    // parse the input
    char *saveptr;
    for (char *str = s; ; str = 0) {
      char *token = strtok_r(str, whitespace, &saveptr);
      if (!token)
	break;
      sscanf(token, "%lf", &coords[n%2][n/2]);
      n++;
    }

    n /= 2;
    
    D for (int i=0; i<n; i++) 
      printf("(%lf,%lf)\n", coords[0][i], coords[1][i]);


    double result = diameter(n);
    printf("Diameter is %0.2f\n", result);
  }
  
  return 0;
}
