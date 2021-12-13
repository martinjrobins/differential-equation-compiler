#include <assert.h>
#include <iostream>
#include <peglib.h>

using namespace peg;
using namespace std;
 
/*
 * Utilities
 */
string format_error_message(size_t ln, size_t col,
                            const string& msg) {
  stringstream ss;
  ss << ln << ":" << col << ": " << msg << endl;
  return ss.str();
}

int main(int argc, const char **argv) {

  parser parser(R"(
  model_library <- model+

  model <- 'model' name '(' args ')' definitions? equations? solve


  args <- arg (',' arg)*
  arg <- definition / ident

  solve <- 'return' expression (',' expression )*

  definitions <- 'let' definition (',' definition)*
  definition <-  domain_definition / variable_definition
  domain_definition <- name 'in' range
  variable_definition <- name ':' domain '->' domain

  range <- '[' real ',' real ']' ('^' integer)?

  domain <- constant_domain / real_domain / ident
  constant_domain <- '1'
  real_domain <- 'R' ('^' integer)?

  equations <- 'in' equation (',' equation)*
  equation <- expression '=' expression

  call <- ident '(' expression ')'
  sequence <- real ':' real ':' real
  derivative <- 'd' ident '/' 'd' ident
  expression <- sign term (term_op term)*
  term       <- factor (factor_op factor)*
  factor     <-  sum_squared_error / sequence / derivative / call / ident / real / integer / '(' expression ')'
  sum_squared_error <- 'sum_squared_error' '(' expression ',' expression ',' expression ')'

  sign       <- < [-+]? >
  term_op    <- < [-+] >
  factor_op  <- < [*/^] >

  ident      <- < name ('.' name)* >
  name      <- < [a-z] [a-z0-9_]* >
  integer    <- < [0-9]+ >
  real       <- < [0-9]+'.'[0-9]+ > / integer

  %whitespace <- [ \t\r\n]*
  )");

  assert(static_cast<bool>(parser) == true);

  parser.enable_ast();

  parser.log = [&](size_t ln, size_t col, const string& msg) {
    cerr << format_error_message(ln, col, msg) << endl;
  };

  auto expr = argv[1];
 
  std::shared_ptr<Ast> ast;
  if (parser.parse(expr, ast)) {
    std::cout << ast_to_s(ast);
    ast = parser.optimize_ast(ast);
    std::cout << ast_to_s(ast);
    return 0;
  }

  
  std::cout << "syntax error..." << std::endl;

}

