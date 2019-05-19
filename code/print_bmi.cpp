#include <Rcpp.h>
using namespace Rcpp;

double calc_bmi(int weight, double height){
  double bmi = weight / (height * height) ;
  return bmi ;
}


// [[Rcpp::export]]
std::string print_bmi(int weight, double height){
  
  double bmi;
  std::string print_text; 
  
  bmi = calc_bmi(weight, height);
  
  if (bmi < 18.5 ) {
    print_text = "underweight, 저체중";
  } else if( (bmi >= 18.5) & (bmi < 23) ) {
    print_text =  "normal, 정상";
  } else if( (bmi >= 23) & (bmi < 25) ){
    print_text = "obesity, 빈만 1 단계";
  } else if( (bmi >= 25) & (bmi < 30) ){
    print_text = "obesity, 빈만 2,3 단계";
  } else {
    print_text = "obesity, 고도";
  } 
  return print_text;
}

/*** R
print_bmi(70, 1.7)
*/
