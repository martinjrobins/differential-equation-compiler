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
    model <- 'model' ident equations definitions solve

    solve <- 'solve' expression (',' expression )*

    definitions         <- 'where' definition (',' definition)*
    definition          <-  domain_definition / variable_definition
    domain_definition   <- ident 'in' range
    variable_definition <- ident ':' domain '->' domain

    domain          <- constant_domain / real_domain / ident
    constant_domain <- '1'
    real_domain     <- 'R' ('^' integer)?
    range           <- '[' real ',' real ']' ('^' integer)?

    equations         <- equation (',' equation)*
    equation          <- rate_equation / initial_condition
    rate_equation     <- 'd' ident '/' 'd' ident '=' expression
    initial_condition <- fixed_variable '=' expression

    expression     <- sign term (term_op term)*
    term           <- factor (factor_op factor)*
    factor         <- fixed_variable / ident / real / integer / '(' expression ')'
    fixed_variable <- ident '(' real ')'

    sign       <- < [-+]? >
    term_op    <- < [-+] >
    factor_op  <- < [*/] >

    ident      <- < [a-z] [a-z0-9]* >
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

