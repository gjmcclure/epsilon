#include "function_store.h"
extern "C" {
#include <assert.h>
}

constexpr int Graph::FunctionStore::numberOfDefaultColors;
constexpr KDColor Graph::FunctionStore::defaultColors[numberOfDefaultColors];

Graph::FunctionStore::FunctionStore() :
  m_numberOfFunctions(0)
{
}

Graph::Function * Graph::FunctionStore::functionAtIndex(int i) {
  assert(i>=0 && i<m_numberOfFunctions);
  return &m_functions[i];
}

Graph::Function * Graph::FunctionStore::addEmptyFunction() {
  assert(m_numberOfFunctions < k_maxNumberOfFunctions);
  Graph::Function addedFunction = Function();
  addedFunction.setColor(defaultColors[numberOfFunctions()%numberOfDefaultColors]);
  addedFunction.setName("f(x)");
  addedFunction.setActive(true);
  m_functions[m_numberOfFunctions] = addedFunction;
  Function * result = &m_functions[m_numberOfFunctions];
  m_numberOfFunctions++;
  return result;
}

void Graph::FunctionStore::removeFunction(Function * f) {
  int i = 0;
  while (&m_functions[i] != f && i < m_numberOfFunctions) {
    i++;
  }
  assert(i>=0 && i<m_numberOfFunctions);
  m_numberOfFunctions--;
  for (int j = i; j<m_numberOfFunctions; j++) {
    m_functions[j] = m_functions[j+1];
  }
}

int Graph::FunctionStore::numberOfFunctions() {
  return m_numberOfFunctions;
}