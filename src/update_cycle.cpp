#include "update_cycle.h"
UpdateCycle::UpdateCycle(const double length) : length{length} {};

bool UpdateCycle::pastLength(const double time) {
  return time - currTime >= length;
}
void UpdateCycle::pushNewTime(const double newCurrTime) {
  currCount++;
  prevTime = currTime, currTime = newCurrTime;
  delta = currTime - prevTime;
}
void UpdateCycle::pushCount() { prevCount = currCount, currCount = 0; }