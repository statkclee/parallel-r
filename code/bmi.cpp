#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
double calc_bmi(int weight, double height){
  double bmi = weight / (height * height) ;
  return bmi ;
}

/*** R
calc_bmi(70, 1.7)
*/
