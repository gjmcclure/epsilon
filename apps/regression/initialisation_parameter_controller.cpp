#include "initialisation_parameter_controller.h"
#include <assert.h>
#include <math.h>

namespace Regression {

InitialisationParameterController::InitialisationParameterController(Responder * parentResponder, Store * store) :
  ViewController(parentResponder),
  m_selectableTableView(SelectableTableView(this, this, Metric::TopMargin, Metric::RightMargin,
    Metric::BottomMargin, Metric::LeftMargin)),
  m_store(store)
{
}

const char * InitialisationParameterController::title() const {
  return "Zoom predefini";
}

View * InitialisationParameterController::view() {
  return &m_selectableTableView;
}

void InitialisationParameterController::didBecomeFirstResponder() {
  m_selectableTableView.selectCellAtLocation(0, 0);
  app()->setFirstResponder(&m_selectableTableView);
}

bool InitialisationParameterController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::OK) {
    RangeMethodPointer rangeMethods[k_totalNumberOfCells] = {&InteractiveCurveViewRange::roundAbscissa, &InteractiveCurveViewRange::normalize, &InteractiveCurveViewRange::setDefault};
    (m_store->*rangeMethods[m_selectableTableView.selectedRow()])();
    StackViewController * stack = (StackViewController *)parentResponder();
    stack->pop();
    return true;
  }
  return false;
}

int InitialisationParameterController::numberOfRows() {
  return k_totalNumberOfCells;
};


TableViewCell * InitialisationParameterController::reusableCell(int index) {
  assert(index >= 0);
  assert(index < k_totalNumberOfCells);
  return &m_cells[index];
}

int InitialisationParameterController::reusableCellCount() {
  return k_totalNumberOfCells;
}

KDCoordinate InitialisationParameterController::cellHeight() {
  return Metric::ParameterCellHeight;
}

void InitialisationParameterController::willDisplayCellForIndex(TableViewCell * cell, int index) {
  MenuListCell * myCell = (MenuListCell *)cell;
  const char * titles[3] = {"Abscisses entieres", "Orthonorme", "Reglage de base"};
  myCell->setText(titles[index]);
}

}