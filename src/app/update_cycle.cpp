module;

module app.update_cycle;

UpdateCycle::UpdateCycle(const unsigned short rate)
    : rate{rate}, length{1.0 / rate} {};

void UpdateCycle::setRate(const unsigned short rate) {
  this->rate = rate;
  this->length = 1.0 / rate;
}

bool UpdateCycle::pastLength(const double time) {
  return time - currTime >= length;
}
void UpdateCycle::pushNewTime(const double newCurrTime) {
  currCount++;
  prevTime = currTime, currTime = newCurrTime;
  delta = currTime - prevTime;
}
void UpdateCycle::pushCount() { prevCount = currCount, currCount = 0; }