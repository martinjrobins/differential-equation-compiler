/// ExprAST - Base class for all expression nodes.
class ExprAST {
public:
  virtual ~ExprAST() {}
};


/// NumberExprAST - Expression class for numeric literals like "1.0".
class RealExprAST : public ExprAST {
  double value;

public:
  IntegerExprAST(double value) : val(value) {}
};

/// IntegerExprAST - Expression class for numeric literals like "1".
class RealExprAST : public ExprAST {
  int value;

public:
  IntegerExprAST(int value) : val(value) {}
};

/// IdentExprAST - Expression class for variables like "x".
class IdentExprAST : public ExprAST {
  std::string name;

public:
  IdentExprAST(std::string name) : name(name) {}
};

/// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
  char Op;
  std::unique_ptr<ExprAST> lhs, rhs;

public:
  BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs,
                std::unique_ptr<ExprAST> rhs)
    : Op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
};

class UnaryExprAST : public ExprAST {
  char Op;
  std::unique_ptr<ExprAST> lhs, rhs;

public:
  UnaryExprAST(char op, std::unique_ptr<ExprAST> child)
    : Op(op), child(std::move(child)) {}
};

class EquationExprAST : public ExprAST {
  std::unique_ptr<ExprAST> rhs;

public:
  EquationExprAST(std::unique_ptr<ExprAST> rhs)
    : rhs(std::move(rhs)) {}
};

class RateEquationExprAST : public EquationAST {
  std::string dep_var_name;
  std::string indep_var_name;

public:
  RateEquationExprAST(std::string dep_var_name, std::string indep_var_name, std::unique_ptr<ExprAST> rhs)
    : EquationAST(rhs), dep_var_name(dep_var_name), indep_var_name(indep_var_name)  {}
};

class BoundaryConditionExprAST : public EquationAST {
  std::string dep_var_name;
  double location;

public:
  BoundaryConditionExprAST(std::string dep_var_name, double location, std::unique_ptr<ExprAST> rhs)
    : EquationAST(rhs), dep_var_name(dep_var_name), location(location)  {}
};

class ConstantEquationExprAST : public EquationAST {
  std::string constant_name;

public:
  ConstantEquationExprAST(std::string constant_name, std::unique_ptr<ExprAST> rhs)
    : EquationAST(rhs), constant_name(constant_name)  {}
};

class ConstantEquationExprAST : public EquationAST {
  std::string constant_name;

public:
  ConstantEquationExprAST(std::string constant_name, std::unique_ptr<ExprAST> rhs)
    : EquationAST(rhs), constant_name(constant_name)  {}
};
