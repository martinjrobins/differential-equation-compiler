/// ExprAST - Base class for all expression nodes.
class ExprAST {
public:
  virtual ~ExprAST() {}
};


/// NumberExprAST - Expression class for numeric literals like "1.0".
class NumberExprAST : public ExprAST {
  double value;

public:
  NumberExprAST(double value) : val(value) {}
};

/// VariableExprAST - Expression class for variables like "x".
class IdentExprAST : public ExprAST {
  std::string name;

public:
  IdentExprAST(std::string name) : name(name) {}
};
