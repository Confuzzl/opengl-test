#pragma once
struct UpdateCycle {
  const double length;
  double prevTime = 0, currTime = 0, delta = 0;
  unsigned long long prevCount = 0, currCount = 0;

  UpdateCycle(double length);

  bool pastLength(double time);
  void pushNewTime(double newCurrTime);
  void pushCount();
};