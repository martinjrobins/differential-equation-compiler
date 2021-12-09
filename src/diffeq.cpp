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
    expression <- sign term (term_op term)*
    term       <- factor (factor_op factor)*
    factor     <- ident / number / '(' expression ')' 

    sign       <- < [-+]? > 
    term_op    <- < [-+] > 
    factor_op  <- < [*/] > 

    ident      <- < [a-z] [a-z0-9]* > 
    number     <- < [0-9]+ >

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

