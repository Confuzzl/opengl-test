#pragma once
struct UpdateCycle {
  const double length;
  double prevTime = 0, currTime = 0, delta = 0;
  unsigned long long prevCount = 0, currCount = 0;

  UpdateCycle(const double length);

  bool pastLength(const double time);
  void pushNewTime(const double newCurrTime);
  void pushCount();
};