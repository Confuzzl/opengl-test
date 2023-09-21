#include "update_cycle.h"
UpdateCycle::UpdateCycle(double length) : length{length} {};

bool UpdateCycle::pastLength(double time) { return time - currTime >= length; }
void UpdateCycle::pushNewTime(double newCurrTime) {
  currCount++;
  prevTime = currTime, currTime = newCurrTime;
  delta = currTime - prevTime;
}
void UpdateCycle::pushCount() { prevCount = currCount, currCount = 0; }